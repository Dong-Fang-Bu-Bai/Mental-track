#include "PVPPlay.h"
#include <QInputDialog>
#include <QMessageBox>
#include "UserFileManager.h"
#include<QVBoxLayout>
#include<QRandomGenerator>
#include<QMutex>

PVPPlay::PVPPlay(User& user, QWidget *parent) :
    QWidget(parent),
    m_customDialog(new CustomDialog(this)), // 初始化自定义对话框
    m_currentUser(&user),
    m_pvpScene(new PVPGridScene(17, this)),
    m_networkManager(new PVPNetworkManager(this)),
    m_view(new QGraphicsView(m_pvpScene, this)),
    m_gameTimer(new QTimer(this))

{
    setupUI();

     // 设置网络管理器中的场景指针
      m_networkManager->setPVPGridScene(m_pvpScene);
      m_networkManager->setCurrentUser(m_currentUser);

    connect(m_networkManager, &PVPNetworkManager::connectionEstablished,
            this, &PVPPlay::onConnectionEstablished);
    connect(m_networkManager, &PVPNetworkManager::gameDataReceived,
            this, &PVPPlay::onGameDataReceived);

//    connect(m_networkManager, &PVPNetworkManager::connectionLost,
//            this, &PVPPlay::onConnectionLost);

//    connect(m_networkManager, &PVPNetworkManager::waitingForPlayer,
//            this, &PVPPlay::onWaitingForPlayer);
//    connect(m_networkManager, &PVPNetworkManager::opponentDisconnected,
//            this, &PVPPlay::onOpponentDisconnected);
//    connect(m_networkManager, &PVPNetworkManager::connectionFailed,
//            this, &PVPPlay::onConnectionFailed);

connect(m_pvpScene, &PVPGridScene::gameOver, this, &PVPPlay::onGameOver);

    connect(m_pvpScene, &PVPGridScene::turnChanged, this, &PVPPlay::onTurnChanged);

    connect(m_pvpScene, &PVPGridScene::timerVisibilityChanged,
            this, &PVPPlay::onTimerVisibilityChanged);

    connect(m_networkManager, &PVPNetworkManager::gameOverReceived,
            this, &PVPPlay::onGameOver, Qt::QueuedConnection); // 使用QueuedConnection确保顺序执行

    connect(m_pvpScene, &PVPGridScene::gameOver,
            this, &PVPPlay::onGameOver, Qt::QueuedConnection);

       connect(m_pvpScene, &PVPGridScene::boundaryViolationDetected,
               this, &PVPPlay::onBoundaryViolation);


}

void PVPPlay::onBoundaryViolation(bool isPlayerViolation) {
    if(m_isHost)
    {
        bool hostWon = !isPlayerViolation;

                  // 获取路径信息
                  const QVector<QPoint>& playerPath = m_pvpScene->getPlayerPath();
                  const QVector<QPoint>& opponentPath = m_pvpScene->getOpponentPath();

                  // 发送结果前确保双方都完成了移动
                  if(playerPath.size() > 1 && opponentPath.size() > 1)
                  {
                      QByteArray data;
                      QDataStream out(&data, QIODevice::WriteOnly);
                      out << (quint8)0x05 << hostWon;
                      m_networkManager->sendGameData(data);

                      onGameOver(hostWon);
                  }
              }
}


void PVPPlay::setupUI()
{
    setFixedSize(1200, 1300);
    setWindowTitle("谁与争锋");

    // 背景
    QLabel *background = new QLabel(this);
    background->setGeometry(0, 0, width(), height());
    background->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    background->setScaledContents(true);

    // 游戏视图
    m_view->setGeometry(20, 70, 1160, 1160);
    m_view->setStyleSheet("background: transparent; border: none;");
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_view->raise(); // 确保视图显示

    // 计时器标签
    m_timerLabel = new QLabel(this);
    m_timerLabel->setGeometry(450, 0, 300, 75);
    m_timerLabel->setAlignment(Qt::AlignCenter);
    m_timerLabel->setStyleSheet(
        "QLabel {"
        "   background: qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, "
        "                               stop:0 rgba(20, 20, 50, 220), "
        "                               stop:1 rgba(0, 0, 30, 220));"
        "   border-radius: 37px;"
        "   padding: 10px;"
        "   font-size: 40px;"
        "   font-weight: bold;"
        "   color: #00FFFF;"
        "   border: 3px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, "
        "                                     stop:0 #00FFFF, stop:1 #0080FF);"
        "   min-width: 100px;"
        "}"
    );

    // 退出按钮
    QPushButton *exitBtn = new QPushButton("退出游戏", this);
    exitBtn->setGeometry(450, 1230, 300, 70);
    exitBtn->setFont(QFont("华文行楷", 25, QFont::Bold));
    exitBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(44, 162, 222, 60%);"
        "   color: Black;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover { background-color: rgba(44, 162, 222, 70%); }"
        "QPushButton:pressed { background-color: rgba(44, 162, 222, 80%); }"
    );
    connect(exitBtn, &QPushButton::clicked, this, &PVPPlay::onExitButtonClicked);

    // 连接游戏场景信号
    connect(m_pvpScene, &PVPGridScene::gameOver, this, &PVPPlay::onGameOver);

    m_gameTimer->setInterval(1000); // 1秒间隔
    connect(m_gameTimer, &QTimer::timeout, this, [this](){
        if(m_pvpScene) {
            int timeLeft = m_pvpScene->getRemainingTime();
            m_timerLabel->setText(QString::number(timeLeft));
        }
    });
    m_gameTimer->start();

}


