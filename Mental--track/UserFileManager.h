#ifndef USERFILEMANAGER_H
#define USERFILEMANAGER_H

#include "User.h"
#include <fstream>
#include <vector>



class UserFileManager
{
public:
    static bool saveUsers(const std::vector<User>& users, const std::string& filename= "user.dat");
    static bool loadUsers(std::vector<User>& users, const std::string& filename = "user.dat");

    // 新增：保存单个用户
    static bool saveUser(const User& user, const std::string& filename = "users.dat");

};

#endif // USERFILEMANAGER_H
