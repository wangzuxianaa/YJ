#include "MissionExecutor.h"




namespace YJ
{
    MissionExecutor::MissionExecutor():mpMissionPlanner()
    {
        // 传送参数 路径规划器
    }

    bool MissionExecutor::AddTask(std::string& start, std::string& goal)
    {
        Json::Value val;
        Json::StyledWriter writer;
        // 传递的Json数据
        val["start"] = start;
        val["goal"] = goal;
        val["start_action"] = 0;
        val["goal_action"] = 0;
        std::cout << val.toStyledString() << std::endl;
        Json::String RequestParam = writer.write(val);
        // 发起Post请求
        cpr::Response response = cpr::Post(cpr::Url{"http://192.168.3.220:9999/api/v1/task/add_task"},
                                            cpr::Header{{"Content-Type", "application/json"}},
                                            cpr::Body(RequestParam));
        std::cout << response.status_code << std::endl;

        // 需要解析json数据
        if(response.status_code == 200) 
        {
            std::cout << "下发任务成功" << std::endl;
            return true;
        }
        else
        {
            return false;
        }
        // 输出回应文本
        std::cout << response.text << std::endl;
    }

    void MissionExecutor::Run()
    {
        // while(true)
        // {
        //     // 获取任务列表
        //     if(UAVAdjustmentFinshFlag)
        //     {
        //         // 发布任务点
        //         std::string start, goal;
        //         AddTask(start, goal);
        //         UAVAdjustmentFinshFlag = false;
        //     }
        //     else
        //     {
        //         std::cout << "等待无人机调整" << std::endl;
        //     }
        // }
        /// 任务执行器
        // 第一步 获取任务列表 queue
        std::queue<MissionPoint> MissionPointQueue = mpMissionPlanner->GetMissionPointQueue();
        // 第二步 addtask 任务开始
        while(MissionPointQueue.size())
        {
            
            // 无人机调整完成,无人机发送一个指令
            if(UAVAdjustmentFinshFlag)
            {
                // 下一个需要执行的任务
                MissionPoint MissionPointCur = MissionPointQueue.front();

                //向无人机发送目标位置高度指令
                MissionPointCur.height;

                // 无人机判定自身到达指定高度，且需要总控电脑做判断到达指定高度
                while(true) 
                {
                    if(true)
                        break;
                }

                // 添加任务，需要判断任务是否成功执行
                bool AddTaskFlag = AddTask(MissionPointCur.start, MissionPointCur.goal);

                if(AddTaskFlag)
                {
                    MissionPointQueue.pop();
                }
                else
                {
                    std::cerr << "任务发送失败" << std::endl;
                }


                UAVAdjustmentFinshFlag = false;

                
            }

        }
        // while(queue.size())
        // {

        // }
        // 什么时候下发下一个规划，需要AGV和UAV状态没问题，且跟随上就pop出队列并addTask()，标志位为调整完成的状态话，就需要pop和addTask()，没有调整完成的话需要就不pop新的任务点
    }
} 