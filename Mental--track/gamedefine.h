#ifndef GAMEDEFINE_H
#define GAMEDEFINE_H

#include<QGraphicsPixmapItem>//图形元素
#include<QGraphicsView>//视图
#include<QMediaPlayer>//媒体播放器
#include<QLabel>
#include"Login.h"
#include"Register.h"
#include"Help.h"
#include"Start.h"
#include"Mode.h"
#include"Map.h"
#include"Setting.h"
#include"Gameplay.h"
#include"AudioManager.h"



class gamedefine
{
public:
    gamedefine();
};

Start* getGlobalStartWindow();

Login* getGlobalLoginWindow();

Register* getGlobalRegisterWindow();

//Help* getGlobalHelpWindow(); 不将 帮助 窗口设置为静态，改为随叫随到

Mode* getGlobalModeWindow();








#endif // GAMEDEFINE_H
