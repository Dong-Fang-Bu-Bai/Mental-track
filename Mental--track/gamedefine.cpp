#include "gamedefine.h"

gamedefine::gamedefine()
{

}


Start* getGlobalStartWindow()
{
    static Start *w = nullptr;  // 全局唯一static
    if (!w) w = new Start();
    return w;
}

Login* getGlobalLoginWindow()
{
    static Login *w = nullptr;  // 全局唯一static
    if (!w) w = new Login();
    return w;
}

Register* getGlobalRegisterWindow()
{
    static Register *w = nullptr;  // 全局唯一static
    if (!w) w = new Register();
    return w;
}


Mode* getGlobalModeWindow()
{
    static Mode *w = nullptr;  // 全局唯一static
    if (!w) w = new Mode();
    return w;
}




