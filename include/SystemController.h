#ifndef SYSTEMCONTROLLER_H
#define SYSTEMCONTROLLER_H

#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>

#include "Common.h"

namespace YJ
{

class SystemController
{
public:
    SystemController(ros::NodeHandle& nh);

    // 无人车暂停
    void AGVStop();

    // 设置AGV的速度
    void SetAGVSpeed(double AGVLinear, double AGVAngular);

    // 发布AGV的位置信息
    void PublishAGVPos();

    // 无人机悬停
    void UAVHover();

    // 无人机降落
    void UAVLanding();

    void Run();

public:

    enum AGVStatus
    {
        Stop,
        GoStraight,
        Turn,
    } eAGVStatus;

    enum UAVStatus
    {
        DroneHover,
        DroneLanding,
        DroneFlight,
    } eUAVStatus;
private:
    ros::Publisher cmd_pub;

    ros::Publisher pos_pub;
    
    geometry_msgs::Twist AGVVel_pub;

    geometry_msgs::Point AGVPos_pub;

};
}

#endif