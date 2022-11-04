#include "MissionPlanner.h"

#include <iostream>

namespace YJ
{
    MissionPlanner::MissionPlanner()
    {
        std::cout << "This is a MissionPlanner!!!" << std::endl;
    }

    std::queue<MissionPoint> MissionPlanner::GetMissionPointQueue()
    {
        std::queue<MissionPoint> MissonPointQueue;
        return MissonPointQueue;
    }
}