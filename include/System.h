#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <thread>
#include <ros/ros.h>
#include <YJI/agv1.h>

#include "UDPServer.h"
#include "SystemController.h"

using namespace std;

namespace YJ
{

class UDPServer;
class SystemController;
class SystemMonitor;
class Common;

class System
{
public:
    System();

    void AGVInfoHandle(const YJI::agv1ConstPtr& AGVInfoMsg);

    void Run();
    
    void Shutdown();

public:

    ros::Subscriber agvmsg_sub;

    ros::NodeHandle nh;

    SystemController* mpSystemController;

    UDPServer* mpUDPServer;

    SystemMonitor* mpSystemMonitor;


    std::thread* mptUDPServer;

    std::thread* mptSystemMonitor;


};

}

#endif