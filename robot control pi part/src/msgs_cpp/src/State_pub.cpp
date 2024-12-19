#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
  
  int main(int argc, char** argv)
  {
	ros::init(argc, argv, "real_joint_states");
    ros::NodeHandle node_s;
    ros::Publisher joint_state_pub = node_s.advertise<sensor_msgs::JointState>("/br_robot/joint_states",1);
    ros::Rate loop_rate(10);

    const double angle = M_PI/180;
    int i =-50;

    sensor_msgs::JointState joint_state_data;
    joint_state_data.name.resize(6);
    joint_state_data.position.resize(6);

    while (ros::ok())
    {
    ROS_INFO("receive start!");
    joint_state_data.header.stamp = ros::Time::now();
    joint_state_data.name[0] = "Joint_1";
    joint_state_data.name[1] = "Joint_2";
    joint_state_data.name[2] = "Joint_3";
    joint_state_data.name[3] = "Joint_4";
    joint_state_data.name[4] = "Joint_5";
    joint_state_data.name[5] = "Joint_6";

    joint_state_data.position[0] =  i * angle;
    joint_state_data.position[1] =  i * angle;
    joint_state_data.position[2] =  i * angle;
    joint_state_data.position[3] =  i * angle;
    joint_state_data.position[4] =  i * angle;
    joint_state_data.position[5] =  i * angle;

    if(i <= 50) i++;
    else i = -50;

    joint_state_pub.publish(joint_state_data);
    loop_rate.sleep();
    }

    return 0;
  }