#include "PVPGridScene.h"
#include <QMessageBox>
#include<QRandomGenerator>
#include<QGraphicsSceneMouseEvent>
#include <QTimer>
#include<QGraphicsRectItem>
#include<QDebug>
#include"gamedefine.h"


PVPGridScene::PVPGridScene(int gridSize, QObject* parent)
    : Gridscene(gridSize, parent),
      m_isHost(false) ,
      m_gameTimer(new QTimer(this)),
      m_remainingTime(0),
      m_state(Waiting),
      m_isPlayerFirst(false),
      m_isPlayerReady(false),
      m_startPositionsInitialized(false)

{
    drawGrid(); // 绘制基础网格
    connect(m_gameTimer, &QTimer::timeout, this, &PVPGridScene::onTimeOut);
}

PVPGridScene::~PVPGridScene()
{
    if(m_gameTimer) {
        m_gameTimer->stop();
    }
}

void PVPGridScene::onBoundaryViolation(bool isPlayerViolation)
{
    if(m_isHost)
    {
            bool hostWon = !isPlayerViolation;

            // 1. 先本地处理游戏结束
            endGame(hostWon);

            // 2. 延迟发送游戏结果给客户端，确保主机先处理完毕
            QTimer::singleShot(100, [this, hostWon]() {
                if(m_networkManager) {
                    QByteArray data;
                    QDataStream out(&data, QIODevice::WriteOnly);
                    out << (quint8)0x05 << hostWon;
                    m_networkManager->sendGameData(data);
                }
            });
        }
}


void PVPGridScene::startNewGame(int timeoutDuration, bool isPlayerFirst)
{
    m_remainingTime = timeoutDuration;
       m_isPlayerFirst = isPlayerFirst;
       m_state = isPlayerFirst ? PlayerTurn : OpponentTurn;

       clearAllItems();

       // 只有位置已初始化才设置路径
       if(m_startPositionsInitialized) {
           m_playerPath.clear();
           m_playerPath.append(m_playerStartPos);
           m_opponentPath.clear();
           m_opponentPath.append(m_opponentStartPos);

           qDebug() << "Starting game with positions - Player:" << m_playerStartPos
                    << "Opponent:" << m_opponentStartPos;
       }

       updateGridDisplay();

       if(m_state == PlayerTurn) {
           m_gameTimer->start(1000);
       }
}

void PVPGridScene::confirmReady()
{
    if(m_isHost) {
            m_isOpponentReady = true;
            // 主机不需要额外操作，等待客户端准备
        } else {
            m_isPlayerReady = true;
            // 客户端发送准备指令
            if(m_networkManager) {
                QByteArray data;
                QDataStream out(&data, QIODevice::WriteOnly);
                out << (quint8)0x03; // 准备就绪指令
                m_networkManager->sendGameData(data);
            }
        }

        // 不在这里开始游戏，等待网络管理器的readyToStart信号
}

void PVPGridScene::startGame()
{
    // 确保双方都准备好了
       if(!(m_isPlayerReady && m_isOpponentReady)) return;

       // 开始游戏逻辑
       m_state = m_isPlayerFirst ? PlayerTurn : OpponentTurn;
       emit timerVisibilityChanged(m_state == PlayerTurn);

       if(m_state == PlayerTurn) {
           m_gameTimer->start(1000);
       }

       // 清除准备提示
       clearAllItems();
       updateGridDisplay();
}

void PVPGridScene::handleOpponentMove(const QPoint& move)
{
    if(m_state != OpponentTurn) return;

       m_opponentPath.append(move);
       updateGridDisplay();

       // 双方都移动后才检查边界
       if(checkBoundaryViolation()) {
           return;
       }

       m_state = PlayerTurn;
       emit turnChanged(true);
       emit timerVisibilityChanged(true, false);
       m_remainingTime = m_networkManager->timeoutDuration();
       m_gameTimer->start(1000);
}

void PVPGridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_state != PlayerTurn) return;

        QPoint clickPos(
            static_cast<int>(event->scenePos().x()) / CELL_SIZE,
            static_cast<int>(event->scenePos().y()) / CELL_SIZE
        );

        if(isValidMove(clickPos))
        {
            AudioManager::instance()->playEffect();
            m_playerPath.append(clickPos);
            updateGridDisplay();

            // 发送移动后检查边界
            sendMoveToOpponent(clickPos);

            // 不在这里检查边界，等待对方移动完成
            m_state = OpponentTurn;
            emit turnChanged(false);
            emit timerVisibilityChanged(false);
            m_gameTimer->stop();
        }
}

