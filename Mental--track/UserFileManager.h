#ifndef USERFILEMANAGER_H
#define USERFILEMANAGER_H

#include "User.h"
#include <fstream>
#include <vector>



class UserFileManager
{
public:
    static bool saveUsers(const std::vector<User>& users, const std::string& filename= "users.dat");
    static bool loadUsers(std::vector<User>& users, const std::string& filename = "users.dat");

    // 新增：保存单个用户
    static bool saveUser(const User& user, const std::string& filename = "users.dat");
    bool generateDeveloperReport(const std::string& userDataFile, const std::string& reportFile);

};

#endif // USERFILEMANAGER_H
