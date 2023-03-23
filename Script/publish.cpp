#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sstream>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  double phase_shift;
  if (n.getParam("phase_shift",phase_shift)){
    ROS_INFO("Got Phase Shift Parameter");
  }
  else{
    phase_shift = -30;
    ROS_INFO("Failed to get Phase Shift Parameter");
  }
  ros::Publisher joint_1_pub = n.advertise<std_msgs::Float64>("/snake/joint1_position_controller/command", 1000);
  ros::Publisher joint_2_pub = n.advertise<std_msgs::Float64>("/snake/joint2_position_controller/command", 1000);
  ros::Publisher joint_3_pub = n.advertise<std_msgs::Float64>("/snake/joint3_position_controller/command", 1000);
  ros::Publisher joint_4_pub = n.advertise<std_msgs::Float64>("/snake/joint4_position_controller/command", 1000);
  ros::Publisher joint_5_pub = n.advertise<std_msgs::Float64>("/snake/joint5_position_controller/command", 1000);
  ros::Publisher joint_6_pub = n.advertise<std_msgs::Float64>("/snake/joint6_position_controller/command", 1000);
  ros::Publisher joint_7_pub = n.advertise<std_msgs::Float64>("/snake/joint7_position_controller/command", 1000);
  ros::Publisher joint_8_pub = n.advertise<std_msgs::Float64>("/snake/joint8_position_controller/command", 1000);
  ros::Publisher joint_9_pub = n.advertise<std_msgs::Float64>("/snake/joint9_position_controller/command", 1000);

  ros::Rate loop_rate(1);

  int count = 0;
  while (ros::ok())
  {

    std_msgs::Float64 msg1,msg2,msg3,msg4,msg5,msg6,msg7,msg8,msg9;
    msg1.data = 5*sin(count);
    msg2.data = 5*sin(count+1*phase_shift);
    msg3.data = 5*sin(count+2*phase_shift);
    msg4.data = 5*sin(count+3*phase_shift);
    msg5.data = 5*sin(count+4*phase_shift);
    msg6.data = 5*sin(count+5*phase_shift);
    msg7.data = 5*sin(count+6*phase_shift);
    msg8.data = 5*sin(count+7*phase_shift);
    msg9.data = 5*sin(count+8*phase_shift);

    ROS_INFO("Joint1: %f",msg1.data);
    ROS_INFO("Joint2: %f",msg1.data);
    ROS_INFO("Joint3: %f",msg3.data);
    ROS_INFO("Joint4: %f",msg4.data);
    ROS_INFO("Joint5: %f",msg5.data);
    ROS_INFO("Joint6: %f",msg6.data);
    ROS_INFO("Joint7: %f",msg7.data);
    ROS_INFO("Joint8: %f",msg8.data);
    ROS_INFO("Joint9: %f",msg9.data);

    joint_1_pub.publish(msg1);
    joint_2_pub.publish(msg2);
    joint_3_pub.publish(msg3);
    joint_4_pub.publish(msg4);
    joint_5_pub.publish(msg5);
    joint_6_pub.publish(msg6);
    joint_7_pub.publish(msg7);
    joint_8_pub.publish(msg8);
    joint_9_pub.publish(msg9);
    ros::spinOnce();
    loop_rate.sleep();

    ++count;
  }


  return 0;
}