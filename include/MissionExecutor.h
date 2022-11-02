#ifndef MISSIONEXECUTOR_H
#define MISSIONEXECUTOR_H

#include "MissionPlanner.h"

#include <string>


namespace YJ
{
class MissionPlanner;
class MissionExecutor
{
public:
    MissionExecutor();

    void AddTask(std::string& start, std::string& goal);

    void Run();

private:
    // 任务规划器
    MissionPlanner* mpMissionPlanner;
}; 
}

#endif