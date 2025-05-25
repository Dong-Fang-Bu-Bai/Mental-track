#include "BattleGridScene.h"
#include <QRandomGenerator>
#include <QTimer>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsRectItem>
#include<QDebug>
#include"gamedefine.h"

BattleGridScene::BattleGridScene(int gridSize, QObject* parent)
    : Gridscene(gridSize, parent), m_state(GameOver), m_difficulty(Easy),
      m_aiStrategy(nullptr)
{

    drawGrid(); // 确保初始绘制网格
    markBaseGridCells(); // 标记基础网格

}

void BattleGridScene::restoreGridTransparency()
{
    QList<QGraphicsItem*> items = this->items();
    for(QGraphicsItem* item : items)
    {
        if(QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(item))
        {
            // 判断是否是基础网格（通过位置是否在网格范围内）
            QPoint pos(rect->rect().x()/CELL_SIZE, rect->rect().y()/CELL_SIZE);
            if(pos.x() >= 0 && pos.y() >= 0 &&
               pos.x() < m_gridSize && pos.y() < m_gridSize)
            {
                QColor color = rect->brush().color();
                color.setAlpha(220); // 恢复透明度
                rect->setBrush(color);
            }
        }
    }
}


void BattleGridScene::startNewGame(Difficulty difficulty)
{

    qDebug() << "BattleGridScene::startNewGame - difficulty:" << difficulty;

    m_difficulty = difficulty;

    // 根据难度设置AI策略
       switch(difficulty)
       {
       case Easy:
           m_aiStrategy = std::make_unique<RandomStrategy>();
           break;
       case Medium:
           m_aiStrategy = std::make_unique<IntermediateStrategy>();
           break;
       case Hard:
           m_aiStrategy = std::make_unique<AdvancedStrategy>();
           break;
       }

    // 直接清除路径并重置状态
    qDebug() << "Clearing old items";

    QList<QGraphicsItem*> items = this->items();
    for(QGraphicsItem* item : items)
    {
        if(item->data(0).toString() != "base_grid")
        {
            removeItem(item);
            delete item;
        }
    }

    qDebug() << "Clearing paths";
    m_playerPath.clear();
    m_aiPath.clear();

    // 随机分配起始位置（对角）
    int corner = QRandomGenerator::global()->bounded(4);
    QPoint startPositions[4] = {QPoint(0,0), QPoint(16,0), QPoint(0,16), QPoint(16,16)};

    qDebug() << "Player start position:" << startPositions[corner];
    qDebug() << "AI start position:" << startPositions[(corner + 2) % 4];

    m_playerPath.append(startPositions[corner]);
    m_aiStartPos = startPositions[(corner + 2) % 4];

    // 更新状态
    m_state = PlayerTurn;

    qDebug() << "Updating grid display";

    updateGridDisplay();

    emit gameStarted(); // 通知BattlePlay游戏已开始
    emit stateChanged(); // 通知状态变化


    qDebug() << "New game initialized";
}

void BattleGridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
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

        if(checkBoundaryViolation())
        {
            stopGame(); // 先停止游戏
            emit gameOver(false);
            return;
        }

        m_state = AITurn;
        QTimer::singleShot(500, this, &BattleGridScene::makeAIMove);
    }
}

void BattleGridScene::makeAIMove()
{
    if(m_state != AITurn) return;

        QPoint lastPos = m_aiPath.isEmpty() ? m_aiStartPos : m_aiPath.last();
        QVector<QPoint> possibleMoves;

        // 获取所有有效移动
        const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};
        for(const QPoint& dir : directions) {
            QPoint newPos = lastPos + dir;
            if(isValidMove(newPos))
                possibleMoves.append(newPos);
        }

        if(possibleMoves.isEmpty()) {
            stopGame();
            emit gameOver(true);
            return;
        }

        // 使用策略计算最佳移动
        QPoint selectedMove = m_aiStrategy->calculateMove(
            lastPos, possibleMoves, m_playerPath, m_aiPath);

        m_aiPath.append(selectedMove);
        updateGridDisplay();

        if(checkBoundaryViolation()) {
            stopGame();
            emit gameOver(true);
            return;
        }

        m_state = PlayerTurn;
        emit stateChanged();


}

