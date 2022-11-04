#ifndef MISSIONPLANNER_H
#define MISSIONPLANNER_H

#include <queue>

#include "Common.h"

namespace YJ
{

class MissionPlanner
{
public:
    MissionPlanner();

    std::queue<MissionPoint> GetMissionPointQueue();
};
}

#endif