void PVPGridScene::onTimeOut()
{
    if(m_remainingTime > 0) {
        m_remainingTime--;

        // 最后3秒变红
        if(m_remainingTime <= 3) {
            emit timerVisibilityChanged(true, true); // 传递两个参数
        } else {
            emit timerVisibilityChanged(true, false); // 正常状态
        }

        if(m_remainingTime == 0) {
            QPoint autoMove = findRandomValidMove();
            if(autoMove.x() != -1) {
                m_playerPath.append(autoMove);
                updateGridDisplay();

                if(checkBoundaryViolation()) {
                    endGame(false);
                    return;
                }

                sendMoveToOpponent(autoMove);
                m_state = OpponentTurn;
                emit turnChanged(false);
                emit timerVisibilityChanged(false); // 隐藏计时器
                m_gameTimer->stop();
            } else {
                endGame(false);
            }
        }
    }
}

QPoint PVPGridScene::findRandomValidMove() const
{
    if(m_playerPath.isEmpty()) return QPoint(-1, -1);

    QPoint lastPos = m_playerPath.last();
    QVector<QPoint> possibleMoves;
    const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};

    for(const QPoint& dir : directions) {
        QPoint newPos = lastPos + dir;
        if(isValidMove(newPos)) {
            possibleMoves.append(newPos);
        }
    }

    if(possibleMoves.isEmpty()) {
        return QPoint(-1, -1);
    }

    return possibleMoves[QRandomGenerator::global()->bounded(possibleMoves.size())];
}

void PVPGridScene::setPlayerPosition(const QPoint& pos)
{
    if(!m_startPositionsInitialized)
    {
            m_playerStartPos = pos;
            qDebug() << "Player position set to:" << pos;

     }
}

void PVPGridScene::setOpponentPosition(const QPoint& pos)
{
    if(!m_startPositionsInitialized)
    {
           m_opponentStartPos = pos;
           m_startPositionsInitialized = true;
           qDebug() << "Opponent position set - Starting game now";

           // 确保网络管理器已设置
           if(m_networkManager) {
               startNewGame(m_networkManager->timeoutDuration(), false);
           }
       }

}


void PVPGridScene::endGame(bool playerWon, bool isDisconnect)
{
    m_state = GameOver;
       m_gameTimer->stop();

       if(isDisconnect) {
           addTextItem(QPoint(8,8), playerWon ? "对方断开连接\n您获胜了!" : "您已断开连接\n游戏结束",
                      QPointF(-100, -20), 20, playerWon ? Qt::green : Qt::red);
       } else {
           addTextItem(QPoint(8,8), playerWon ? "恭喜您获胜!" : "很遗憾您输了",
                      QPointF(-80, -20), 24, playerWon ? Qt::green : Qt::red);
       }

       // 使用QueuedConnection确保游戏结束信号在主线程处理
       QMetaObject::invokeMethod(this, [this, playerWon]() {
           emit gameOver(playerWon);
       }, Qt::QueuedConnection);
}


int PVPGridScene::getRemainingTime() const
{
    return m_remainingTime;
}

void PVPGridScene::setOpponentName(const QString& name)
{
    m_opponentName = name;
}

void PVPGridScene::setNetworkManager(PVPNetworkManager* manager)
{
    if (m_networkManager) {
        disconnect(m_networkManager, nullptr, this, nullptr);
    }

    m_networkManager = manager;

    if (m_networkManager) {
        m_isHost = m_networkManager->isHost();  // 设置主机状态
        connect(m_networkManager, &PVPNetworkManager::opponentDisconnected,
                this, &PVPGridScene::onOpponentDisconnected);
    }
}

void PVPGridScene::sendMoveToOpponent(const QPoint& move)
{
    if(m_networkManager)
    {
            QByteArray data;
            QDataStream out(&data, QIODevice::WriteOnly);
            out << (quint8)0x02 << move; // 只发送移动位置，不发送起点
            m_networkManager->sendGameData(data);
      }
}

void PVPGridScene::onOpponentDisconnected()
{
    endGameWithDisconnect(true); // 对手断开，玩家获胜
}

void PVPGridScene::endGameWithDisconnect(bool playerWon)
{
    m_state = GameOver;
    m_gameTimer->stop();

    addTextItem(QPoint(8,8), playerWon ? "对方断开连接\n您获胜了!" : "您已断开连接\n游戏结束",
               QPointF(-100, -20), 20, playerWon ? Qt::green : Qt::red);

    emit gameOver(playerWon);
}

void PVPGridScene::updateGridDisplay()
{
    clearAllItems();
        drawGrid();

        // 始终绘制起点位置
        addPathCell(m_playerStartPos, true, true, 0);
        addPathCell(m_opponentStartPos, false, true, 0);

        // 绘制玩家路径(从第二个点开始)
        for(int i = 1; i < m_playerPath.size(); ++i) {
            addPathCell(m_playerPath[i], true, false, i);
        }

        // 绘制对手路径(从第二个点开始)
        for(int i = 1; i < m_opponentPath.size(); ++i)
        {
            addPathCell(m_opponentPath[i], false, false, i);
        }
}

