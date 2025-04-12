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
