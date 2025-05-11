#include "Workshopgridscene.h"
#include "Pathcalculator.h"
#include <fstream>
#include <string>
#include<direct.h>
#include <errno.h>

Workshopgridscene::Workshopgridscene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent),m_currentMode(PlayerPath)
{
    drawGrid();
}

void Workshopgridscene::setEditMode(EditMode mode)
{
    m_currentMode = mode;
    updateGridDisplay(); // 使用统一的更新函数
}


void Workshopgridscene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QPoint currentPos(
        static_cast<int>(event->scenePos().x()) / CELL_SIZE,
        static_cast<int>(event->scenePos().y()) / CELL_SIZE
    );

    // Boundary check
    if (currentPos.x() < 0 || currentPos.y() < 0 ||
        currentPos.x() >= m_gridSize || currentPos.y() >= m_gridSize) {
        return;
    }

    // Check if cell is locked (player path in enemy mode)
    QList<QGraphicsItem*> items = this->items(event->scenePos());
    for (QGraphicsItem* item : items) {
        if (item->data(0) == "locked") {
            return;
        }
    }

    if (m_currentMode == PlayerPath) {
        // First click starts the path
        if (m_playerPath.isEmpty()) {
            m_playerPath.append(currentPos);
            drawPathCell(currentPos, 1, QColor(135, 206, 250));
            return;
        }

        // Subsequent clicks must be adjacent
        if (!isAdjacent(currentPos, m_playerPath.last())) {
            return;
        }

        // Add to path
        m_playerPath.append(currentPos);
        drawPathCell(currentPos, m_playerPath.size(), QColor(135, 206, 250));

//        // If path is long enough, emit signal
//        if (m_playerPath.size() >= 3) {
//            emit pathCompleted();
//        }
    }
    else if (m_currentMode == EnemyPath)
    {

        // First click starts the path
        if (m_enemyPath.isEmpty())
        {
            m_enemyPath.append(currentPos);
            drawPathCell(currentPos, 1, Qt::yellow);
            return;
        }

        // Subsequent clicks must be adjacent
        if (!isAdjacent(currentPos, m_enemyPath.last()))
        {
            return;
        }

        // Add to path
        m_enemyPath.append(currentPos);
        drawPathCell(currentPos, m_enemyPath.size(), Qt::yellow);


    }
}

// 新方法：绘制路径单元格（不删除网格线）
void Workshopgridscene::drawPathCell(const QPoint& pos, int step, const QColor& color)
{
    // 只删除非锁定的路径单元格
    QList<QGraphicsItem*> itemsToRemove;
    for (QGraphicsItem* item : items())
    {
        if (item->data(0).toString() == "path_cell" &&
            item->sceneBoundingRect().contains(pos.x() * CELL_SIZE + CELL_SIZE/2,
                                             pos.y() * CELL_SIZE + CELL_SIZE/2) &&
            item->data(0) != "locked") {  // 不删除锁定的项目
            itemsToRemove.append(item);
        }
    }

    for (QGraphicsItem* item : itemsToRemove) {
        removeItem(item);
        delete item;
    }

    // 创建新的路径单元格
    QGraphicsRectItem* cell = new QGraphicsRectItem(
        pos.x() * CELL_SIZE, pos.y() * CELL_SIZE,
        CELL_SIZE, CELL_SIZE);
    cell->setBrush(color);
    cell->setData(0, "path_cell"); // 标记为路径单元格
    addItem(cell);

    // 添加步数文本
    QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem(QString::number(step));
    textItem->setData(0, "path_text"); // 标记为路径文本
    QFont font;
    font.setPointSize(12);
    textItem->setFont(font);
    textItem->setBrush(QBrush(Qt::black));

    // 居中文本
    QRectF textRect = textItem->boundingRect();
    textItem->setPos(
        pos.x() * CELL_SIZE + (CELL_SIZE - textRect.width()) / 2,
        pos.y() * CELL_SIZE + (CELL_SIZE - textRect.height()) / 2
    );

    addItem(textItem);
}


bool Workshopgridscene::isAdjacent(const QPoint& p1, const QPoint& p2) const
{
    return (qAbs(p1.x() - p2.x()) + qAbs(p1.y() - p2.y())) == 1;
}

bool Workshopgridscene::verifyPaths()
{
    // Check if enemy path ends adjacent to player endpoint
    if (!m_enemyPath.isEmpty() && !isAdjacent(m_enemyPath.last(), m_playerPath.last()))
    {
        emit errorOccurred("双方终点不一致");
        return false;
    }

    m_enemyPath.append(m_playerPath.last());


    // Calculate relative path
    QVector<QPoint> relativePath;
    if (!Pathcalculator::setPaths(m_playerPath, m_enemyPath, relativePath, m_gridSize))
    {
        emit errorOccurred("相对路径无效！");
        return false;
    }

    return true;
}