bool PVPGridScene::isValidMove(const QPoint& pos) const
{
    qDebug()<<pos.x()<<" "<<pos.y()<<endl;
    // 边界检查
       if(pos.x() < 0 || pos.y() < 0 || pos.x() > m_gridSize || pos.y() > m_gridSize) {
           qDebug() << "Invalid move: out of bounds";
           return false;
       }

       // 检查是否已被占据
       if(isPositionOccupied(pos)) {
           qDebug() << "Invalid move: position occupied";
           return false;
       }

       // 第一步移动必须从起点出发
       QPoint lastPos = m_playerPath.isEmpty() ? m_playerStartPos : m_playerPath.last();
       int distance = qAbs(pos.x() - lastPos.x()) + qAbs(pos.y() - lastPos.y());

       if(distance != 1)
       {
           qDebug() << "Invalid move: not adjacent to last position";
           return false;
       }

       return true;
}

bool PVPGridScene::checkBoundaryViolation()
{
    // 只有当双方都有移动时才检查
        if(m_playerPath.size() <= 1 || m_opponentPath.size() <= 1) {
            return false;
        }

        // 计算相对路径
        QVector<QPoint> relativePath;
        QPoint centerPos(8, 8);
        relativePath.append(centerPos);

        // 从第1步开始计算(跳过起点)
        for(int i = 1; i < qMax(m_playerPath.size(), m_opponentPath.size()); ++i) {
            QPoint playerMove = (i < m_playerPath.size()) ?
                m_playerPath[i] - m_playerPath[i-1] : QPoint(0,0);
            QPoint opponentMove = (i < m_opponentPath.size()) ?
                m_opponentPath[i] - m_opponentPath[i-1] : QPoint(0,0);

            // 主机和客户端移动方向相反
            QPoint newPos = relativePath.last() + (opponentMove - playerMove);
            relativePath.append(newPos);

            // 检查是否越界
            if(newPos.x() < 0 || newPos.y() < 0 || newPos.x() >= 17 || newPos.y() >= 17) {
                // 确定是谁导致了越界
                bool isPlayerViolation = (playerMove != QPoint(0,0));
                emit boundaryViolationDetected(isPlayerViolation);
                return true;
            }
        }
        return false;
}

bool PVPGridScene::isPositionOccupied(const QPoint& pos) const
{
    // 检查玩家路径
    for(const QPoint& p : m_playerPath)
        if(p == pos) return true;

    // 检查对手路径
    for(const QPoint& p : m_opponentPath)
        if(p == pos) return true;


    // 检查对手起点
    if(pos == m_opponentStartPos) return true;

    return false;
}

void PVPGridScene::clearAllItems()
{
    QList<QGraphicsItem*> itemsToRemove;
    for(QGraphicsItem* item : items()) {
        if(item->data(0).toString() != "base_grid") {
            itemsToRemove.append(item);
        }
    }

    for(QGraphicsItem* item : itemsToRemove) {
        removeItem(item);
        delete item;
    }
}

void PVPGridScene::addPathCell(const QPoint& pos, bool isPlayer, bool isStart, int step)
{
    QGraphicsRectItem* cell = new QGraphicsRectItem(
        pos.x() * CELL_SIZE,
        pos.y() * CELL_SIZE,
        CELL_SIZE, CELL_SIZE);

    if(isPlayer) {
        cell->setBrush(isStart ? QColor(100, 255, 100, 220) : QColor(150, 255, 150, 220));
        cell->setData(0, isStart ? "player_start" : "player_path");
    } else {
        cell->setBrush(isStart ? QColor(255, 100, 100, 220) : QColor(255, 150, 150, 220));
        cell->setData(0, isStart ? "opponent_start" : "opponent_path");
    }

    cell->setZValue(1);
    addItem(cell);

    if(isStart) {
        addTextItem(pos, isPlayer ? "己方" : "对手",
                   QPointF(CELL_SIZE/4 -13, CELL_SIZE/4 +5), 14, Qt::white);
    } else {
        addTextItem(pos, QString::number(step),
                   QPointF(CELL_SIZE/3, CELL_SIZE/3), 14,
                   isPlayer ? Qt::white : QColor(255, 255, 200));
    }
}

void PVPGridScene::addTextItem(const QPoint& pos, const QString& text,
                             const QPointF& offset, int fontSize, const QColor& color)
{
    QGraphicsTextItem* textItem = new QGraphicsTextItem(text);
    textItem->setDefaultTextColor(color);
    textItem->setFont(QFont("华文行楷", fontSize, QFont::Bold));
    textItem->setPos(pos.x() * CELL_SIZE + offset.x(),
                    pos.y() * CELL_SIZE + offset.y());
    textItem->setZValue(2);
    addItem(textItem);
}


QPoint PVPGridScene::getPlayerStartPos() const {
    return m_playerStartPos;
}

QPoint PVPGridScene::getOpponentStartPos() const {
    return m_opponentStartPos;
}

bool PVPGridScene::isStartPosInitialized() const {
    return m_startPositionsInitialized;
}

//void PVPGridScene::setOpponentStartPos(const QPoint& pos) {
//    m_opponentStartPos = pos;
//    m_startPositionsInitialized = true;
//}
