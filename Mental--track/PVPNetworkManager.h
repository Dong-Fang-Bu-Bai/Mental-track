#ifndef PVPNETWORKMANAGER_H
#define PVPNETWORKMANAGER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QTimer>
#include "User.h"
#include"PVPGridScene.h"

class PVPGridScene; // 前向声明

class PVPNetworkManager : public QObject {
    Q_OBJECT
public:
    enum ConnectionState {
        Disconnected,
        Hosting,
        Connecting,
        Connected
    };

    explicit PVPNetworkManager(QObject *parent = nullptr);
    ~PVPNetworkManager();

    void startAsHost(quint16 port, const QString& password, int timeout);
    void connectAsClient(const QString& address, quint16 port, const QString& password);
    void disconnectFromHost();
    void sendGameData(const QByteArray& data);

    ConnectionState connectionState() const { return m_state; }
    bool isHost() const { return m_isHost; }
    int timeoutDuration() const { return m_timeoutDuration; }

    void setCurrentUser(User* user) { m_currentUser = user; }

    void setPVPGridScene(PVPGridScene* scene); // 新增方法

signals:
    void connectionEstablished(const QString& opponentName);
    void gameDataReceived(const QByteArray& data);
    void connectionLost();
    void waitingForPlayer();
    void opponentDisconnected();
    void connectionFailed(const QString& reason);
    void passwordRequired();
    void passwordAccepted();
    void opponentReady();  // 新增信号 - 对手已准备
    void hostReady();     // 新增信号 - 主机已准备
    void readyToStart(); // 双方都准备好可以开始游戏
    void gameOverReceived(bool playerWon);

private slots:
    void onNewConnection();
    void onClientConnected();
    void onDataReceived();
    void onDisconnected();
    void onConnectionTimeout();

private:
    void setupSocketConnections();
    void cleanUp();

    QTcpServer *m_server = nullptr;
    QTcpSocket *m_socket = nullptr;
    ConnectionState m_state = Disconnected;
    bool m_isHost = false;
    QString m_password;
    int m_timeoutDuration = 6; // 默认6秒
    QTimer m_connectionTimer;
    User* m_currentUser = nullptr;
    QString m_opponentName;
    PVPGridScene* m_pvpScene = nullptr;
};


#endif // PVPNETWORKMANAGER_H
