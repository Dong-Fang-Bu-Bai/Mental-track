#ifndef USER_H
#define USER_H
#include "MedalType.h"
#include "LevelRecord.h"
#include <unordered_map>
#include <vector>
#include <QCryptographicHash>


class User
{
public:
    //User(const std::string& username = "", const std::string& password = "",int totalLevels = 61);

    // 创建新用户（会初始化关卡记录）
        static User* createNewUser(const std::string& username, const std::string& password, int totalLevels = 61);

    // 从序列化数据加载用户（不会初始化关卡记录）
        static User createFromSerialized(std::istream& in);

    // 序列化接口
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    // 账户验证
    bool verifyPassword(const std::string& input) const;

    // 关卡状态管理 (新增)
    void setLevelPassed(int levelId, bool passed = true);
    bool isLevelPassed(int levelId) const;
    void setLevelCompletionTime(int levelId, float time);
    float getLevelCompletionTime(int levelId) const;


    // 勋章系统
    void addMedal(MedalType medal);
    bool hasMedal(MedalType medal) const;

    // 访问方法
    std::string getUsername() const;
    const std::unordered_map<int, LevelRecord>& getAllRecords() const;
    const std::vector<MedalType>& getMedals() const;
    const std::string& getPasswordHash() const { return passwordHash; }

private:
    std::string username;
    std::string passwordHash; //哈希值
    std::unordered_map<int, LevelRecord> levelRecords;// 同时存储通关状态和时间
    std::vector<MedalType> medals;
    void initializeLevelRecords(int totalLevels);  // 新增初始化方法
    // 设为私有，强制使用工厂方法创建
    User(const std::string& username, const std::string& password);
    User() = default; // 用于反序列化


};

#endif // USER_H
