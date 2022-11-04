#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <mutex>

namespace YJ
{
class UDPServer;
class System;
class ChassisSerialPort;

// 导航电脑传过来的数据
enum UDPMessage : unsigned char
{
    Invalid = 0,
    Linear,
    Angular,
    Charger_Switch,
    Final_Pose,
    Power_State,
    Button_Stop,
    Charge_State,
    Motor_Lock_State,
    Position,
    Rotation,
    Twist,
    Percent,
    Voltage,
    Current
};

// AGV位置信息
struct AGVPos
{
    float AGVX;
    float AGVY;
    float AGVYaw;
};

// 小车速度
struct AGVVel
{
    float Linear;
    float Angular;
};

// 任务点信息
struct MissionPoint
{
    // 起始库位点，终点库位点和高度信息
    std::string start;
    std::string goal;
    float height;
};

// 底盘小车数据回传
struct AGVInfo
{
    int Vx;
    float Vz;
    float AccX;
    float AccY;
    float AccZ;
    float GyrX;
    float GyrY;
    float GyrZ;
    int16_t Voltage;
    int16_t State;
    int16_t Light12;
    int16_t Light34;
};

// 底盘回传的AGV信息
extern AGVInfo AGV_Info;

// 小车位置信息
extern AGVPos AGV_Pos;

// 小车速度信息
extern AGVVel AGV_Vel;

// 充电开关
extern bool ChargerSwitch;

// UAV完成调整的标志位
extern bool UAVAdjustmentFinshFlag;

// 小车信息 锁
extern std::mutex mMutexAGVInfo;

// 小车速度 锁
extern std::mutex mMutexAGVVel;

// 小车位置 锁
extern std::mutex mMutexAGVPos;

// 调整标志位锁
extern std::mutex mMutexUAVAdjustmentFlag;



}


#endif