void BattleGridScene::makeRandomAIMove()
{
    // 原有随机移动逻辑
    QPoint lastPos = m_aiPath.isEmpty() ? m_aiStartPos : m_aiPath.last();
    QVector<QPoint> possibleMoves;

    const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};
    for(const QPoint& dir : directions)
    {
        QPoint newPos = lastPos + dir;
        if(isValidMove(newPos))
            possibleMoves.append(newPos);
    }

    if(possibleMoves.isEmpty())
    {
        stopGame(); // 先停止游戏
        emit gameOver(true);
        return;
    }

    QPoint selectedMove = possibleMoves[QRandomGenerator::global()->bounded(possibleMoves.size())];
    m_aiPath.append(selectedMove);
    updateGridDisplay();

    if(checkBoundaryViolation())
    {
        stopGame(); // 先停止游戏
        emit gameOver(true);
        return;
    }



    m_state = PlayerTurn;
    emit stateChanged(); // 通知状态变化

}

void BattleGridScene::makeStrategicAIMove()
{
//    QPoint lastPos = m_aiPath.isEmpty() ? m_aiStartPos : m_aiPath.last();
//    QVector<QPoint> possibleMoves;

//    const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};
//    for(const QPoint& dir : directions) {
//        QPoint newPos = lastPos + dir;
//        if(isValidMove(newPos))
//            possibleMoves.append(newPos);
//    }

//    if(possibleMoves.isEmpty()) {
//        emit gameOver(true);
//        return;
//    }

//    QPoint selectedMove = findBestMove(possibleMoves);
//    m_aiPath.append(selectedMove);
//    updateGridDisplay();

//    if(checkBoundaryViolation()) {
//        emit gameOver(true);
//        return;
//    }


//    m_state = PlayerTurn;
//    emit stateChanged(); // 通知状态变化

     makeAIMove(); // 现在统一使用策略模式

}

QPoint BattleGridScene::findBestMove(const QVector<QPoint>& possibleMoves)
{
//    // 声明方向数组
//    const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};

//    // 中级难度：优先向中心移动
//    if(m_difficulty == Medium)
//    {
//        QPoint center(8, 8);
//        QPoint bestMove;
//        int minDistance = INT_MAX;

//        for(const QPoint& move : possibleMoves)
//        {
//            int distance = qAbs(move.x() - center.x()) + qAbs(move.y() - center.y());
//            if(distance < minDistance)
//            {
//                minDistance = distance;
//                bestMove = move;
//            }
//        }
//        return bestMove;
//    }
//    // 高级难度：更复杂的策略
//    else
//    {
//        // 1. 优先向中心移动
//        QPoint center(8, 8);
//        QVector<QPoint> centerMoves;
//        int minDistance = INT_MAX;

//        for(const QPoint& move : possibleMoves)
//        {
//            int distance = qAbs(move.x() - center.x()) + qAbs(move.y() - center.y());
//            if(distance < minDistance)
//            {
//                minDistance = distance;
//                centerMoves.clear();
//                centerMoves.append(move);
//            }
//            else if(distance == minDistance)
//            {
//                centerMoves.append(move);
//            }
//        }

//        // 2. 在最优中心移动中，选择能限制玩家移动的
//        if(!m_playerPath.isEmpty())
//        {
//            QPoint playerPos = m_playerPath.last();
//            QPoint bestMove;
//            int maxPlayerDistance = -1;

//            for(const QPoint& move : centerMoves)
//            {
//                // 计算这个移动后，玩家可能的移动方向数量
//                int playerDirections = 0;
//                for(const QPoint& dir : directions)
//                {
//                    QPoint newPos = playerPos + dir;
//                    if(isValidMove(newPos) && newPos != move)
//                        playerDirections++;
//                }

//                if(playerDirections > maxPlayerDistance)
//                {
//                    maxPlayerDistance = playerDirections;
//                    bestMove = move;
//                }
//            }
//            return bestMove;
//        }

//        // 默认返回第一个中心移动
//        return centerMoves.first();
//    }
    return m_aiStrategy->calculateMove
            (
            m_aiPath.isEmpty() ? m_aiStartPos : m_aiPath.last(),
            possibleMoves,
            m_playerPath,
            m_aiPath
            );

}



