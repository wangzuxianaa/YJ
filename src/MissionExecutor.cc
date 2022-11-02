#include "MissionExecutor.h"

// #include <cpr/cpr.h>
#include <json/json.h>

namespace YJ
{
    MissionExecutor::MissionExecutor():mpMissionPlanner()
    {
        // 传送参数 路径规划器
    }

    void MissionExecutor::AddTask(std::string& start, std::string& goal)
    {
        
    }

    void MissionExecutor::Run()
    {
        // 任务执行器
        // 第一步 获取任务列表 queue

        // 第二步 addtask 任务开始
        // while(queue.size())
        // {

        // }
        // 什么时候下发下一个规划，需要AGV和UAV状态没问题，且跟随上就pop出队列并addTask()，标志位为调整完成的状态话，就需要pop和addTask()，没有调整完成的话需要就不pop新的任务点
    }
} 