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
    User(const std::string& username = "", const std::string& password = "");

    // 序列化接口
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

    // 账户验证
    bool verifyPassword(const std::string& input) const;

    // 关卡记录管理
    void addLevelRecord(int levelId, float completionTime);
    const LevelRecord* getLevelRecord(int levelId) const;

    // 勋章系统修改为枚举类型
        void addMedal(MedalType medal);
        bool hasMedal(MedalType medal) const;

    // 访问方法
    std::string getUsername() const;
    const std::unordered_map<int, LevelRecord>& getAllRecords() const;
    const std::vector<MedalType>& getMedals() const;

private:
    std::string username;
    std::string passwordHash; //哈希值
    std::unordered_map<int, LevelRecord> levelRecords;
    std::vector<MedalType> medals; // 替换原来的std::vector<std::string>


};

#endif // USER_H