bool BattleGridScene::isValidMove(const QPoint& pos) const
{
    // 边界检查
       if(pos.x() < 0 || pos.y() < 0 || pos.x() >= m_gridSize || pos.y() >= m_gridSize)
           return false;

       // 检查是否已被占据（包括所有路径点和起点）
       if(isPositionOccupied(pos))
           return false;

       // 必须与最后位置相邻
       QPoint lastPos = m_state == PlayerTurn ?
           (m_playerPath.isEmpty() ? QPoint(-1,-1) : m_playerPath.last()) :
           (m_aiPath.isEmpty() ? m_aiStartPos : m_aiPath.last());

       return qAbs(pos.x() - lastPos.x()) + qAbs(pos.y() - lastPos.y()) == 1;
}

QVector<QPoint> BattleGridScene::calculateRelativePath() const
{
    QVector<QPoint> relativePath;
    QPoint centerPos(8, 8); // (9,9)对应QPoint(8,8)
    relativePath.append(centerPos);

    for(int i = 1; i < qMax(m_playerPath.size(), m_aiPath.size()); ++i)
    {
        QPoint playerMove = (i < m_playerPath.size()) ?
            m_playerPath[i] - m_playerPath[i-1] : QPoint(0,0);
        QPoint aiMove = (i < m_aiPath.size()) ?
            m_aiPath[i] - (i == 1 ? m_aiStartPos : m_aiPath[i-1]) : QPoint(0,0);

        QPoint newPos = relativePath.last() + (aiMove - playerMove);
        relativePath.append(newPos);
    }
    return relativePath;
}

bool BattleGridScene::checkBoundaryViolation() const
{
    for(const QPoint& p : calculateRelativePath()) {
        if(p.x() < 0 || p.y() < 0 || p.x() >= 17 || p.y() >= 17)
            return true;
    }
    return false;
}

void BattleGridScene::updateGridDisplay()
{
    qDebug() << "Updating grid display - start";

    // 使用更安全的清除方式
    clearAllItems();

    // 确保网格透明度
    restoreGridTransparency();

    // 绘制玩家路径
    if(!m_playerPath.isEmpty())
    {
        // 绘制玩家起点
        addPathCell(m_playerPath.first(), true,0);

        // 绘制玩家路径
        for(int i = 1; i < m_playerPath.size(); ++i)
        {
            addPathCell(m_playerPath[i], false, i);
        }
    }

    // 绘制AI路径
    if(!m_aiPath.isEmpty())
    {
        // 绘制AI起点
        addAICell(m_aiStartPos, true,0);

        // 绘制AI路径
        for(int i = 0; i < m_aiPath.size(); ++i)
        {
            addAICell(m_aiPath[i], false, i+1);
        }
    }

    qDebug() << "Updating grid display - done";



}


void BattleGridScene::markBaseGridCells()
{
    QList<QGraphicsItem*> items = this->items();
        for(QGraphicsItem* item : items)
        {
            if(QGraphicsRectItem* rect = qgraphicsitem_cast<QGraphicsRectItem*>(item))
            {
                // 只设置一次透明度
                if(item->data(0).isNull())
                {
                    rect->setData(0, "base_grid");
                    QColor color(93, 155, 213, 220); // 直接使用透明颜色
                    rect->setBrush(color);
                    rect->setZValue(-1);
                }
            }
        }
}

