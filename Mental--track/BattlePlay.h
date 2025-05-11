#ifndef BATTLEPLAY_H
#define BATTLEPLAY_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsOpacityEffect>
#include<QLabel>
#include"User.h"

namespace Ui {
class BattlePlay;
}

class BattleGridScene;
class DifficultyDialog;

class BattlePlay : public QWidget
{
    Q_OBJECT

public:
    explicit BattlePlay(User&,QWidget *parent = nullptr);  // 修改构造函数
    ~BattlePlay();

    void stopTimer();

    // 添加成员变量
    void setCurrentUser(User* user);

private slots:
    void onGameOver(bool playerWon);
    void onDifficultySelected(int difficulty);
    void onPauseButtonClicked();  // 暂停按钮点击槽函数
    void resumeGame();           // 恢复游戏函数
    void restartLevel();  // 新增重新开始函数

private:
    User* m_currentUser = nullptr; // 改为指针成员
    void setupUI();
    void showDifficultyDialog();

    // 添加计时器相关成员
       QTimer* m_gameTimer;
       int m_timeLeft;
       QLabel* m_timerLabel; // 用于显示计时器的QLabel


       void startTimer();

       void updateTimerDisplay();
       void onTimerTimeout();


    Ui::BattlePlay *ui;
    BattleGridScene* m_battleScene;
    QGraphicsView* m_view;
    QWidget* m_mask = nullptr; // 新增遮罩窗口指针
    QWidget* m_pauseOverlay;     // 暂停时的覆盖层
    int m_pausedTimeLeft = 0; // 保存暂停时的剩余时间
};

#endif // BATTLEPLAY_H
