#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>
#include <ignition/math/Vector3.hh>
#include <ros/ros.h>
#include <snake/jointcon.h>
#include <geometry_msgs/Vector3.h>
namespace gazebo{
    class  Jointcontrol : public ModelPlugin{
    public:
        double  force_1_x ;
        double  force_1_y ;
        double  force_1_z ;

        double  force_2_x ;
        double  force_2_y ;
        double  force_2_z ;

        double  force_3_x ;
        double  force_3_y ;
        double  force_3_z ;


        int count = 0;
        void Load(physics::ModelPtr _model , sdf::ElementPtr _sdf){
            this->model = _model;
            if (!ros::isInitialized())
            {
                ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized");
                return;
            }
            

            //this->jointByNum = _model->GetLink("head_link"); 
            //std::cout<< "Joint By Number =" << this->jointByNum->GetScopedName() << std::endl;
            this->joint_sub = this->nh.subscribe("/snake/jointcon", 50, &Jointcontrol::jointcon_callback,this); 
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&Jointcontrol::OnUpdate, this));
        }
        void jointcon_callback(const snake::jointconPtr &msg){
           this->force_1_x = msg->force_1[0];
           this->force_1_y = msg->force_1[1];
           this->force_1_z = msg->force_1[2];

           this->force_2_x = msg->force_2[0];
           this->force_2_y = msg->force_2[1];
           this->force_2_z = msg->force_2[2];

           this->force_3_x = msg->force_3[0];
           this->force_3_y = msg->force_3[1];
           this->force_3_z = msg->force_3[2];


           //this->joint_1_x = msg->joint_1[0];
           //this->joint_1_y = msg->joint_1[1];
           //this->joint_1_z = msg->joint_1[2];

        }
        void OnUpdate() {
            //double t = joint_1;            
            const ignition::math::Vector3d force(this->force_1_x,this->force_1_y,this->force_1_z);
            const ignition::math::Vector3d force2(this->force_2_x,this->force_2_y,this->force_2_z);
            const ignition::math::Vector3d force3(this->force_2_x,this->force_2_y,this->force_2_z);
            //this->model->this->joint1->SetParam("fmax", 0, this->joint_1_x);
            this->model->GetLink("head_link")->SetForce(force3);
            this->model->GetLink("link_6")->SetForce(force);
            this->model->GetLink("link_9")->SetForce(force2);
            //ROS_INFO("Received Message = %d", this->joint_1);
            
            //std::cout<< this->force_1_x<<std::endl;

            }  
    

    private:
        physics::ModelPtr model;  // Pointer to the model
        event::ConnectionPtr updateConnection;
        ros::NodeHandle nh;
        ros::Subscriber joint_sub;
        
    };

    GZ_REGISTER_MODEL_PLUGIN(Jointcontrol);
}