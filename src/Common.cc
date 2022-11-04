#include "Common.h"


namespace YJ
{

AGVInfo AGV_Info;
AGVPos AGV_Pos;
AGVVel AGV_Vel;
bool ChargerSwitch;
bool UAVAdjustmentFinshFlag;
// 小车信息 锁
std::mutex mMutexAGVInfo;

// 小车速度 锁
std::mutex mMutexAGVVel;

// 小车位置 锁
std::mutex mMutexAGVPos;

std::mutex mMutexUAVAdjustmentFlag;
}

