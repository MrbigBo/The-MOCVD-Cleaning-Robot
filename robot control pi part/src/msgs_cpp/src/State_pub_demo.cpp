#include <ros/ros.h>
#include <iostream>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/String.h>
#include <serial/serial.h>

#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

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

typedef actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> Server;
std::vector <std::vector<double>> _Pos_all;

void ser_config(void);
int _sub_flag( void );
void combine_msg( unsigned int len_arr );
void msg_dti( double pub_intput , uint8_t *char_array );
void ultimate_msg(unsigned int len_arr , std::vector <std::vector<double>> _Pos);

void execute(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal, Server* as);

serial::Serial _ser_demo;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "real_robot_server_ros");
	
	//Node_1
	ros::NodeHandle node_f;
	Server server(node_f, "br_robot/follow_joint_trajectory", boost::bind(&execute, _1, &server), false);
	//Node_2
	ros::NodeHandle node_p;    
    
    ser_config();
    try
    {
        _ser_demo.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
    }                          
    if(_ser_demo.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyCH341USB0 is opened.");
    }

	server.start();
	ROS_INFO("server start!");
	ros::spin(); 
}

void ser_config( void )
{
    serial::Timeout _ser_to = serial::Timeout::simpleTimeout(1000); 
	serial::parity_t _ser_pt = serial::parity_t::parity_none; 
	serial::bytesize_t _ser_bt =  serial::bytesize_t::eightbits; 
	serial::flowcontrol_t _ser_ft = serial::flowcontrol_t::flowcontrol_none; 
	serial::stopbits_t _ser_st = serial::stopbits_t::stopbits_one;

	_ser_demo.setPort("/dev/ttyCH341USB0");
    _ser_demo.setBaudrate(115200);
    _ser_demo.setTimeout(_ser_to);
    _ser_demo.setParity(_ser_pt); 
    _ser_demo.setBytesize(_ser_bt);
    _ser_demo.setFlowcontrol(_ser_ft);
    _ser_demo.setStopbits(_ser_st);
}
int _sub_flag( void )
{
	while(! _ser_demo.available());
	_ser_demo.flushInput();
	return 1;
}
void combine_msg( unsigned int len_arr )
{
    ROS_INFO("_ser_pub_head start!");
	uint8_t len_array = len_arr + '0';
	_ser_demo.write(&len_array, 1);
	while (!_sub_flag());
	ROS_INFO("_ser_pub_head_1 start!");
	_ser_demo.write(&len_array, 1);
	while (!_sub_flag());
}
void msg_dti( double pub_intput , uint8_t *char_array )
{
    *char_array = (pub_intput >0)?2:1;
    pub_intput=abs(pub_intput);

    int length = 4;
    while(length--)
    {
		char_array++;
		*char_array = pub_intput;
		pub_intput = (pub_intput - *char_array)*10;
    }
}
void ultimate_msg(unsigned int len_arr , std::vector <std::vector<double>> _Pos)
{
    //head'
    ROS_INFO("_pub_head Finish!");
    uint8_t len_array = len_arr + '0';
	_ser_demo.write(&len_array, 1);
	//while (!_sub_flag());
	_ser_demo.write(&len_array, 1);
	//while (!_sub_flag());
    //msg'
    for (size_t i = 0; i < _Pos.size(); i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			//1byte symbol 5byte date
			uint8_t char_array[5];
			msg_dti(_Pos[i][j] , char_array);
			_ser_demo.write(char_array, 5);
		}
	}
    ROS_INFO("_pub_data Finish!");
    //tail'
    uint8_t data_tail = 'a';
	_ser_demo.write(&data_tail, 1);
	//while (!_sub_flag());
}
void execute(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal, Server* as)
{
    as->setSucceeded();
    ros::NodeHandle node_s;
    ros::Publisher joint_state_pub = node_s.advertise<sensor_msgs::JointState>("/br_robot/joint_states",1);

	sensor_msgs::JointState joint_state_data;
    joint_state_data.name.resize(6);
    joint_state_data.position.resize(6);
    ros::Rate loop_rate(10);

    std::vector<double> row(6);

    for (int j = 0; j <goal->trajectory.points.size();j++)
    {
        for (int i = 0; i < 6; i++)
        {
            row[i] = goal->trajectory.points[j].positions[i];
        }
        _Pos_all.push_back(row);
    }

    ultimate_msg(_Pos_all.size() , _Pos_all);

    for (int j = 0; j <goal->trajectory.points.size();j++)
    {
        joint_state_data.header.stamp = ros::Time::now();

        joint_state_data.name[0] = "Joint_1";
        joint_state_data.name[1] = "Joint_2";
        joint_state_data.name[2] = "Joint_3";
        joint_state_data.name[3] = "Joint_4";
        joint_state_data.name[4] = "Joint_5";
        joint_state_data.name[5] = "Joint_6";

        joint_state_data.position[0] =   goal->trajectory.points[j].positions[0];
        joint_state_data.position[1] =   goal->trajectory.points[j].positions[1];
        joint_state_data.position[2] =   goal->trajectory.points[j].positions[2];
        joint_state_data.position[3] =   goal->trajectory.points[j].positions[3];
        joint_state_data.position[4] =   goal->trajectory.points[j].positions[4];
        joint_state_data.position[5] =   goal->trajectory.points[j].positions[5];

        joint_state_pub.publish(joint_state_data);

        loop_rate.sleep();
    }
    
    //

}



