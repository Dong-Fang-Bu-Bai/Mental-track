#include "User.h"
#include <algorithm>
#include<QString>

User::User(const std::string& username, const std::string& password)
    : username(username) {
    // 密码加盐哈希
    QString salt = "game_salt_2025";
    passwordHash = QCryptographicHash::hash(
        (salt + QString::fromStdString(password)).toUtf8(),
        QCryptographicHash::Sha256
    ).toHex().toStdString();
}

// 序列化
void User::serialize(std::ostream& out) const
{
    // 写入用户名长度和内容
    size_t nameLen = username.size();
    out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    out.write(username.c_str(), nameLen);

    // 写入密码哈希
    size_t hashLen = passwordHash.size();
    out.write(reinterpret_cast<const char*>(&hashLen), sizeof(hashLen));
    out.write(passwordHash.c_str(), hashLen);

    // 写入关卡记录
    size_t recordCount = levelRecords.size();
    out.write(reinterpret_cast<const char*>(&recordCount), sizeof(recordCount));
    for (const auto& record : levelRecords)
    {
        record.second.serialize(out);
    }

    // 写入勋章（存储为字符串）
        size_t medalCount = medals.size();
        out.write(reinterpret_cast<const char*>(&medalCount), sizeof(medalCount));
        for (const auto& medal : medals)
        {
            std::string medalStr = medalToString(medal);
            size_t medalLen = medalStr.size();
            out.write(reinterpret_cast<const char*>(&medalLen), sizeof(medalLen));
            out.write(medalStr.c_str(), medalLen);
        }
}


// 账户验证
bool User::verifyPassword(const std::string& input) const {
    QString salt = "game_salt_2025";
    QString inputHash = QCryptographicHash::hash(
        (salt + QString::fromStdString(input)).toUtf8(),
        QCryptographicHash::Sha256
    ).toHex();
    return inputHash.toStdString() == passwordHash;
}

// 关卡记录管理
void User::addLevelRecord(int levelId, float completionTime) {
    auto it = levelRecords.find(levelId);
    if (it != levelRecords.end()) {
        if (completionTime < it->second.getCompletionTime()) {
            it->second.updateCompletionTime(completionTime);
        }
    } else {
        levelRecords.emplace(levelId, LevelRecord(levelId, completionTime));
    }
}

const LevelRecord* User::getLevelRecord(int levelId) const {
    auto it = levelRecords.find(levelId);
    return it != levelRecords.end() ? &it->second : nullptr;
}

// 勋章系统
void User::addMedal(MedalType medal) {
    if (!hasMedal(medal)) {
        medals.push_back(medal);
    }
}

bool User::hasMedal(MedalType medal) const {
    return std::find(medals.begin(), medals.end(), medal) != medals.end();
}

// 访问方法
std::string User::getUsername() const {
    return username;
}

const std::unordered_map<int, LevelRecord>& User::getAllRecords() const {
    return levelRecords;
}

const std::vector<MedalType>& User::getMedals() const
{
    return medals;
}


// 反序列化实现
void User::deserialize(std::istream& in) {
    // 读取用户名
    size_t nameLen;
    in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    username.resize(nameLen);
    in.read(&username[0], nameLen);

    // 读取密码哈希
    size_t hashLen;
    in.read(reinterpret_cast<char*>(&hashLen), sizeof(hashLen));
    passwordHash.resize(hashLen);
    in.read(&passwordHash[0], hashLen);

    // 读取关卡记录
    size_t recordCount;
    in.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    for (size_t i = 0; i < recordCount; ++i) {
        LevelRecord record;
        record.deserialize(in);
        levelRecords.emplace(record.getLevelId(), record);
    }

    // 读取勋章
       size_t medalCount;
       in.read(reinterpret_cast<char*>(&medalCount), sizeof(medalCount));
       for (size_t i = 0; i < medalCount; ++i)
       {
           size_t medalLen;
           in.read(reinterpret_cast<char*>(&medalLen), sizeof(medalLen));
           std::string medalStr(medalLen, '\0');
           in.read(&medalStr[0], medalLen);
           medals.push_back(stringToMedal(medalStr));
       }
}


//// 授予勋章
//user.addMedal(MedalType::SpeedRunner);

//// 检查勋章
//if(user.hasMedal(MedalType::FirstBlood)) {
//    // 处理首胜逻辑
//}

//// 显示所有勋章
//for(auto medal : user.getMedals()) {
//    std::cout << medalToString(medal) << std::endl;
//}
