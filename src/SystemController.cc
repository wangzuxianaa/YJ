#include <mutex>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>

#include "SystemController.h"

namespace YJ
{
    SystemController::SystemController(ros::NodeHandle& nh)
    {
        cmd_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

        pos_pub = nh.advertise<geometry_msgs::Point>("/agv_pos", 10);
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
        AGVVel_pub.linear.x = AGVLinear;
        AGVVel_pub.angular.z = AGVAngular;
        cmd_pub.publish(AGVVel_pub);
    }

    void SystemController::PublishAGVPos()
    {
        std::unique_lock<std::mutex> lock(mMutexAGVPos);
        AGVPos_pub.x = AGV_Pos.AGVX;
        AGVPos_pub.y = AGV_Pos.AGVY;
        AGVPos_pub.z = AGV_Pos.AGVYaw;
        pos_pub.publish(AGVPos_pub);
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
            //  // 无人机调整完成 小车开始移动
            // if(UAVAdjustmentFinshFlag) 
            // {
            //     sleep(2);
            //     SetAGVSpeed(AGV_Vel.Linear, AGV_Vel.Angular);
            // }
            // // 没有调整完成
            // else
            // {
            //     // 小车停止
            //     AGVStop();
            // }
            // 特殊情形
            // if(1)
            // {
            //     AGVStop();          
            // }
            {
                std::unique_lock<std::mutex> lock(mMutexAGVVel);
                SetAGVSpeed(AGV_Vel.Linear, 0.2*AGV_Vel.Angular);
            }
            PublishAGVPos();
            ros::spinOnce();
            looprate.sleep();
        }
    }
}