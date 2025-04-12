#ifndef MEDALTYPE_H
#define MEDALTYPE_H


#include <string>

enum class MedalType {
    FirstBlood,      // 首胜
    SpeedRunner,     // 速通
    Collector,       // 收集者
    PerfectScore,    // 满分通关
    Marathoner,      // 持久战
    // 添加其他勋章类型...
};

// 辅助函数声明
std::string medalToString(MedalType type);
MedalType stringToMedal(const std::string& str);



#endif // MEDALTYPE_H
