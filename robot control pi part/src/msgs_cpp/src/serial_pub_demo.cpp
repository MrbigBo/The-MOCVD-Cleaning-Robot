#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <iostream>
#include <string>
#include <sstream>

void _Ser_set_port()
{

}

int _Ser_pub_port(int argc, char** argv);

int main(int argc, char** argv)
{
    ros::init(argc,argv,"Serial_pub_port");
    ros::NodeHandle sP;

    serial::Serial _ser_demo;
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

    ros::Rate loop_rate(1);

    while(ros::ok())
    {
        //PUB
        // uint8_t buffer_pub[10] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,0.0};
        // _ser_demo.write(buffer_pub, 10);

        //SUB
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
        loop_rate.sleep();
    }

    return 0;
}