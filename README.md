FWlib directory	            Functions
robot control pi part	      RRT path planning, T velocity planning, Path pruning, and so on.
robot control stm part	    CAN, Sensor data monitoring, Motor control, and so on.
robot control pi vis part	  Robot control visualization and Robot vision

ROS packages, including actionlib, message_generation, roscpp, movit_core, and others. 
Developed custom packages to implement critical functionalities such as RRT path planning and velocity planning.

The communication between hardware components primarily involves serial communication between ROS and STM, as well as CAN communication between STM and the driver. 
To enhance the reliability of the serial communication, we also incorporated CRC-16 checksum. 
