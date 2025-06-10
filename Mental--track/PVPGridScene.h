#ifndef PVPGRIDSCENE_H
#define PVPGRIDSCENE_H


#include "Gridscene.h"
#include "PVPNetworkManager.h"
#include <QTimer>
#include <QVector>

class PVPNetworkManager; // 前向声明

class PVPGridScene : public Gridscene
{
    Q_OBJECT
public:
    explicit PVPGridScene(int gridSize = 17, QObject* parent = nullptr);
    ~PVPGridScene();

    void startNewGame(int timeoutDuration, bool isPlayerFirst);
    void handleOpponentMove(const QPoint& move);
    int getRemainingTime() const;
    void setOpponentName(const QString& name);
    void setNetworkManager(PVPNetworkManager* manager);
    void sendMoveToOpponent(const QPoint& move);
    void endGameWithDisconnect(bool playerWon);
    bool isPlayerTurn() const { return m_state == PlayerTurn; }

    void confirmReady(); // 确认准备方法
    void startGame(); // 开始游戏


    QPoint getPlayerStartPos() const;
    QPoint getOpponentStartPos() const;
    bool isStartPosInitialized() const;

    //void setOpponentStartPos(const QPoint& pos);

     void setRandomSeed(int seed)
     {
         m_randomSeed=seed;
     }

     void setPlayerPosition(const QPoint& pos);
     void setOpponentPosition(const QPoint& pos);

      void onBoundaryViolation(bool isPlayerViolation);

      const QVector<QPoint>& getPlayerPath() const { return m_playerPath; }
      const QVector<QPoint>& getOpponentPath() const { return m_opponentPath; }


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;


private slots:
    void onTimeOut();
    void onOpponentDisconnected();

signals:
    void gameOver(bool playerWon);  // 添加信号声明
    void turnChanged(bool isPlayerTurn); // 新增回合切换信号
   void timerVisibilityChanged(bool visible, bool isCritical = false);
    void boundaryViolationDetected(bool isPlayerViolation);

private:
     enum GameState { Waiting, PlayerTurn, OpponentTurn, GameOver };


    void endGame(bool playerWon, bool isDisconnect = false);
    void updateGridDisplay();
    bool isValidMove(const QPoint& pos) const;
    bool checkBoundaryViolation() ;
    bool isPositionOccupied(const QPoint& pos) const;
    bool m_isHost;
    void clearAllItems();
    void addPathCell(const QPoint& pos, bool isPlayer, bool isStart, int step);
    void addTextItem(const QPoint& pos, const QString& text, const QPointF& offset,
                    int fontSize, const QColor& color);
    QPoint findRandomValidMove() const; // 寻找随机有效移动



    PVPNetworkManager* m_networkManager = nullptr;
    QTimer* m_gameTimer;
    int m_remainingTime;
    QString m_opponentName;
    GameState m_state;
    bool m_isPlayerFirst;
    bool m_isPlayerReady;
    bool m_isOpponentReady;
    QPoint m_playerStartPos;
    QPoint m_opponentStartPos;
    QVector<QPoint> m_playerPath;
    QVector<QPoint> m_opponentPath;
    bool m_startPositionsInitialized; // 标记是否已初始化起点

    int m_randomSeed = 0;
};


#endif // PVPGRIDSCENE_H
