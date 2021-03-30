#include <gazebo/gazebo.hh>
#include <gazebo/physics/Joint.hh>
#include <gazebo/physics/JointController.hh>
#include <gazebo/physics/Model.hh>
#include <gazebo/physics/PhysicsTypes.hh>

namespace gazebo
{
  class SetJointVelocityPlugin : public ModelPlugin
  {
    public: physics::JointControllerPtr jointController;

    public: virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
      {
        this->model = _model;
        this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&SetJointVelocityPlugin::Update, this, std::placeholders::_1));
      }

    public: void Update(const common::UpdateInfo &_info)
      {
        if (update_num == 0)
        {
          // Joint velocity instantaneously without applying forces
          this->model->GetJoint("gray_joint")->SetVelocity(0, 1.0);

          // Joint velocity using joint motors
          this->model->GetJoint("orange_joint")->SetParam("fmax", 0, 100.0);
          this->model->GetJoint("orange_joint")->SetParam("vel", 0, 1.0);

          // Joint velocity using PID controller
          this->jointController.reset(new physics::JointController(
                this->model));
          this->jointController->AddJoint(model->GetJoint("purple_joint"));
          std::string name = model->GetJoint("purple_joint")->GetScopedName();
          this->jointController->SetVelocityPID(name, common::PID(100, 0, 0));
          this->jointController->SetVelocityTarget(name, 1.0);
        }
        else if (update_num < 200)
        {
          // Must update PID controllers so they apply forces
          this->jointController->Update();
        }
        else if (update_num == 200)
        {
          // Joint motors are disabled by setting max force to zero
          this->model->GetJoint("orange_joint")->SetParam("fmax", 0, 0.0);
        }
        update_num++;
      }

    /// \brief a pointer to the model this plugin was loaded by
    public: physics::ModelPtr model;
    /// \brief object for callback connection
    public: event::ConnectionPtr updateConnection;
    /// \brief number of updates received
    public: int update_num = 0;
  };

  GZ_REGISTER_MODEL_PLUGIN(SetJointVelocityPlugin)
}
