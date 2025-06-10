#include "PVPNetworkManager.h"

#include <QMessageBox>

PVPNetworkManager::PVPNetworkManager(QObject *parent) : QObject(parent) {
    connect(&m_connectionTimer, &QTimer::timeout, this, &PVPNetworkManager::onConnectionTimeout);
    m_connectionTimer.setSingleShot(true);
}

void PVPNetworkManager::startAsHost(quint16 port, const QString& password, int timeout) {
    m_password = password;
    m_timeoutDuration = timeout;
    m_isHost = true;

    if(!m_server) {
        m_server = new QTcpServer(this);
        connect(m_server, &QTcpServer::newConnection, this, &PVPNetworkManager::onNewConnection);
    }

    if(!m_server->listen(QHostAddress::Any, port)) {
        emit connectionFailed("无法启动服务器: " + m_server->errorString());
        return;
    }

    m_state = Hosting;
    emit waitingForPlayer();
    m_connectionTimer.start(30000); // 30秒等待超时
}

void PVPNetworkManager::connectAsClient(const QString& address, quint16 port, const QString& password) {
    m_password = password;
    m_isHost = false;

    m_socket = new QTcpSocket(this);
    setupSocketConnections();

    m_state = Connecting;
    emit connectionEstablished("正在连接...");

    m_socket->connectToHost(address, port);
    m_connectionTimer.start(10000); // 10秒连接超时
}

void PVPNetworkManager::onNewConnection() {
    if(m_state == Hosting)
    {
           QTcpSocket* clientSocket = m_server->nextPendingConnection();
           if(!m_socket) {
               m_socket = clientSocket;
               setupSocketConnections();

               // 不再主动发送请求，等待客户端先发送密码
               emit passwordRequired();
           } else {
               clientSocket->close();
               clientSocket->deleteLater();
           }
       }
}

void PVPNetworkManager::onClientConnected()
{

        qDebug() << "Client connected, isHost:" << m_isHost
                 << "CurrentUser:" << (m_currentUser ? "valid" : "null");

        if(!m_isHost && !m_currentUser)
        {
                qDebug() << "Fatal: Client mode but no user set!";
                disconnectFromHost();
                return;
        }

            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out << (quint8)0x01 << m_password;

            if(m_currentUser) {
                out << QString::fromStdString(m_currentUser->getUsername());
            } else {
                out << QString("UnknownPlayer");
            }

            m_socket->write(data);
}

void PVPNetworkManager::setPVPGridScene(PVPGridScene* scene)
{
    m_pvpScene = scene;
}


