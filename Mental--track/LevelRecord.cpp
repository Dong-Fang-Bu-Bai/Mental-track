#include "LevelRecord.h"
#include <iostream>

LevelRecord::LevelRecord(int levelId, float completionTime)
    : levelId(levelId), completionTime(completionTime) {}

void LevelRecord::serialize(std::ostream& out) const
{
    out.write(reinterpret_cast<const char*>(&levelId), sizeof(levelId));
    out.write(reinterpret_cast<const char*>(&completionTime), sizeof(completionTime));
}

void LevelRecord::deserialize(std::istream& in)
{
    in.read(reinterpret_cast<char*>(&levelId), sizeof(levelId));
    in.read(reinterpret_cast<char*>(&completionTime), sizeof(completionTime));
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

void LevelRecord::updateCompletionTime(float newTime)
{
    // 只更新更优（更小）的完成时间
    if(newTime < completionTime || completionTime == 0.0f)
    {
        completionTime = newTime;
    }
}
