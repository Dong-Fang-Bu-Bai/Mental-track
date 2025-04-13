#include "UserFileManager.h"

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
    users.resize(userCount);

    for (auto& user : users)
    {
        user.deserialize(inFile);
    }

    return inFile.good();
}


bool UserFileManager::saveUser(const User& user, const std::string& filename) {
    // 先加载所有用户
    std::vector<User> users;
    if (!loadUsers(users, filename)) {
        // 如果文件不存在，创建新文件
        users.clear();
    }

    // 查找并更新用户
    bool found = false;
    for (auto& u : users) {
        if (u.getUsername() == user.getUsername()) {
            u = user;  // 更新用户数据
            found = true;
            break;
        }
    }

    // 如果没找到，添加新用户
    if (!found) {
        users.push_back(user);
    }

    // 保存所有用户
    return saveUsers(users, filename);
}
