#include <mutex>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "SystemController.h"

namespace YJ
{
    SystemController::SystemController(ros::NodeHandle& nh)
    {
        cmd_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    }

    void SystemController::AGVStop()
    {
        // AGV停止，向底盘发送速度0
        AGVVel_pub.linear.x = 0;
        AGVVel_pub.angular.z = 0;
        cmd_pub.publish(AGVVel_pub);
    }

    void SystemController::SetAGVSpeed(double AGVLinear, double AGVAngular)
    {
        // 设置AGV的速度，可以直接接收UDP得到的速度数据
        std::unique_lock<std::mutex> lock(mMutexAGVVel);
        AGVVel_pub.linear.x = AGVLinear;
        AGVVel_pub.angular.z = AGVAngular;
        cmd_pub.publish(AGVVel_pub);
    }

    void SystemController::UAVHover()
    {
        // 向无人机发送悬停指令
    }

    void SystemController::UAVLanding()
    {
        // 向无人机发送降落指令
    }

    void SystemController::Run()
    {
        
        std::cout << "Main thread is to control AGV and UAV" << std::endl;
        ros::Rate looprate(50);
        while(ros::ok())
        {
            // 发布底盘数据
            {
                std::unique_lock<std::mutex> lock(mMutexAGVVel);

                AGVVel_pub.linear.x = AGV_Vel.Linear;
                AGVVel_pub.angular.z = AGV_Vel.Angular;
                cmd_pub.publish(AGVVel_pub);
            }
            ros::spinOnce();
            looprate.sleep();
        }
    }
}