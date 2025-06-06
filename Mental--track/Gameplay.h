#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QLabel>
#include <QTimer>
#include<QPushButton>
#include "User.h"
#include"UserFileManager.h"
#include"Interactivegridscene.h"
#include"Displaygridscene.h"

namespace Ui {
class Gameplay;
}

class Gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit Gameplay(const QString& levelPath = ":/leveldata/Debug/levels/level1/level1.txt",
                      int levelId = 1, // 新增关卡ID参数
                      User* currentUser = nullptr, // 新增当前用户指针
                     QWidget *parent = nullptr);
    ~Gameplay();

signals:
    void returnToMapRequested();
    void levelCompleted(int levelId); // 新增信号

private slots:
    void updateTimer(); // 计时器更新槽函数
    void onReturnButtonClicked();
    void onPauseButtonClicked();  // 暂停按钮点击槽函数
    void resumeGame();           // 恢复游戏函数
    void restartLevel();  // 新增重新开始函数

private:
    Ui::Gameplay *ui;
    QString m_levelPath; // 存储关卡路径
    int m_levelId;       // 当前关卡ID
    User* m_currentUser; // 当前用户指针
    QLabel *m_timeLabel; // 显示时间的标签
    QTimer *m_timer;     // 计时器
    int m_elapsedTime;   // 已用时间(秒)
    QPushButton *m_returnButton;//返回按钮
    QWidget* m_pauseOverlay;     // 暂停时的覆盖层
    bool m_isPaused;             // 游戏是否暂停
    InteractiveGridScene* interactiveScene;
    DisplayGridScene *displayScene;

    bool loadLevel(const QString& filePath ,
                            QVector<QPoint>& playerPath,
                            QVector<QPoint>& enemyPath) ;
};

#endif // GAMEPLAY_H
