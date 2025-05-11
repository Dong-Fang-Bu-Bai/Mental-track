#ifndef BATTLEGRIDSCENE_H
#define BATTLEGRIDSCENE_H

#include "Gridscene.h"
#include <QVector>
#include <QPoint>
#include <QTimer>



class BattleGridScene : public Gridscene
{
    Q_OBJECT
public:
    // 添加枚举和成员变量
    enum Difficulty { Easy, Medium, Hard };
    enum GameState { PlayerTurn, AITurn, GameOver };

    explicit BattleGridScene(int gridSize = 17, QObject* parent = nullptr);
    void startNewGame(Difficulty);
    ~BattleGridScene();
    void clearAllItems();

    void stopGame()
    {
        if(m_state == GameOver) return; // 如果已经是结束状态则不再处理
        m_state = GameOver;
        emit stateChanged(); // 通知状态变化

        // 注意：这里不再直接控制计时器，由BattlePlay通过stateChanged信号处理
        // 游戏结束的具体原因由调用方通过gameOver信号参数传递
    }

    Difficulty getDifficulty() const { return m_difficulty; }
    GameState getState() const { return m_state; }
    void handleTimeout(); // 处理超时的方法


signals:
    void gameOver(bool playerWon);
    void gameStarted();  // 添加游戏开始信号
    void stateChanged(); // 添加状态变化信号

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    GameState m_state;
    Difficulty m_difficulty;
    QVector<QPoint> m_playerPath;
    QVector<QPoint> m_aiPath;
    QPoint m_aiStartPos;

    //AI相关方法
    void makeAIMove();
    void makeStrategicAIMove();
    void makeRandomAIMove();
    QPoint findBestMove(const QVector<QPoint>& possibleMoves);


    //游戏逻辑方法
    bool isValidMove(const QPoint& pos) const;
    QVector<QPoint> calculateRelativePath() const;
    bool checkBoundaryViolation() const;
    bool isPositionOccupied(const QPoint& pos) const;


    //显示相关方法
    void updateGridDisplay();
    void restoreGridTransparency();
    void markBaseGridCells();
    void addPathCell(const QPoint& pos, bool isStart, int step);
    void addAICell(const QPoint& pos, bool isStart, int step);
    void addTextItem(const QPoint& pos, const QString& text, const QPointF& offset, int fontSize, const QColor& color);


};

#endif // BATTLEGRIDSCENE_H
