#include <math.h>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>

void arm_config();
void set_aim();

int main(int argc, char **argv)
{
    ros::init(argc ,argv , "Demo_wash");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    moveit::planning_interface::MoveGroupInterface arm("rbd_src_1");
    std::string end_effector_link = arm.getEndEffectorLink();

    std::string reference_frame = "base_link";
    arm.setPoseReferenceFrame(reference_frame);
    arm.allowReplanning(true);
    arm.setGoalPositionTolerance(0.001);
    arm.setGoalOrientationTolerance(0.01);
    arm.setMaxAccelerationScalingFactor(10);
    arm.setMaxVelocityScalingFactor(5);

    arm.setNamedTarget("Home_2");
    arm.move();
    sleep(1);

    // geometry_msgs::Pose target_pose;
    // target_pose.orientation.x = 0;
    // target_pose.orientation.y = 0;
    // target_pose.orientation.z = 0;
    // target_pose.orientation.w = 0;

    // target_pose.position.x = 1.100;
    // target_pose.position.y = 0.0;
    // target_pose.position.z = 1.000;

    // arm.setPoseTarget(target_pose);
    // arm.move();
    // sleep(1);

    geometry_msgs::Pose target_pose_1;
    target_pose_1.orientation.x = 0;
    target_pose_1.orientation.y = 1;
    target_pose_1.orientation.z = 0;
    target_pose_1.orientation.w = 0;

    target_pose_1.position.x = 1.100;
    target_pose_1.position.y = 0.0;
    target_pose_1.position.z = 1.200;

    arm.setPoseTarget(target_pose_1);
    arm.move();
    sleep(1);

    // std::vector<geometry_msgs::Pose> waypoints;
    // waypoints.push_back(target_pose_1);

    // double centerA = target_pose_1.position.x;
    // double centerB = target_pose_1.position.y;
    // double radius = 0.1;

    // for(double th=0.0; th<=6.28; th=th+0.01)
    // {
    //     target_pose_1.position.x = centerA + radius * cos(th);
    //     target_pose_1.position.y = centerB + radius * sin(th);
    //     waypoints.push_back(target_pose_1);
    // }
    // waypoints.push_back(target_pose_1);
    // for(double th=6.28; th>=0; th=th-0.01)
    // {
    //     target_pose_1.position.x = centerA + radius * cos(th);
    //     target_pose_1.position.y = centerB + radius * sin(th);
    //     waypoints.push_back(target_pose_1);
    // }

    // moveit_msgs::RobotTrajectory trajectory;
	// const double jump_threshold = 0.0;
	// const double eef_step = 0.01;
	// double fraction = 0.0;
    // int maxtries = 100;   //最大尝试规划次数
    // int attempts = 0;     //已经尝试规划次数

    // while(fraction < 1.0 && attempts < maxtries)
    // {
    //     fraction = arm.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
    //     attempts++;
        
    //     if(attempts % 10 == 0)
    //         ROS_INFO("Still trying after %d attempts...", attempts);
    // }
    
    // if(fraction == 1)
    // {   
    //     ROS_INFO("Path computed successfully. Moving the arm.");

	//     // 生成机械臂的运动规划数据
	//     moveit::planning_interface::MoveGroupInterface::Plan plan;
	//     plan.trajectory_ = trajectory;

	//     // 执行运动
	//     arm.execute(plan);
    //     sleep(1);
    // }
    // else
    // {
    //     ROS_INFO("Path planning failed with only %0.6f success after %d attempts.", fraction, maxtries);
    // }

    // arm.setNamedTarget("Home_1");
    // arm.move();
    // sleep(1);

	ros::shutdown(); 
    return 0;
}

void arm_config()
{

}

void set_aim()
{

}

