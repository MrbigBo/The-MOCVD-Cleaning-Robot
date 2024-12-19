#include <ros/ros.h>
#include <iostream>
#include <actionlib/server/simple_action_server.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <std_msgs/Float32MultiArray.h>
 #include <std_msgs/String.h>
 #include <serial/serial.h>

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


int _sub_flag(void);
void _cout_vec(void);
void _ser_sub(void);
void _ser_pub_head(unsigned int  len_arr );
void _ser_pub_data(std::vector <std::vector<double>> _Pos);
void _ser_pub_tail(void);
void double2uint(double pub_intput , uint8_t *char_array);
void execute(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal, Server* as);

serial::Serial _ser_demo;

int main(int argc, char** argv)
{
	ros::init(argc, argv, "real_robot_server_stm");
	
	//Node_1
	ros::NodeHandle node_f;
	Server server(node_f, "br_robot/follow_joint_trajectory", boost::bind(&execute, _1, &server), false);
	//Node_2
	ros::NodeHandle node_p;    

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
void _ser_pub_head(unsigned int len_arr )
{
	ROS_INFO("_ser_pub_head start!");
	uint8_t len_array = len_arr + '0';
	_ser_demo.write(&len_array, 1);
	while (!_sub_flag());
	ROS_INFO("_ser_pub_head_1 start!");
	_ser_demo.write(&len_array, 1);
	while (!_sub_flag());
}
void _ser_pub_data(std::vector <std::vector<double>> _Pos)
{
	ROS_INFO("_ser_pub_data start!");
	for (size_t i = 0; i < _Pos.size(); i++)
	{
		for (size_t j = 0; j < 6; j++)
		{
			//1byte symbol 5byte date
			uint8_t char_array[5];
			double2uint(_Pos[i][j] , char_array);
			_ser_demo.write(char_array, 5);
		}
	}
}
void _ser_pub_tail()
{
	ROS_INFO("_ser_pub_tail start!");
	uint8_t data_tail = 'a';
	_ser_demo.write(&data_tail, 1);
	while (!_sub_flag());
}
void _ser_sub()
{
	ROS_INFO("_ser_sub start!");
	size_t n = _ser_demo.available();
	if(n!=0)
	{
		uint8_t buffer_sub[1024];
		n = _ser_demo.read(buffer_sub, n);
		for(int i=0; i<n; i++)
		{
		std::cout << std::hex << (buffer_sub[i] & 0xff) << " ";
		}
		std::cout << std::endl;
	}
}
int _sub_flag()
{
	while(! _ser_demo.available());
	_ser_demo.flushInput();
//	printf("%d",flag);
	return 1;
}

void _cout_vec()
{
	for (int i = 0; i < _Pos_all.size(); i++)
	{
		float a_0 = 180*_Pos_all[i][0]/M_PI;
		float a_1 = 180*_Pos_all[i][1]/M_PI;
		float a_2 = 180*_Pos_all[i][2]/M_PI;
		float a_3 = 180*_Pos_all[i][3]/M_PI;
		float a_4 = 180*_Pos_all[i][4]/M_PI;
		float a_5 = 180*_Pos_all[i][5]/M_PI;
		printf("goal[%d]=[%f,%f,%f,%f,%f,%f]\n",i,a_0,a_1,a_2,a_3,a_4,a_5);
	}
}

void double2uint(double pub_intput , uint8_t *char_array)
{
    *char_array = (pub_intput >0)?2:1;
    pub_intput=abs(pub_intput);

    int times = 4;
    while(times--)
    {
		char_array++;
		*char_array = pub_intput;
		pub_intput = (pub_intput - *char_array)*10;
    }
}

void execute(const control_msgs::FollowJointTrajectoryGoalConstPtr& goal, Server* as)
{
	std::vector<double> row(6);
	
	// ros::Rate rate(1);
	ROS_INFO("receive start!");
	for (int j = 0; j <goal->trajectory.points.size();j++)
	{
		for (int i = 0; i < 6; i++)
		{
			row[i] = goal->trajectory.points[j].positions[i];
		}
		_Pos_all.push_back(row);
	}
	_cout_vec();	
	as->setSucceeded();

	_ser_pub_head(_Pos_all.size());
	_ser_pub_data(_Pos_all);
	_ser_pub_tail();
}



