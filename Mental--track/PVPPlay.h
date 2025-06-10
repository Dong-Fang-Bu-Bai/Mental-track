#ifndef PVPPLAY_H
#define PVPPLAY_H

#include <QWidget>
#include"gamedefine.h"
#include "User.h"
#include "PVPGridScene.h"
#include "PVPNetworkManager.h"
#include "CustomDialog.h"


class PVPPlay : public QWidget
{
    Q_OBJECT

public:
    explicit PVPPlay(User& user, QWidget *parent = nullptr);
    ~PVPPlay();

    void startAsHost(const QString& password, int timeout);
    void connectAsClient(const QString& address, quint16 port, const QString& password);

signals:
    void returnToLobby();

private slots:
    void onConnectionEstablished(const QString& opponentName);
    void onGameDataReceived(const QByteArray& data);
    void onConnectionLost();
    void onWaitingForPlayer();
    void onOpponentDisconnected();
    void onConnectionFailed(const QString& reason);
    void onExitButtonClicked();
    void onGameOver(bool playerWon);
    void onTurnChanged(bool isPlayerTurn);
    void onTimerVisibilityChanged(bool visible, bool isCritical = false);
    void onReturnToLobbyConfirmed(bool keepRoomOpen);

private:
    void setupUI();
    void showWaitingDialog();
    void showConnectionDialog();
    void showDisconnectMessage(bool playerWon);
    void updateUserStats(bool playerWon);

    void onBoundaryViolation(bool isPlayerViolation);

    void showGameResult(bool playerWon);

    //QMessageBox* m_messageBox; // 用于显示非阻塞提示
    CustomDialog *m_customDialog; // 替换原来的QMessageBox

    User* m_currentUser;
    PVPGridScene* m_pvpScene;
    PVPNetworkManager* m_networkManager;
    QGraphicsView* m_view;
    QLabel* m_timerLabel;
    QTimer* m_gameTimer;
    int m_timeLeft;
    bool m_isHost;
    QString m_password;
    int m_timeoutDuration;

    bool m_gameEnded = false;
};


#endif // PVPPLAY_H
