#include <ros/ros.h>
#include <iostream>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/String.h>
#include <serial/serial.h>

#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <msgs_cpp/Joint_val.h>

#include <sstream>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void chatterCallback(const msgs_cpp::Joint_val& ptr)
{
    float joi1 = 1.000;

    ros::NodeHandle node_RB_STATES;
    ros::Publisher pub = node_RB_STATES.advertise<sensor_msgs::JointState>("/br_robot/joint_states",1);

    sensor_msgs::JointState joint_state_data;
    joint_state_data.name.resize(6);
    joint_state_data.position.resize(6);

    ROS_INFO("pub start!");
    joint_state_data.header.stamp = ros::Time::now();

    joint_state_data.name[0] = "Joint_1";
    joint_state_data.name[1] = "Joint_2";
    joint_state_data.name[2] = "Joint_3";
    joint_state_data.name[3] = "Joint_4";
    joint_state_data.name[4] = "Joint_5";
    joint_state_data.name[5] = "Joint_6";

    joint_state_data.position[0] =  joi1;
    joint_state_data.position[1] =  joi1;
    joint_state_data.position[2] =  joi1;
    joint_state_data.position[3] =  joi1;
    joint_state_data.position[4] =  joi1;
    joint_state_data.position[5] =  joi1;

    pub.publish(joint_state_data);

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ROS_GUI_SUB");
	
	//Node_1
	ros::NodeHandle node_GUI;
    ros::Subscriber sub = node_GUI.subscribe( "chatter", 1000, chatterCallback );

    ros::NodeHandle node_p;    

    ros::spin( );
    return 0;
}
