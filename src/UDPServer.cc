#include "UDPServer.h"
#include "System.h"
#include <iostream>
#include <string>


namespace YJ
{
UDPServer::UDPServer(const int port) : mSocket(mIoContext, udp::endpoint(udp::v4(), port))
{
    if(mSocket.is_open())
    {
        std::cout << "Init Socket Successfully" << std::endl;
    }
    else 
    {
        std::cerr << "Fail to Init Socket" << std::endl;
    }
}

UDPServer::~UDPServer()
{
    if(mSocket.is_open())
    {
        mSocket.cancel();
        mSocket.close();
        std::cout << "Socket is closed" << std::endl;
    }
}

void UDPServer::StartRecvUDPData()
{
    // 套接字异步接收数据
    mSocket.async_receive_from(
        boost::asio::buffer(mRecvBuff), mRemoteEndPoint,
        [this](boost::system::error_code err, std::size_t bytes_recvd)
        {
            // std::cout << "1" << std::endl;
            if(!err && bytes_recvd > 0) 
            {
                // 解析json数据
                // std::cout << "Begin to Receive Data!" << std::endl;
                // boost::property_tree::ptree RecvPtree;
                // std::string msg(mRecvBuff, bytes_recvd);
                // std::stringstream ss(msg);
                // boost::property_tree::read_json(ss, RecvPtree);
                // for(auto it = RecvPtree.begin(); it != RecvPtree.end(); it++)
                // {
                //     std::cout << it->first << std::endl;
                //     StartSendUDPData(it->first,RecvPtree);
                // }
                // // 继续接收数据
                // std::cout << "continue" << std::endl;
                Json::Value val;
                Json::Reader reader;

                // 解析json数据
                if(reader.parse(mRecvBuff, val)) {
                    // std::cout << val.toStyledString() << std::endl;

                    Json::Value::Members member = val.getMemberNames();

                    std::string str = member[0];

                    StartSendUDPData(str, val);
                }

            } 
            else 
            {
                std::cerr << "async_receive error" << std::endl;
            }
            StartRecvUDPData();
        });
}

void UDPServer::StartSendUDPData(const std::string& message, Json::Value& val)
{
    Json::Value jsonwriter;
    Json::StyledWriter writer;
    // 根据接收类型发数据
    switch (ResolveMessage(message))
    {
    case UDPMessage::Linear:
        // 线速度
        {
            unique_lock<std::mutex> lock(mMutexAGVVel);
            AGV_Vel.Linear = val["Linear"].asFloat();
            std::cout << "Linear: " << AGV_Vel.Linear << std::endl;
            break;
        }
    case UDPMessage::Angular:
        // 角速度
        {
            unique_lock<std::mutex> lock(mMutexAGVVel);
            AGV_Vel.Angular = val["Angular"].asFloat();
            std::cout << "Angular: " << AGV_Vel.Angular << std::endl;
            break;
        }
    case UDPMessage::Charger_Switch:
        // 充电开关
        ChargerSwitch = val["Charger_Switch"].asBool();
        break;
    case UDPMessage::Final_Pose:
        // 小车定位位置 
        {
            unique_lock<std::mutex> lock(mMutexAGVPos);
            const Json::Value FinalPose = val["Final_Pose"];
            AGV_Pos.AGVX = FinalPose[0].asFloat();
            AGV_Pos.AGVY = FinalPose[1].asFloat();
            AGV_Pos.AGVYaw = FinalPose[2].asFloat();
            break;
        }
    case UDPMessage::Power_State:
        // 电源开关
        if(val["Power_State"].asInt() == 0) {
            jsonwriter["Power_State"] = true;
        } 
        break;
    case UDPMessage::Button_Stop:
        // 急停按钮
        if(val["Button_Stop"].asInt() == 0) {
            jsonwriter["Button_Stop"] = false;
        }
        break;
    case UDPMessage::Charge_State:
        // 充电状态
         if(val["Charge_State"].asInt() == 0) {
            jsonwriter["Charge_State"] = false;
        }
    case UDPMessage::Motor_Lock_State:
        // 电机
        if(val["Motor_Lock_State"].asInt() == 0) {
            jsonwriter["Motor_Lock_State"] = false;
        }
        break;
    case UDPMessage::Position:
        // 小车位置
        {
            unique_lock<std::mutex> lock(mMutexAGVPos);
            if(val["Position"].asInt() == 0) {
                jsonwriter["Position"].append(AGV_Pos.AGVX);
                jsonwriter["Position"].append(AGV_Pos.AGVY);
            }
            break;
        }
    case UDPMessage::Rotation:
        // 小车偏航角
        {
            unique_lock<std::mutex> lock(mMutexAGVPos);
            if(val["Rotation"].asInt() == 0) {
                jsonwriter["Rotation"] = AGV_Pos.AGVYaw;
            }
            break;
        }
    case UDPMessage::Twist:
        // 小车线速度和角速度
        {
            unique_lock<std::mutex> lock(mMutexAGVInfo);
            if(val["Twist"].asInt() == 0) {
                jsonwriter["Twist"].append((float)AGV_Info.Vx / 1000.0);
                jsonwriter["Twist"].append((float)AGV_Info.Vz);
            }
            break;
        }
    case UDPMessage::Percent:
        // 小车电量
        if(val["Percent"].asInt() == 0) {
            jsonwriter["Percent"] = 50.0;
        }
        break;
    case UDPMessage::Voltage:
        //  小车电压
        {
            unique_lock<std::mutex> lock(mMutexAGVInfo);
            if(val["Voltage"].asInt() == 0) {
                jsonwriter["Voltage"] = (float)AGV_Info.Voltage / 10.0;
            }
            break;
        }
    case UDPMessage::Current:
        // 小车电流
       if(val["Current"].asInt() == 0) {
            jsonwriter["Current"] = 20.0;
        }
        break;
    default:
        break;
    }
    std::string SendBuf = writer.write(jsonwriter);

    mSocket.send_to(boost::asio::buffer(SendBuf), mRemoteEndPoint);
}

void UDPServer::SetChassisSerialPort(ChassisSerialPort* pChassisSerialPort)
{
    mpChassisSerialPort = pChassisSerialPort;
}

UDPMessage UDPServer::ResolveMessage(std::string str)
{

    if(str == "Linear")           return UDPMessage::Linear;
    if(str == "Angular")          return UDPMessage::Angular;
    if(str == "Charger_Switch")   return UDPMessage::Charger_Switch;
    if(str == "Final_Pose")       return UDPMessage::Final_Pose;
    if(str == "Power_State")      return UDPMessage::Power_State;
    if(str == "Button_Stop")      return UDPMessage::Button_Stop;
    if(str == "Charge_State")     return UDPMessage::Charge_State;
    if(str == "Motor_Lock_State") return UDPMessage::Motor_Lock_State;
    if(str == "Position")         return UDPMessage::Position;
    if(str == "Rotation")         return UDPMessage::Rotation;
    if(str == "Twist")            return UDPMessage::Twist;
    if(str == "Percent")          return UDPMessage::Percent;
    if(str == "Voltage")          return UDPMessage::Voltage;
    if(str == "Current")          return UDPMessage::Current;
    return UDPMessage::Invalid;
}

void UDPServer::Run()
{
    try {
        // 接收数据
        StartRecvUDPData();
        mIoContext.run();
    } catch (const std::exception& ex){
        std::cerr << ex.what() << std::endl;
    }
}
}