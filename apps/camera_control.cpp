
#include <ignition/math/Pose3.hh>
#include <gazebo/gazebo_client.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>

#include <iostream>

int main(int _argc, char **_argv)
{
  // Load gazebo
  gazebo::client::setup(_argc, _argv);

  // Create our node for communication
  gazebo::transport::NodePtr node(new gazebo::transport::Node());
  node->Init();

  // Publish to a Gazebo topic
  gazebo::transport::PublisherPtr pub =
    node->Advertise<gazebo::msgs::Pose>("/gazebo/default/user_camera/joy_pose");

  // Wait for a subscriber to connect
  pub->WaitForConnection();

  // Publisher loop...replace with your own code.
  while (true)
  {
    // Throttle Publication
    gazebo::common::Time::MSleep(100);

    // Generate a pose
    ignition::math::Pose3d pose(0, 0, 3, 0, 0, 0);

    // Convert to a pose message
    gazebo::msgs::Pose msg;
    gazebo::msgs::Set(&msg, pose);

    pub->Publish(msg);
    break;
  }

  // Make sure to shut everything down.
  gazebo::client::shutdown();
}