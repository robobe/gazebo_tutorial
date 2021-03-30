#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/transport.hh>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

namespace gazebo
{
  class SimplePlugin : public ModelPlugin
  {
  public:
    void OnMessage(ConstGzStringPtr &msg)
    {
      gzmsg << msg->data() << std::endl;

      msgs::GzString o_msg;
      o_msg.set_data("hello from gazebo");
      this->my_publisher->Publish(o_msg);
    }

  public:
    void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      gzmsg << "demo plug for string pub/sub loaded";
      this->model = _parent;
      this->node = gazebo::transport::NodePtr(new gazebo::transport::Node());
      node->Init();

      this->my_subscriber = node->Subscribe("test/hello", &SimplePlugin::OnMessage, this);
      this->my_publisher = node->Advertise<msgs::GzString>("~/my_pub");

      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&SimplePlugin::OnUpdate, this));
    }

  public:
    void OnUpdate()
    {
    }

  private:
    physics::ModelPtr model;
    event::ConnectionPtr updateConnection;
    transport::SubscriberPtr my_subscriber;
    transport::PublisherPtr my_publisher;
    gazebo::transport::NodePtr node;
  };

  GZ_REGISTER_MODEL_PLUGIN(SimplePlugin)
} // namespace gazebo
