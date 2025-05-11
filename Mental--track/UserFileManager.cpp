#include "UserFileManager.h"
#include <fstream>
#include <iomanip>
#include <ctime>
#include<QDebug>

bool UserFileManager::saveUsers(const std::vector<User>& users, const std::string& filename)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) return false;

    size_t userCount = users.size();
    outFile.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));

    for (const auto& user : users)
    {
        user.serialize(outFile);
    }

    return outFile.good();
}

bool UserFileManager::loadUsers(std::vector<User>& users, const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) return false;

    size_t userCount;
    inFile.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));
    //users.resize(userCount);
    users.clear();
    users.reserve(userCount);

    for (size_t i = 0; i < userCount; ++i)
    {
        //user.deserialize(inFile);
        users.push_back(User::createFromSerialized(inFile));
    }

    return inFile.good();
}


bool UserFileManager::saveUser(const User& user, const std::string& filename) {
    std::vector<User> users;
        if(!loadUsers(users, filename)) {
            users.clear();
        }

        bool found = false;
        for(auto& u : users) {
            if(u.getUsername() == user.getUsername()) {
                u = user; // 这里会调用User的赋值运算符
                found = true;
                break;
            }
        }

        if(!found) {
            users.push_back(user);
        }

        return saveUsers(users, filename);
}


bool UserFileManager::generateDeveloperReport(const std::string& userDataFile,
                                            const std::string& reportFile)
{

        // 加载所有用户数据
        std::vector<User> users;
        if (!loadUsers(users, userDataFile))
        {
            qDebug()<<"false"<<endl;
            return false;
        }

        // 创建报告文件
        std::ofstream out(reportFile);
        if (!out) {
            return false;
        }

        // 获取当前时间
        auto now = std::time(nullptr);
        auto localTime = *std::localtime(&now);

        // 写入报告头
        out << "=== 用户数据开发者报告 ===\n";
        out << "生成时间: " << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "\n";
        out << "用户总数: " << users.size() << "\n\n";

        // 遍历所有用户
        for (const auto& user : users) {
            out << "用户名: " << user.getUsername() << "\n";
            out << "密码哈希: " << user.getPasswordHash() << "\n";  // 注意：这只是哈希值，不是明文密码

            // 统计并显示通过的关卡
            const auto& records = user.getAllRecords();
            int passedCount = 0;

            // 收集已通过的关卡并按关卡ID从大到小排序
            std::vector<std::pair<int, LevelRecord>> passedLevels;
            for (const auto& record : records)
            {
                if (record.second.isPassed()) {
                    passedCount++;
                    passedLevels.emplace_back(record.first, record.second);
                }
            }

            // 按关卡ID从大到小排序
            std::sort(passedLevels.begin(), passedLevels.end(),
                       [](const std::pair<int, LevelRecord>& a,
                          const std::pair<int, LevelRecord>& b)
                       {
                           return a.first > b.first; // 降序排列
                       });

            out << "通过关卡数: " << passedCount << "/" << records.size() << "\n";

            // 显示通过的关卡详情（已排序）
            if (passedCount > 0) {
                out << "通过的关卡详情 :\n";
                for (const auto& record : passedLevels) {
                    out << "  关卡" << record.first
                        << " - 最佳时间: " << record.second.getCompletionTime() << "秒\n";
                }
            }

            // 显示勋章情况
            const auto& medals = user.getMedals();
            out << "获得勋章数: " << medals.size() << "\n";
            if (!medals.empty()) {
                out << "勋章详情:\n";
                for (const auto& medal : medals) {
                    out << "  " << medalToString(medal) << "\n";
                }
            }

            //显示创意工坊贡献情况
            out << "创意工坊:\n";
            out << "  创建地图数: " << user.getCreatedMaps() << "\n";
            out << "  获得积分: " << user.getWorkshopPoints() << "\n";

            // 添加人机对战数据
            out << "人机对战:\n";
            out << "  胜场数: " << user.getBattleWins() << "\n";
            out << "  总场数: " << user.getBattleTotal() << "\n";
            out << "  胜率: " << QString::number(user.getWinRate(), 'f', 1).toStdString() << "%\n";
            out << "  对战积分: " << user.getBattlePoints() << "\n";

            out << "----------------------------------------\n\n";
        }

        out << "=== 报告结束 ===\n";
        return out.good();
}
