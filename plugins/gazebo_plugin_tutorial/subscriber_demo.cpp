#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

typedef const boost::shared_ptr<const gazebo::msgs::Empty> ConstEmptyPtr;

namespace gazebo{
    class ModelSub : public ModelPlugin{
        private:
            physics::ModelPtr model_;
            std::string world_name_;
            std::string topic_name_;
            gazebo::transport::NodePtr node_;
            gazebo::transport::SubscriberPtr sub_;
        public:
            void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf){
                this->model_ = _parent;
                this->world_name_ = _parent->GetWorld()->Name();
                gzmsg << this->world_name_ << std::endl;

                this->node_ = transport::NodePtr(new transport::Node());
                this->node_->Init(this->world_name_);
                this->topic_name_ = "/position/cmd";
                this->sub_ = this->node_->Subscribe(this->topic_name_, &ModelSub::OnMsg, this);
                gzmsg << "plug 1\n";
            }

            // ConstEmptyPtr
            void OnMsg(ConstGzStringPtr &_msg){
                gzmsg << "string msg " << _msg->data() << "\n";
            }

    };
    GZ_REGISTER_MODEL_PLUGIN(ModelSub)
}