#ifndef LEVELRECORD_H
#define LEVELRECORD_H
#include <string>
#include <vector>


class LevelRecord
{
    public:
    LevelRecord(int levelId = 0, float completionTime = 0.0f);

        // 序列化方法
        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);

        // 访问方法
        int getLevelId() const;
        float getCompletionTime() const;
        void updateCompletionTime(float newTime);

    private:
        int levelId;
        float completionTime; // 单位：秒
};

#endif // LEVELRECORD_H
