#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <mutex>
#include <json/json.h>
#include "Common.h"

using boost::asio::ip::udp;
using boost::asio::serial_port;

namespace YJ
{
class Common;
class System;
class ChassisSerialPort;
 
class UDPServer 
{
public:
    UDPServer(const int port);

    ~UDPServer();

    void StartRecvUDPData();

    void StartSendUDPData(const std::string& message, Json::Value& val);

    void SetChassisSerialPort(ChassisSerialPort* pChassisSerialPort);

    // 请求中止线程
    void RequestFinish();

    void Run();

protected:
    UDPMessage ResolveMessage(std::string str);


private:

    boost::asio::io_context mIoContext;

    // UDP套接字
    udp::socket mSocket;

    // 客户端信息
    udp::endpoint mRemoteEndPoint;


    // //  电源开关 锁
    // std::mutex mMutexChargerSwitch;

    // UDPMessage meMessage;

    // boost::asio::io_context mIoContext;

    ChassisSerialPort* mpChassisSerialPort;

    char mRecvBuff[1024];
};
}

#endif
