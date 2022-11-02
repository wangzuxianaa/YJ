#include <ros/ros.h>
#include <YJI/agv1.h>

#include "Common.h"
#include "System.h"
#include "UDPServer.h"


int main(int argc, char** argv)
{
    ros::init(argc, argv, "YJI");

    YJ::System YJISystem;

    YJISystem.Run();
    
}