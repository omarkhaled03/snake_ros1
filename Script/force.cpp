#include <ros/ros.h>
#include <std_msgs/String.h>
#include <snake/jointcon.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "joint");
    ros::NodeHandle nh;
    
    ros::Publisher pub = nh.advertise<snake::jointcon>("/snake/jointcon", 10);
    
    ros::Rate loop_rate(10);
    while (ros::ok()) {
        snake::jointcon msg;
        msg.joint_1 = 5;
        std::cout<<msg.joint_1<<std::endl; 
        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}
