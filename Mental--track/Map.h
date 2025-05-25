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
        //最终关
        {0, ":/leveldata/Debug/levels/levelS/levelS.txt"},

        //火焰四
        {1, ":/leveldata/Debug/levels/level10/level10.txt"},

        //雷霆四
        {2, ":/leveldata/Debug/levels/level1/level1.txt"},

        //暗影四
        {3, ":/leveldata/Debug/levels/level1/level1.txt"},

        //寒冰四
        {4, ":/leveldata/Debug/levels/level1/level1.txt"},

        //自然四
        {5, ":/leveldata/Debug/levels/level1/level1.txt"},

        //神圣四
        {6, ":/leveldata/Debug/levels/level1/level1.txt"},

        //火焰三
        {7, ":/leveldata/Debug/levels/level8/level8.txt"},
        {8, ":/leveldata/Debug/levels/level9/level9.txt"},

        //雷霆三
        {9, ":/leveldata/Debug/levels/level1/level1.txt"},
        {10, ":/leveldata/Debug/levels/level1/level1.txt"},

        //暗影三
        {11, ":/leveldata/Debug/levels/level1/level1.txt"},
        {12, ":/leveldata/Debug/levels/level1/level1.txt"},


        //寒冰三
        {13, ":/leveldata/Debug/levels/level1/level1.txt"},
        {14, ":/leveldata/Debug/levels/level1/level1.txt"},


        //自然三
        {15, ":/leveldata/Debug/levels/level1/level1.txt"},
        {16, ":/leveldata/Debug/levels/level1/level1.txt"},


        //神圣三
        {17, ":/leveldata/Debug/levels/level1/level1.txt"},
        {18, ":/leveldata/Debug/levels/level1/level1.txt"},


        //火焰二
        {19, ":/leveldata/Debug/levels/level5/level5.txt"},
        {20, ":/leveldata/Debug/levels/level6/level6.txt"},
        {21, ":/leveldata/Debug/levels/level7/level7.txt"},


        //雷霆二
        {22, ":/leveldata/Debug/levels/level1/level1.txt"},
        {23, ":/leveldata/Debug/levels/level1/level1.txt"},
        {24, ":/leveldata/Debug/levels/level1/level1.txt"},


        //暗影二
        {25, ":/leveldata/Debug/levels/level1/level1.txt"},
        {26, ":/leveldata/Debug/levels/level1/level1.txt"},
        {27, ":/leveldata/Debug/levels/level1/level1.txt"},

        //寒冰二
        {28, ":/leveldata/Debug/levels/level1/level1.txt"},
        {29, ":/leveldata/Debug/levels/level1/level1.txt"},
        {30, ":/leveldata/Debug/levels/level1/level1.txt"},


        //自然二
        {31, ":/leveldata/Debug/levels/level1/level1.txt"},
        {32, ":/leveldata/Debug/levels/level1/level1.txt"},
        {33, ":/leveldata/Debug/levels/level1/level1.txt"},


        //神圣二
        {34, ":/leveldata/Debug/levels/level1/level1.txt"},
        {35, ":/leveldata/Debug/levels/level1/level1.txt"},
        {36, ":/leveldata/Debug/levels/level1/level1.txt"},

        //火焰一
        {37, ":/leveldata/Debug/levels/level1/level1.txt"},
        {38, ":/leveldata/Debug/levels/level2/level2.txt"},
        {39, ":/leveldata/Debug/levels/level3/level3.txt"},
        {40, ":/leveldata/Debug/levels/level4/level4.txt"},

        //雷霆一
        {41, ":/leveldata/Debug/levels/level1/level1.txt"},
        {42, ":/leveldata/Debug/levels/level1/level1.txt"},
        {43, ":/leveldata/Debug/levels/level1/level1.txt"},
        {44, ":/leveldata/Debug/levels/level1/level1.txt"},

        //暗影一
        {45, ":/leveldata/Debug/levels/level1/level1.txt"},
        {46, ":/leveldata/Debug/levels/level1/level1.txt"},
        {47, ":/leveldata/Debug/levels/level1/level1.txt"},
        {48, ":/leveldata/Debug/levels/level1/level1.txt"},


        //寒冰一
        {49, ":/leveldata/Debug/levels/level1/level1.txt"},
        {50, ":/leveldata/Debug/levels/level1/level1.txt"},
        {51, ":/leveldata/Debug/levels/level1/level1.txt"},
        {52, ":/leveldata/Debug/levels/level1/level1.txt"},


        //自然一
        {53, ":/leveldata/Debug/levels/level1/level1.txt"},
        {54, ":/leveldata/Debug/levels/level1/level1.txt"},
        {55, ":/leveldata/Debug/levels/level1/level1.txt"},
        {56, ":/leveldata/Debug/levels/level1/level1.txt"},


        //神圣一
        {57, ":/leveldata/Debug/levels/level1/level1.txt"},
        {58, ":/leveldata/Debug/levels/level1/level1.txt"},
        {59, ":/leveldata/Debug/levels/level1/level1.txt"},
        {60, ":/leveldata/Debug/levels/level1/level1.txt"},


    };
};

#endif // MAP_H
