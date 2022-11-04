#ifndef MISSIONEXECUTOR_H
#define MISSIONEXECUTOR_H

#include "MissionPlanner.h"
#include "Common.h"

#include <json/json.h>
#include <cpr/cpr.h>
#include <string>
#include <iostream>



namespace YJ
{
class MissionPlanner;
class MissionExecutor
{
public:
    MissionExecutor();

    bool AddTask(std::string& start, std::string& goal);

    void Run();

private:
    // 任务规划器
    MissionPlanner* mpMissionPlanner;
}; 
}

#endif