bool Workshopgridscene::saveToFile(const std::string& fileName, const  std::string&  userName)
{
    // 创建目录路径
        std::string dirPath = "./WorkShop/" + userName;
        // 创建目录（跨平台方式）

        int ret = _mkdir(dirPath.c_str());

        if (ret != 0 && errno != EEXIST) { // EEXIST表示目录已存在
            emit errorOccurred("无法创建用户目录");
            return false;
        }

        // 创建文件路径
        std::string filePath = dirPath + "/" + fileName + ".txt";

        // 打开文件
        std::ofstream file(filePath);
        if (!file.is_open()) {
            emit errorOccurred("无法创建文件");
            return false;
        }

        // 在文件开头添加难度信息
        Difficulty difficulty = evaluateDifficulty();
        std::string difficultyStr;
        switch(difficulty)
        {
            case Beginner: difficultyStr = "Beginner"; break;
            case Intermediate: difficultyStr = "Intermediate"; break;
            case Advanced: difficultyStr = "Advanced"; break;
        }

        file << "[Difficulty]\n" << difficultyStr << "\n\n";



        // 写入玩家路径
        file << "[Player]\n";
        for (const QPoint& p : m_playerPath) {
            file << p.x() << "," << p.y() << "\n";
        }

        // 写入敌人路径（包含共享终点）
        file << "[Enemy]\n";
        for (const QPoint& p : m_enemyPath) {
            file << p.x() << "," << p.y() << "\n";
        }
        file << m_playerPath.last().x() << "," << m_playerPath.last().y() << "\n";

        file.close();
        return true;
}

QVector<QPoint> Workshopgridscene::getPlayerPath() const
{
    return m_playerPath;
}

QVector<QPoint> Workshopgridscene::getEnemyPath() const
{
    QVector<QPoint> fullEnemyPath = m_enemyPath;
    if (!m_playerPath.isEmpty() && !m_enemyPath.isEmpty()) {
        fullEnemyPath.append(m_playerPath.last());
    }
    return fullEnemyPath;
}

void Workshopgridscene::updateGridDisplay()
{
    // 清除所有路径标记（保留锁定的玩家路径）
    QList<QGraphicsItem*> itemsToRemove;
    for (QGraphicsItem* item : items()) {
        if ((item->data(0) == "path_cell" || item->data(0) == "path_text") &&
            item->data(0) != "locked") {  // 不删除锁定的项目
            itemsToRemove.append(item);
        }
    }

    for (QGraphicsItem* item : itemsToRemove) {
        removeItem(item);
        delete item;
    }

    // 重新绘制玩家路径（始终显示）
    for (int i = 0; i < m_playerPath.size(); ++i) {
        // 使用不同的样式区分当前模式
        if (m_currentMode == PlayerPath) {
            drawPathCell(m_playerPath[i], i+1, QColor(135, 206, 250));
        } else {
            // 敌人模式下使用不同的颜色/样式显示玩家路径
            drawPathCell(m_playerPath[i], i+1,  QColor(173, 216, 230));
        }
    }

    // 绘制敌人路径（如果处于敌人模式）
    if (m_currentMode == EnemyPath) {
        for (int i = 0; i < m_enemyPath.size(); ++i) {
            drawPathCell(m_enemyPath[i], i+1, Qt::yellow);
        }
    }
}
void Workshopgridscene::clearPaths()
{
    m_playerPath.clear();
    m_enemyPath.clear();
    m_currentMode = PlayerPath;
    updateGridDisplay(); // 调用更新函数
}

void Workshopgridscene::undoLastStep()
{
    if (m_currentMode == PlayerPath && !m_playerPath.isEmpty())
    {
        m_playerPath.removeLast();
    }
    else if (m_currentMode == EnemyPath && !m_enemyPath.isEmpty())
    {
        m_enemyPath.removeLast();
    }
    updateGridDisplay();
}

Workshopgridscene::Difficulty Workshopgridscene::evaluateDifficulty() const
{
    // 评估标准：
    // 1. 路径长度
    // 2. 路径复杂度(拐点数)
    // 3. 敌人路径与玩家路径的相对复杂度

    if(m_playerPath.size() < 5) return Beginner;

    int playerTurns = 0;
    for(int i = 1; i < m_playerPath.size()-1; ++i) {
        QPoint prev = m_playerPath[i-1];
        QPoint curr = m_playerPath[i];
        QPoint next = m_playerPath[i+1];

        // 检查是否是拐点
        if((prev.x() == curr.x() && curr.y() != next.y()) ||
           (prev.y() == curr.y() && curr.x() != next.x())) {
            playerTurns++;
        }
    }

    int enemyTurns = 0;
    for(int i = 1; i < m_enemyPath.size()-1; ++i) {
        QPoint prev = m_enemyPath[i-1];
        QPoint curr = m_enemyPath[i];
        QPoint next = m_enemyPath[i+1];

        if((prev.x() == curr.x() && curr.y() != next.y()) ||
           (prev.y() == curr.y() && curr.x() != next.x())) {
            enemyTurns++;
        }
    }

    // 综合评估
    if(playerTurns >= 3 || enemyTurns >= 2)
        return Advanced;
    else if(playerTurns >= 1 || enemyTurns >= 1)
        return Intermediate;
    else
        return Beginner;
}

