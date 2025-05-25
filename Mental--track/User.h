#ifndef USER_H
#define USER_H
#include "MedalType.h"
#include "LevelRecord.h"
#include <unordered_map>
#include <vector>
#include <QCryptographicHash>
#include<QDebug>
#include<QString>


class User
{
public:

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
    // 获取当前勋章数量
    int getMedalsCount() const
    {
        return medals.size();
    }
    void addMedal(MedalType medal);
    bool hasMedal(MedalType medal) const;

    // 访问方法
    std::string getUsername() const;
    const std::unordered_map<int, LevelRecord>& getAllRecords() const;
    const std::vector<MedalType>& getMedals() const;
    const std::string& getPasswordHash() const { return passwordHash; }
    int getPassedLevelCount() const
    {
        int count = 0;
        for (const auto& [id, record] : levelRecords)
        {
            if (record.isPassed()) count++;
        }
        return count;
    }

    void debugPrint() const
    {
        qDebug() << "User:" << QString::fromStdString(username);
        qDebug() << "Passed levels:" << getPassedLevelCount();
        qDebug() << "Medals count:" << medals.size();
        for(const auto& [id, record] : levelRecords) {
            if(record.isPassed()) {
                qDebug() << "Level" << id << "time:" << record.getCompletionTime();
            }
        }
    }

    // 添加这个方法替代原来的validate()
       bool isValid() const
       {
           // 基础验证
           if(username.empty()) {
               qDebug() << "Invalid user: empty username";
               return false;
           }

           // 检查是否有有效记录
           bool hasValidRecords = false;
           for(const auto& [id, record] : levelRecords) {
               if(record.isPassed() && record.getCompletionTime() > 0) {
                   hasValidRecords = true;
                   break;
               }
           }

           if(!hasValidRecords) {
               qDebug() << "User" << username.c_str() << "has no valid records";
           }

           return hasValidRecords;
       }

       // 添加这个方法获取有效关卡数
           int getValidPassedLevelCount() const {
               int count = 0;
               for(const auto& [id, record] : levelRecords)
               {
                   if(record.isPassed() && record.getCompletionTime() > 0) {
                       count++;
                   }
               }
               return count;
           }

           // 添加内存安全的访问方法
            std::string  getSafeUsername() const {
               try {
                   return username;
               } catch(...) {
                   return "[corrupted]";
               }
           }

           // 安全获取记录
           const std::unordered_map<int, LevelRecord> getSafeRecords() const
           {
               std::unordered_map<int, LevelRecord> safeCopy;
               try {
                   for(const auto& [id, record] : levelRecords) {
                       if(id > 0 && record.validate()) {
                           safeCopy.insert({id, record});
                       }
                   }
               } catch(...) {
                   qCritical() << "Error copying records";
               }
               return safeCopy;
           }

           // 新增方法
           int getCreatedMaps() const { return createdMaps; }
           int getWorkshopPoints() const { return workshopPoints; }
           void incrementCreatedMaps() { createdMaps++; }
           void addWorkshopPoints(int points) { workshopPoints += points; }



       // 新增访问方法
       int getBattleWins() const { return battleWins; }
       int getBattleTotal() const { return battleTotal; }
       int getBattlePoints() const { return battlePoints; }
       float getWinRate() const
       {
        return battleTotal > 0 ? (float)battleWins / battleTotal * 100 : 0.0f;
       }

       // 新增修改方法
       void addBattleResult(bool isWin, int points)
       {
         battleTotal++;
         if(isWin)
         {
           battleWins++;
           battlePoints += points;
         }

       }


private:
    std::string  username;
    std::string passwordHash; //哈希值
    std::unordered_map<int, LevelRecord> levelRecords;// 同时存储通关状态和时间
    std::vector<MedalType> medals;
    int createdMaps = 0;  // 创建的地图数
    int workshopPoints = 0; // 创意工坊积分
    // 新增人机对战相关属性
       int battleWins = 0;       // 胜局数
       int battleTotal = 0;      // 总对局数
       int battlePoints = 0;     // 对战积分

    void initializeLevelRecords(int totalLevels);  // 新增初始化方法
    // 设为私有，强制使用工厂方法创建
    User(const std::string& username, const std::string& password);
    User() = default; // 用于反序列化


};

#endif // USER_H
