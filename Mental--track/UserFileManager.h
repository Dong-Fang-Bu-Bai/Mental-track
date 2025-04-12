#ifndef USERFILEMANAGER_H
#define USERFILEMANAGER_H

#include "User.h"
#include <fstream>
#include <vector>



class UserFileManager
{
public:
     static bool saveUsers(const std::vector<User>& users, const std::string& filename);
    static bool loadUsers(std::vector<User>& users, const std::string& filename = "user.dat");

};

#endif // USERFILEMANAGER_H
