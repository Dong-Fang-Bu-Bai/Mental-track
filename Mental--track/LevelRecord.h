#ifndef LEVELRECORD_H
#define LEVELRECORD_H
#include <string>
#include <vector>


class LevelRecord
{
 public:
    // 构造函数添加passed参数
    LevelRecord(int levelId = 0, float completionTime = 0.0f, bool passed = false);

    // 数据验证方法
    bool validate() const;

    // 更新完成时间
    void updateCompletionTime(float newTime);

    // 设置/获取通关状态
    void setPassed(bool passed);
    bool isPassed() const;

    // 访问方法
    int getLevelId() const;
    float getCompletionTime() const;


    // 序列化方法
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);




    private:
        int levelId;
        float completionTime; // 单位：秒
        bool passed;          // 新增：表示关卡是否已通关
};

#endif // LEVELRECORD_H
