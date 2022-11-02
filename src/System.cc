#include "System.h"

#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <YJI/agv1.h>

namespace YJ
{
    System::System()
    {


        // 创建UDP接收线程，接收导航电脑的数据
        mpUDPServer = new UDPServer(9090);


        mptUDPServer = new thread(&YJ::UDPServer::Run,
                            mpUDPServer);


        agvmsg_sub = nh.subscribe<YJI::agv1>("agv_info", 10, &YJ::System::AGVInfoHandle, this);

        // // 系统检测电池状态信息
        // mpSystemMonitor = new SystemMonitor("/dev/pts/0", 115200);

        // mptSystemMonitor = new thread(&YJI::SystemMonitor::Run,
        //                                 mpSystemMonitor);

        mpSystemController = new SystemController(nh);


    }

    void System::AGVInfoHandle(const YJI::agv1ConstPtr& AGVInfoMsg)
    {
        unique_lock<std::mutex> lock(mMutexAGVInfo);
        AGV_Info.AccX = AGVInfoMsg->AccX;
        AGV_Info.AccY = AGVInfoMsg->AccY;
        AGV_Info.AccZ = AGVInfoMsg->AccZ;
        AGV_Info.GyrX = AGVInfoMsg->GyrX;
        AGV_Info.GyrY = AGVInfoMsg->GyrY;
        AGV_Info.GyrZ = AGVInfoMsg->GyrZ;
        AGV_Info.Light12 = AGVInfoMsg->Light12;
        AGV_Info.Light34 = AGVInfoMsg->Light34;
        AGV_Info.State = AGVInfoMsg->State;
        AGV_Info.Voltage = AGVInfoMsg->Voltage;
        AGV_Info.Vx = AGVInfoMsg->Vx;
        AGV_Info.Vz = AGVInfoMsg->Vz;
    }

    void System::Run()
    {
        // 控制
        mpSystemController->Run();
    }
    

    void System::Shutdown()
    {

    }
} // namespace YJI