void PVPPlay::startAsHost(const QString& password, int timeout)
{
        m_isHost = true;
        m_password = password;          // 保存密码
        m_timeoutDuration = timeout;    // 保存超时时间
        m_networkManager->startAsHost(12345, password, timeout);
        //showWaitingDialog();
         qDebug() << "等待玩家连接...";
}

void PVPPlay::connectAsClient(const QString& address, quint16 port, const QString& password)
{
       m_isHost = false;
       m_password = password;          // 保存密码
       m_timeoutDuration = m_networkManager->timeoutDuration(); // 从网络管理器获取超时时间
       m_networkManager->connectAsClient(address, port, password);
       //showConnectionDialog();
       qDebug() << "正在连接服务器...";
}

void PVPPlay::onConnectionEstablished(const QString& opponentName)
{
    qDebug() << "Connection established with:" << opponentName;

        m_pvpScene->setOpponentName(opponentName);
        m_pvpScene->setNetworkManager(m_networkManager);
        m_timeoutDuration = m_networkManager->timeoutDuration();

        if(m_isHost) {
            QPoint hostPos(16, 0);  // 主机位置
            QPoint clientPos(0, 16); // 客户端位置

            // 设置主机自己的位置
            m_pvpScene->setPlayerPosition(hostPos);
            m_pvpScene->setOpponentPosition(clientPos);

            // 确保发送位置数据
            QByteArray positionData;
            QDataStream posStream(&positionData, QIODevice::WriteOnly);
            posStream << (quint8)0x04 << clientPos << hostPos;

            qDebug() << "Host sending position data - Size:" << positionData.size()
                     << "ClientPos:" << clientPos << "HostPos:" << hostPos;

            m_networkManager->sendGameData(positionData);

            // 立即开始游戏（主机）
            m_pvpScene->startNewGame(m_timeoutDuration, true);
        }
        // 客户端等待接收位置数据
}



void PVPPlay::onGameDataReceived(const QByteArray& data)
{
    QDataStream in(data);
       quint8 type;
       in >> type;

       switch(type) {
       case 0x02: { // 移动指令
           QPoint move;
           in >> move;
           m_pvpScene->handleOpponentMove(move);
           break;
       }
       case 0x05: { // 游戏结果指令
           bool hostWon;
           in >> hostWon;
           bool playerWon = !hostWon; // 客户端视角的胜负
           onGameOver(playerWon);
           break;
       }
       }
}

void PVPPlay::onExitButtonClicked()
{
    if(QMessageBox::question(this, "退出游戏", "确定要退出当前对战吗?这将判您失败。") == QMessageBox::Yes)
    {
        m_networkManager->disconnectFromHost();
        close();
    }
}

void PVPPlay::onGameOver(bool playerWon) {
    // 确保只处理一次游戏结束
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        if(m_gameEnded) return;
        m_gameEnded = true;

        // 更新用户统计数据
        updateUserStats(playerWon);

        // 如果是主机，先返回主菜单再发送结果
        if(m_isHost) {
            emit returnToLobby();
            QTimer::singleShot(100, this, [this, playerWon]() {
                showGameResult(playerWon);
                close();
            });
        }
        // 如果是客户端，等待接收结果后再处理
        else {
            showGameResult(playerWon);
            emit returnToLobby();
            close();
        }

}

void PVPPlay::showGameResult(bool playerWon)
{
    // 确保在主线程显示消息框
    QMetaObject::invokeMethod(this, [this, playerWon]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle("游戏结束");
        msgBox.setText(playerWon ? "恭喜你获胜了！" : "很遗憾，你输了");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setWindowFlags(msgBox.windowFlags() | Qt::WindowStaysOnTopHint);
        msgBox.exec();
    }, Qt::QueuedConnection);
}

