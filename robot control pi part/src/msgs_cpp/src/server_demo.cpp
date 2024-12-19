#include <ros/ros.h>
#include <iostream>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <std_msgs/Float32MultiArray.h>
 
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
 
using namespace std;
 
typedef actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> Server;
vector<vector<double>> _Pos_all;
void _cout_vec();

std::basic_string<char> Link1;
std::basic_string<char> Link2;
std::basic_string<char> Link3;
std::basic_string<char> Link4;
std::basic_string<char> Link5;
std::basic_string<char> Link6;
 
/* 收到action的goal后调用的回调函数 */
void execute(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal, Server* as)
{
	vector<double> row(6);
	
	// ros::Rate rate(1);
	ROS_INFO("receive start!");
	Link1 = goal->trajectory.joint_names[0];
	Link2 = goal->trajectory.joint_names[1];
	Link3 = goal->trajectory.joint_names[2];
   	Link4 = goal->trajectory.joint_names[3];
	Link5 = goal->trajectory.joint_names[4];
	Link6 = goal->trajectory.joint_names[5];

	for (int j = 0; j <goal->trajectory.points.size();j++)
	{
		for (int i = 0; i < 6; i++)
		{
			row[i] = goal->trajectory.points[j].positions[i];
		}
		_Pos_all.push_back(row);
	}
	as->setSucceeded();

	_cout_vec();
}

/* 主函数主要用于动作订阅和套接字通信 */
int main(int argc, char** argv)
{
	ros::init(argc, argv, "real_robot_server");
	ros::NodeHandle nh;
	// 定义一个服务器
	Server server(nh, "br_robot/follow_joint_trajectory", boost::bind(&execute, _1, &server), false);

	// 服务器开始运行
	server.start();
	ROS_INFO("server start!");
	ros::spin(); 
}
 
void _cout_vec()
{
	for (int i = 0; i < _Pos_all.size(); i++)
	{
		printf("goal[%d]=[%f,%f,%f,%f,%f,%f]\n",i,_Pos_all[i][0],_Pos_all[i][1],_Pos_all[i][2],_Pos_all[i][3],_Pos_all[i][4],_Pos_all[i][5]);
	}
}