bool BattleGridScene::isPositionOccupied(const QPoint& pos) const
{
    // 检查是否在玩家路径中
    for(const QPoint& p : m_playerPath)
        if(p == pos) return true;

    // 检查是否在AI路径中
    for(const QPoint& p : m_aiPath)
        if(p == pos) return true;

    // 检查是否是AI起点
    if(pos == m_aiStartPos) return true;

    return false;
}




void BattleGridScene::handleTimeout()
{
    if(m_state != PlayerTurn) return;

        // 自动选择移动
        QPoint lastPos = m_playerPath.isEmpty() ? QPoint(-1,-1) : m_playerPath.last();
        const QPoint directions[4] = {QPoint(0,1), QPoint(1,0), QPoint(0,-1), QPoint(-1,0)};
        QVector<QPoint> possibleMoves;

        // 先收集所有可能的移动
        for(const QPoint& dir : directions) {
            QPoint newPos = lastPos + dir;
            if(isValidMove(newPos)) {
                possibleMoves.append(newPos);
            }
        }

        // 如果没有有效移动，才判负
        if(possibleMoves.isEmpty()) {
            stopGame();
            emit gameOver(false);
            return;
        }

        // 随机选择一个有效移动
        QPoint selectedMove = possibleMoves[QRandomGenerator::global()->bounded(possibleMoves.size())];
        m_playerPath.append(selectedMove);
        updateGridDisplay();

        // 检查移动后是否越界
        if(checkBoundaryViolation()) {
            stopGame();
            emit gameOver(false);
            return;
        }

        // 切换到AI回合
        m_state = AITurn;
        emit stateChanged();
        QTimer::singleShot(500, this, &BattleGridScene::makeAIMove);
}



void BattleGridScene::clearAllItems()
{
    QList<QGraphicsItem*> itemsToRemove;
    for(QGraphicsItem* item : items())
    {
        if(item->data(0).toString() != "base_grid")
        {
            itemsToRemove.append(item);
        }
    }

    for(QGraphicsItem* item : itemsToRemove)
    {
        removeItem(item);
        delete item;
    }
}

void BattleGridScene::addPathCell(const QPoint& pos, bool isStart, int step)
{
    QGraphicsRectItem* cell = new QGraphicsRectItem
    (   pos.x() * CELL_SIZE,
        pos.y() * CELL_SIZE,
        CELL_SIZE, CELL_SIZE);

    cell->setBrush(isStart ? QColor(100, 150, 255, 220) : QColor(112, 187, 230, 220));
    cell->setData(0, isStart ? "player_start" : "player_path");
    cell->setZValue(1);
    addItem(cell);

    if(isStart)
    {
        addTextItem(pos, "玩家", QPointF(CELL_SIZE/4 -13, CELL_SIZE/4 +5), 14, Qt::white);
    }
    else
    {
        addTextItem(pos, QString::number(step), QPointF(CELL_SIZE/3, CELL_SIZE/3), 14, Qt::white);
    }
}


void BattleGridScene::addAICell(const QPoint& pos, bool isStart, int step)
{
    QGraphicsRectItem* cell = new QGraphicsRectItem(
    pos.x() * CELL_SIZE,
    pos.y() * CELL_SIZE,
    CELL_SIZE, CELL_SIZE);

    cell->setBrush(isStart ? QColor(255, 100, 100, 220) : QColor(255, 150, 150, 220));
    cell->setData(0, isStart ? "ai_start" : "ai_path");
    cell->setZValue(1);
    addItem(cell);

    if(isStart)
    {
        addTextItem(pos, "电脑", QPointF(CELL_SIZE/4 -13, CELL_SIZE/4 +5), 14, Qt::white);
    }
    else
    {
        addTextItem(pos, QString::number(step), QPointF(CELL_SIZE/3, CELL_SIZE/3), 14, QColor(255, 255, 200));
    }
}


void BattleGridScene::addTextItem(const QPoint& pos, const QString& text,
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


BattleGridScene::~BattleGridScene()
{
    qDebug() << "~BattleGridScene - Begin";
        m_state = GameOver;
        clearAllItems();
        qDebug() << "~BattleGridScene - End";
}

