#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include"Hexagonbutton.h"
#include"User.h"
#include"Gameplay.h"
#include<QPointer>
#include<QMap>
#include<Leaderboard.h>
#include "MedalPopup.h"

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(User&,QWidget *parent = nullptr);
    ~Map();

   HexagonButton* getButton(int index)
   {
        return m_buttons.value(index); // QVector版

   }

   void setupLevelButtons();

public slots:
    void refreshUserData();

//private slots:
//    void handleLevelCompleted(int levelId);

private:
    Ui::Map *ui;
    User *m_currentUser;// 改为指针
    QVector<HexagonButton*> m_buttons; // 通过vector按创建顺序存储按钮
    QPointer<Gameplay> m_currentGameplay; // 自动置空当窗口被删除时
    void gamebtn(int);
    void onGameplayFinished();
    void updatePassedLevelsLabel();  // 新增方法
    Leaderboard* leaderboard = nullptr;
    QLabel *label_Play;
    // 为不同按钮指定不同关卡
    //设置映射表
    QMap<int, QString> levelMap
    {
        {0, ":/leveldata/Debug/levels/level1/level1.txt"},
        {1, ":/leveldata/Debug/levels/level1/level1.txt"},
        {2, ":/leveldata/Debug/levels/level1/level1.txt"},
        {3, ":/leveldata/Debug/levels/level1/level1.txt"},
        {4, ":/leveldata/Debug/levels/level1/level1.txt"},
        {5, ":/leveldata/Debug/levels/level1/level1.txt"},
        {6, ":/leveldata/Debug/levels/level1/level1.txt"},
        {7, ":/leveldata/Debug/levels/level1/level1.txt"},
        {8, ":/leveldata/Debug/levels/level1/level1.txt"},
        {9, ":/leveldata/Debug/levels/level1/level1.txt"},
        {10, ":/leveldata/Debug/levels/level1/level1.txt"},
        {11, ":/leveldata/Debug/levels/level1/level1.txt"},
        {12, ":/leveldata/Debug/levels/level1/level1.txt"},
        {13, ":/leveldata/Debug/levels/level1/level1.txt"},
        {14, ":/leveldata/Debug/levels/level1/level1.txt"},
        {15, ":/leveldata/Debug/levels/level1/level1.txt"},
        {16, ":/leveldata/Debug/levels/level1/level1.txt"},
        {17, ":/leveldata/Debug/levels/level1/level1.txt"},
        {18, ":/leveldata/Debug/levels/level1/level1.txt"},
        {19, ":/leveldata/Debug/levels/level1/level1.txt"},
        {20, ":/leveldata/Debug/levels/level1/level1.txt"},
        {21, ":/leveldata/Debug/levels/level1/level1.txt"},
        {22, ":/leveldata/Debug/levels/level1/level1.txt"},
        {23, ":/leveldata/Debug/levels/level1/level1.txt"},
        {24, ":/leveldata/Debug/levels/level1/level1.txt"},
        {25, ":/leveldata/Debug/levels/level1/level1.txt"},
        {26, ":/leveldata/Debug/levels/level1/level1.txt"},
        {27, ":/leveldata/Debug/levels/level1/level1.txt"},
        {28, ":/leveldata/Debug/levels/level1/level1.txt"},
        {29, ":/leveldata/Debug/levels/level1/level1.txt"},
        {30, ":/leveldata/Debug/levels/level1/level1.txt"},
        {31, ":/leveldata/Debug/levels/level1/level1.txt"},
        {32, ":/leveldata/Debug/levels/level1/level1.txt"},
        {33, ":/leveldata/Debug/levels/level1/level1.txt"},
        {34, ":/leveldata/Debug/levels/level1/level1.txt"},
        {35, ":/leveldata/Debug/levels/level1/level1.txt"},
        {36, ":/leveldata/Debug/levels/level1/level1.txt"},
        {37, ":/leveldata/Debug/levels/level1/level1.txt"},
        {38, ":/leveldata/Debug/levels/level1/level1.txt"},
        {39, ":/leveldata/Debug/levels/level1/level1.txt"},
        {40, ":/leveldata/Debug/levels/level1/level1.txt"},
        {41, ":/leveldata/Debug/levels/level1/level1.txt"},
        {42, ":/leveldata/Debug/levels/level1/level1.txt"},
        {43, ":/leveldata/Debug/levels/level1/level1.txt"},
        {44, ":/leveldata/Debug/levels/level1/level1.txt"},
        {45, ":/leveldata/Debug/levels/level1/level1.txt"},
        {46, ":/leveldata/Debug/levels/level1/level1.txt"},
        {47, ":/leveldata/Debug/levels/level1/level1.txt"},
        {48, ":/leveldata/Debug/levels/level1/level1.txt"},
        {49, ":/leveldata/Debug/levels/level1/level1.txt"},
        {50, ":/leveldata/Debug/levels/level1/level1.txt"},
        {51, ":/leveldata/Debug/levels/level1/level1.txt"},
        {52, ":/leveldata/Debug/levels/level1/level1.txt"},
        {53, ":/leveldata/Debug/levels/level1/level1.txt"},
        {54, ":/leveldata/Debug/levels/level1/level1.txt"},
        {55, ":/leveldata/Debug/levels/level1/level1.txt"},
        {56, ":/leveldata/Debug/levels/level1/level1.txt"},
        {57, ":/leveldata/Debug/levels/level1/level1.txt"},
        {58, ":/leveldata/Debug/levels/level1/level1.txt"},
        {59, ":/leveldata/Debug/levels/level1/level1.txt"},
        {60, ":/leveldata/Debug/levels/level1/level1.txt"},


    };
};

#endif // MAP_H
