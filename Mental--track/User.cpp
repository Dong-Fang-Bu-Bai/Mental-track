#include "User.h"
#include <algorithm>
#include<QString>

// 新增初始化关卡记录的方法
void User::initializeLevelRecords(int totalLevels)
{
    for (int i = 1; i <= totalLevels; ++i)
    {
        // 默认创建未通关记录(完成时间0.0f, passed=false)
        levelRecords.emplace(i, LevelRecord(i, 0.0f, false));
    }
}

// 工厂方法 - 创建新用户
User* User::createNewUser(const std::string& username, const std::string& password, int totalLevels)
{
    User *user=new User(username, password);
    user->initializeLevelRecords(totalLevels);
    return user;
}

// 工厂方法 - 从序列化数据加载
User User::createFromSerialized(std::istream& in)
{
    User user;
    user.deserialize(in);
    return user;
}

// 私有构造函数（用于创建新用户）
User::User(const std::string& username, const std::string& password)
    : username(username)
{
    // 密码加盐哈希
    QString salt = "game_salt_2025";
    passwordHash = QCryptographicHash::hash
    (
        (salt + QString::fromStdString(password)).toUtf8(),
        QCryptographicHash::Sha256
    ).toHex().toStdString();


    // 注意：这里不初始化关卡记录！
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

        //写入创建关卡数以及积分数
        out.write(reinterpret_cast<const char*>(&createdMaps), sizeof(createdMaps));
        out.write(reinterpret_cast<const char*>(&workshopPoints), sizeof(workshopPoints));

        // 写入人机对战数据
        out.write(reinterpret_cast<const char*>(&battleWins), sizeof(battleWins));
        out.write(reinterpret_cast<const char*>(&battleTotal), sizeof(battleTotal));
        out.write(reinterpret_cast<const char*>(&battlePoints), sizeof(battlePoints));
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

// 新增关卡状态管理方法
void User::setLevelPassed(int levelId, bool passed)
{
    auto it = levelRecords.find(levelId);
    if (it != levelRecords.end()) {
        it->second.setPassed(passed);
    } else {
        levelRecords.emplace(levelId, LevelRecord(levelId, 0.0f, passed));
    }
}

bool User::isLevelPassed(int levelId) const {
    auto it = levelRecords.find(levelId);
    return it != levelRecords.end() ? it->second.isPassed() : false;
}

void User::setLevelCompletionTime(int levelId, float time) {
    auto it = levelRecords.find(levelId);
    if (it != levelRecords.end()) {
        it->second.updateCompletionTime(time);
    } else {
        levelRecords.emplace(levelId, LevelRecord(levelId, time, true));
    }
}

float User::getLevelCompletionTime(int levelId) const {
    auto it = levelRecords.find(levelId);
    return it != levelRecords.end() ? it->second.getCompletionTime() : 0.0f;
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

const std::unordered_map<int, LevelRecord>& User::getAllRecords() const
{
    return levelRecords;
}

const std::vector<MedalType>& User::getMedals() const
{
    return medals;
}


// 反序列化实现
void User::deserialize(std::istream& in)
{

    // 清空现有数据
    levelRecords.clear();
    medals.clear();

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

       //读取创意工坊数据
       in.read(reinterpret_cast<char*>(&createdMaps), sizeof(createdMaps));
       in.read(reinterpret_cast<char*>(&workshopPoints), sizeof(workshopPoints));

       // 读取人机对战数据
       in.read(reinterpret_cast<char*>(&battleWins), sizeof(battleWins));
       in.read(reinterpret_cast<char*>(&battleTotal), sizeof(battleTotal));
       in.read(reinterpret_cast<char*>(&battlePoints), sizeof(battlePoints));
}

