#include <math.h>
#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/robot_trajectory/robot_trajectory.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "demo02");
	ros::AsyncSpinner spinner(1);
	spinner.start();

    moveit::planning_interface::MoveGroupInterface arm("rbd_src_1");

    //获取终端link的名称
    std::string end_effector_link = arm.getEndEffectorLink();

    //设置目标位置所使用的参考坐标系
    std::string reference_frame = "base_link";
    arm.setPoseReferenceFrame(reference_frame);

    //当运动规划失败后，允许重新规划
    arm.allowReplanning(true);

    //设置位置(单位：米)和姿态（单位：弧度）的允许误差
    arm.setGoalPositionTolerance(0.001);
    arm.setGoalOrientationTolerance(0.01);

    //设置允许的最大速度和加速度
    arm.setMaxAccelerationScalingFactor(10);
    arm.setMaxVelocityScalingFactor(5);

    // 控制机械臂先回到初始化位置
    arm.setNamedTarget("Home_1");
    arm.move();
    sleep(1);

    geometry_msgs::Pose target_pose;
    target_pose.orientation.x = 0;
    target_pose.orientation.y = 0;
    target_pose.orientation.z = 1;
    target_pose.orientation.w = 1.570;

    target_pose.position.x = 1.400000;
    target_pose.position.y = 0.0;
    target_pose.position.z = 1.400000;

    arm.setPoseTarget(target_pose);
    arm.move();

    // 控制机械臂先回到初始化位置
    // arm.setNamedTarget("Home_2");
    // arm.move();
    // sleep(1);

    arm.setNamedTarget("Home_1");
    arm.move();
    sleep(1);


	ros::shutdown(); 
	return 0;
}