void PVPNetworkManager::onDataReceived()
{

    while(m_socket->bytesAvailable() > 0)
    {
            try {

            // 先读取类型字节
                   char type;
                   if(m_socket->peek(&type, 1) != 1) return;

                   qDebug() << "Processing network data - Type:" << (quint8)type
                            << "Bytes available:" << m_socket->bytesAvailable();


                switch((quint8)type)
                {
                case 0x01:
                { // 密码验证
                    m_socket->read(1); // 跳过类型字节
                    QDataStream in(m_socket);
                    if(m_isHost)
                    {
                        QString receivedPassword, username;
                        in >> receivedPassword >> username;

                        if(!m_currentUser) {
                            qDebug() << "Error: Host current user is null";
                            disconnectFromHost();
                            return;
                        }

                        bool accepted = (receivedPassword == m_password);

                        QByteArray response;
                        QDataStream out(&response, QIODevice::WriteOnly);
                        out << (quint8)0x01 << accepted;
                        if(accepted) {
                            out << QString::fromStdString(m_currentUser->getUsername());
                        }
                        m_socket->write(response);

                        if(accepted) {
                            m_opponentName = username;
                            m_state = Connected;
                            m_connectionTimer.stop();
                            emit connectionEstablished(username);
                        } else {
                            m_socket->disconnectFromHost();
                            emit connectionFailed("密码错误");
                        }
                    } else {
                        bool accepted;
                        QString opponentName;
                        in >> accepted >> opponentName;

                        if(accepted) {
                            qDebug() << "Connection accepted, opponent:" << opponentName;
                            // 添加状态检查，避免重复处理
                            if(m_state != Connected) {
                                m_state = Connected;
                                m_connectionTimer.stop();
                                emit connectionEstablished(opponentName);
                            }
                        } else {
                            emit connectionFailed("密码错误");
                            disconnectFromHost();
                        }
                    }
                    break;
              }

             case 0x02: // 游戏数据
              {
                    m_socket->read(1); // 跳过类型字节
                    QDataStream in(m_socket);
                    QPoint move;
                    //QPoint startPos;
                    in >> move ;

                    qDebug() << "Received move:" << move ;

                     // 只转发移动数据
                    QByteArray moveData;
                    QDataStream out(&moveData, QIODevice::WriteOnly);
                    out << (quint8)0x02 << move;
                    emit gameDataReceived(moveData);

                    break;
               }

               case 0x04:
                { // 位置同步指令
                    // 检查数据完整性
                               if(m_socket->bytesAvailable() < 1 + 2*sizeof(QPoint)) {
                                   qDebug() << "Waiting for complete position data...";
                                   return;
                               }

                               // 读取完整数据包
                               m_socket->read(1); // 跳过类型字节
                               QPoint clientPos, hostPos;
                               QDataStream in(m_socket);
                               in >> clientPos >> hostPos;

                               qDebug() << "Received position data - ClientPos:" << clientPos
                                        << "HostPos:" << hostPos;

                               if(m_pvpScene && !m_isHost) {
                                   m_pvpScene->setPlayerPosition(clientPos);
                                   m_pvpScene->setOpponentPosition(hostPos);
                               }
                               break;
                }

                case 0x05:
                { // 游戏结果指令
                    m_socket->read(1); // 跳过类型字节
                        QDataStream in(m_socket);
                        bool hostWon;
                        in >> hostWon;
                        qDebug() << "Received game result - HostWon:" << hostWon;

                        // 客户端收到结果后，转换为自己是否获胜
                        bool playerWon = !hostWon;

                        // 确保先处理游戏结束逻辑再显示提示
                        QMetaObject::invokeMethod(this, [this, playerWon]() {
                            emit gameOverReceived(playerWon);
                        }, Qt::QueuedConnection);
                        break;

                 }
                case 0x06:
                { // 确认指令
                    m_socket->read(1); // 跳过类型字节
                    qDebug() << "Client acknowledged game result";
                    break;
                }


            }
        }
         catch(...)
        {
                qDebug() << "数据解析错误";
                disconnectFromHost();
        }
     }
}

void PVPNetworkManager::setupSocketConnections() {
    connect(m_socket, &QTcpSocket::connected, this, [this]() {
           qDebug() << "Socket connected";
           onClientConnected();
       });

       connect(m_socket, &QTcpSocket::readyRead, this, [this]() {
           qDebug() << "Data received, bytes:" << m_socket->bytesAvailable();
           onDataReceived();
       });

       connect(m_socket, &QTcpSocket::disconnected, this, [this]() {
           qDebug() << "Socket disconnected";
           onDisconnected();
       });

       connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
           [this](QAbstractSocket::SocketError error)
       {
               qDebug() << "Socket error:" << m_socket->errorString();
               emit connectionFailed(m_socket->errorString());
       });
}

void PVPNetworkManager::cleanUp() {
    if(m_socket) {
        m_socket->deleteLater();
        m_socket = nullptr;
    }

    if(m_server) {
        m_server->close();
        m_server->deleteLater();
        m_server = nullptr;
    }

    m_state = Disconnected;
    m_connectionTimer.stop();
}

void PVPNetworkManager::disconnectFromHost() {
    if(m_socket) {
        m_socket->disconnectFromHost();
    }
    cleanUp();
}

void PVPNetworkManager::sendGameData(const QByteArray& data) {
    if(m_socket && m_socket->state() == QTcpSocket::ConnectedState) {
        m_socket->write(data);
    }
}

void PVPNetworkManager::onDisconnected() {
    if(m_state == Connected) {
        emit connectionLost();
    }
    cleanUp();
}

void PVPNetworkManager::onConnectionTimeout() {
    if(m_state == Hosting) {
        emit connectionFailed("等待玩家连接超时");
    } else if(m_state == Connecting) {
        emit connectionFailed("连接服务器超时");
    }
    cleanUp();
}


PVPNetworkManager::~PVPNetworkManager()
{
    cleanUp();
}