void PVPPlay::onTurnChanged(bool isPlayerTurn)
{
    // 可以在这里更新UI显示当前回合状态
}

void PVPPlay::updateUserStats(bool playerWon) {
    if(m_currentUser) {
        int points = 20; // PvP基础积分

        // 更新PvP统计数据
        m_currentUser->addPvPResult(playerWon, points);

        // 保存用户数据
        UserFileManager::saveUser(*m_currentUser, "users.dat");
    }
}

void PVPPlay::onTimerVisibilityChanged(bool visible, bool isCritical)
{
    if(visible) {
          QString style = isCritical ?
              "color: red; font-weight: bold;" : "color: #00FFFF;";
          m_timerLabel->setStyleSheet(
              "QLabel {"
              "   background: qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, "
              "                               stop:0 rgba(20, 20, 50, 220), "
              "                               stop:1 rgba(0, 0, 30, 220));"
              "   border-radius: 37px;"
              "   padding: 10px;"
              "   font-size: 40px;"
              "   font-weight: bold;"
              "   " + style +
              "   border: 3px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, "
              "                                     stop:0 #00FFFF, stop:1 #0080FF);"
              "   min-width: 100px;"
              "}"
          );
      }
      m_timerLabel->setVisible(visible);
}

void PVPPlay::onReturnToLobbyConfirmed(bool keepRoomOpen)
{
    if(!keepRoomOpen) {
            m_networkManager->disconnectFromHost();
        }
        close();

        if(m_isHost && keepRoomOpen) {
            // 使用保存的密码和超时时间重新创建房间
            m_networkManager->startAsHost(12345, m_password, m_timeoutDuration);
            showWaitingDialog();
        } else {
            getGlobalModeWindow()->show();
        }
}


void PVPPlay::showWaitingDialog() {
    m_customDialog->setMessage("等待玩家加入");
        m_customDialog->setInformativeText("等待玩家连接中...");
        m_customDialog->addButton("取消", QMessageBox::RejectRole);

        connect(m_customDialog, &CustomDialog::rejected, this, [this](){
            m_networkManager->disconnectFromHost();
            close();
        });

        connect(m_networkManager, &PVPNetworkManager::connectionEstablished, this, [this](){
            m_customDialog->hide();
        });
        connect(m_networkManager, &PVPNetworkManager::connectionFailed, this, [this](){
            m_customDialog->hide();
        });

        m_customDialog->show();
}

void PVPPlay::showConnectionDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("连接中");
    dialog.setFixedSize(400, 200);

    QVBoxLayout layout(&dialog);

    QLabel label("正在连接服务器...", &dialog);
    label.setAlignment(Qt::AlignCenter);
    layout.addWidget(&label);

    QPushButton cancelBtn("取消连接", &dialog);
    layout.addWidget(&cancelBtn);

    connect(&cancelBtn, &QPushButton::clicked, [&]() {
        m_networkManager->disconnectFromHost();
        dialog.reject();
        close();
    });

    connect(m_networkManager, &PVPNetworkManager::connectionEstablished, &dialog, &QDialog::accept);
    connect(m_networkManager, &PVPNetworkManager::connectionFailed, &dialog, &QDialog::reject);

    dialog.exec();
}

void PVPPlay::showDisconnectMessage(bool playerWon) {
    QMessageBox::information(this, "游戏结束",
        playerWon ? "对方断开连接，您获胜了！" : "您已断开连接");
    emit returnToLobby();
    close();
}

void PVPPlay::onConnectionLost() {
//    // 如果游戏正在进行中，则视为对方断开连接
//        if(m_pvpScene->getState() != PVPGridScene::GameOver) {
//            bool playerWon = true; // 对方断开，玩家获胜
//            onGameOver(playerWon);
//        } else {
//            QMessageBox::information(this, "连接断开", "与服务器的连接已断开");
//            emit returnToLobby();
//            close();
//        }
}

void PVPPlay::onWaitingForPlayer() {
    // 已经在showWaitingDialog中处理
}

void PVPPlay::onOpponentDisconnected() {
    QMessageBox::information(this, "游戏结束", "对手已断开连接，你获得了胜利");
        emit returnToLobby();
        close();
}

void PVPPlay::onConnectionFailed(const QString& reason)
{
    QMessageBox::critical(this, "连接失败", reason);
    close();
}

PVPPlay::~PVPPlay()
{
    qDebug() << "PVPPlay destructor";
        if(m_networkManager) {
            m_networkManager->disconnectFromHost();
        }
        // 注意不要删除m_currentUser，它由外部管理
}
