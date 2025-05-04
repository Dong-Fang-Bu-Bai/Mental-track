#include "LevelRecord.h"
#include <iostream>
#include<QDebug>

LevelRecord::LevelRecord(int levelId, float completionTime, bool passed)
    : levelId(levelId), completionTime(completionTime), passed(passed) {}

bool LevelRecord::validate() const
{
    try {
        // 验证关卡ID
        if(levelId <= 0) {
            qWarning() << "Invalid level ID:" << levelId;
            return false;
        }

        // 验证完成时间
        if(completionTime < 0 || completionTime > 3600) { // 假设最大1小时
            qWarning() << "Invalid completion time:" << completionTime;
            return false;
        }

        // 如果标记为已通关，但时间为0，则无效
        if(passed && completionTime <= 0) {
            qWarning() << "Passed level with invalid time:" << completionTime;
            return false;
        }

        return true;
    } catch(...) {
        qCritical() << "Exception in LevelRecord::validate()";
        return false;
    }
}


void LevelRecord::serialize(std::ostream& out) const
{
    out.write(reinterpret_cast<const char*>(&levelId), sizeof(levelId));
    out.write(reinterpret_cast<const char*>(&completionTime), sizeof(completionTime));
    out.write(reinterpret_cast<const char*>(&passed), sizeof(passed));
}

void LevelRecord::deserialize(std::istream& in)
{
    in.read(reinterpret_cast<char*>(&levelId), sizeof(levelId));
    in.read(reinterpret_cast<char*>(&completionTime), sizeof(completionTime));
    in.read(reinterpret_cast<char*>(&passed), sizeof(passed));
}

// 访问方法实现
int LevelRecord::getLevelId() const
{
    return levelId;
}

float LevelRecord::getCompletionTime() const
{
    return completionTime;
}

bool LevelRecord::isPassed() const
{
    return passed;
}

void LevelRecord::updateCompletionTime(float newTime)
{
    // 只更新更优（更小）的完成时间
    if(newTime < completionTime || completionTime == 0.0f)
    {
        completionTime = newTime;
        passed = true; // 更新完成时间时自动标记为已通关
    }
}

// 新增：设置通关状态
void LevelRecord::setPassed(bool ifpassed)
{
    this->passed = ifpassed;

    // 如果设置为未通关，重置完成时间
    if(!passed) {
        completionTime = 0.0f;
    }
}
