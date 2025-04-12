#include "Interactivegridscene.h"


InteractiveGridScene::InteractiveGridScene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent)
{
    drawGrid();
}

void InteractiveGridScene::setStartEnd(const QPoint& start, const QPoint& end, const QVector<QPoint>& correctPath)
{
    clearGrid();
    m_userPath.clear();

    m_start = start;
    m_end = end;
    m_correctPath = correctPath;

    drawStartEndMarkers();
}

void InteractiveGridScene::drawStartEndMarkers()
{
    // 起点标记（黄色，带锁图标表示不可更改）
    m_startItem = new QGraphicsRectItem(
        m_start.x() * CELL_SIZE, m_start.y() * CELL_SIZE,
        CELL_SIZE, CELL_SIZE);
    m_startItem->setBrush(Qt::yellow);
    m_startItem->setData(0, "locked"); // 标记为锁定状态
    addItem(m_startItem);

    auto startText = new QGraphicsSimpleTextItem("1", m_startItem);
    QFont font = startText->font();
    font.setPointSize(18); // 设置更大的字号
    startText->setFont(font);
    // 动态计算居中位置
    QRectF textRect = startText->boundingRect();
    startText->setPos(
        m_start.x() * CELL_SIZE + (CELL_SIZE - textRect.width()) / 2,
        m_start.y() * CELL_SIZE + (CELL_SIZE - textRect.height()) / 2
    );

    // 终点标记（黄色，带锁图标）
    m_endItem = new QGraphicsRectItem(
        m_end.x() * CELL_SIZE, m_end.y() * CELL_SIZE,
        CELL_SIZE, CELL_SIZE);
    m_endItem->setBrush(Qt::yellow);
    m_endItem->setData(0, "locked");
    addItem(m_endItem);

    auto endText = new QGraphicsSimpleTextItem(QString::number(m_correctPath.size()), m_endItem);
    endText->setFont(font); // 使用相同字体设置
    textRect = endText->boundingRect();
    endText->setPos(
        m_end.x() * CELL_SIZE + (CELL_SIZE - textRect.width()) / 2,
        m_end.y() * CELL_SIZE + (CELL_SIZE - textRect.height()) / 2
    );

}

bool InteractiveGridScene::isAdjacent(const QPoint& p1, const QPoint& p2) const
{
    return (qAbs(p1.x() - p2.x()) + qAbs(p1.y() - p2.y())) == 1;
}

void InteractiveGridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // 如果已经达到或超过最大步数，不再响应
       if(m_userPath.size() >= m_correctPath.size()-1) {
           return;
       }

    QPoint currentPos(
        static_cast<int>(event->scenePos().x()) / CELL_SIZE,
        static_cast<int>(event->scenePos().y()) / CELL_SIZE
    );

    // 边界检查
    if(currentPos.x() < 0 || currentPos.y() < 0 ||
       currentPos.x() >= m_gridSize || currentPos.y() >= m_gridSize) {
        return;
    }

    // 禁止点击起点和终点
    if(currentPos == m_start || currentPos == m_end) {
        qDebug() << "起点和终点不可更改";
        return;
    }

    // 第一次点击必须从起点相邻位置开始
    if(m_userPath.isEmpty()) {
        if(!isAdjacent(currentPos, m_start)) {
            qDebug() << "第一次点击必须从起点相邻位置开始";
            return;
        }
        m_userPath.append(m_start); // 自动添加起点
    }

    // 后续点击必须与上一位置相邻
    if(!m_userPath.isEmpty() && !isAdjacent(currentPos, m_userPath.last())) {
        qDebug() << "每次只能移动到相邻格子";
        return;
    }

    // 添加到路径（如果当前位置不在路径中）
        if(m_userPath.isEmpty() || currentPos != m_userPath.last())
        {
            m_userPath.append(currentPos);
            updateLastCellWithStepNumber(); // 修改为带步数的更新方法
            emit pathPointAdded(currentPos.x(), currentPos.y());
        }
}

bool  InteractiveGridScene::verifyUserPath()
{
    if(m_userPath.isEmpty())
    {
        return false;
    }

    // 自动补全终点
    if (m_userPath.last() != m_end) {
        m_userPath.append(m_end);

    }

    // 验证路径
    if(m_userPath.size() != m_correctPath.size()) {

        return false;
    }

    for(int i = 0; i < m_userPath.size(); ++i) {
        if(m_userPath[i] != m_correctPath[i]) {
            return false;
        }
    }
    return true;
}

void InteractiveGridScene::updateLastCellWithStepNumber()
{
    if(m_userPath.isEmpty()) return;

        QPoint p = m_userPath.last();
        // 跳过起点和终点的重新绘制
        if(p == m_start || p == m_end) return;

        // 创建黄色格子
        auto cell = new QGraphicsRectItem(
            p.x() * CELL_SIZE, p.y() * CELL_SIZE,
            CELL_SIZE, CELL_SIZE);
        cell->setBrush(Qt::yellow);
        addItem(cell);

        // 添加步数文本
        int stepNumber = m_userPath.size(); // 当前步数
        auto stepText = new QGraphicsSimpleTextItem(QString::number(stepNumber), cell);

        QFont font = stepText->font();
        font.setPointSize(18); // 与起点终点相同字号
        stepText->setFont(font);

        // 计算居中位置（修正：考虑当前格子的坐标）
        QRectF textRect = stepText->boundingRect();
        stepText->setPos(
            p.x() * CELL_SIZE + (CELL_SIZE - textRect.width()) / 2,  // 添加x坐标偏移
            p.y() * CELL_SIZE + (CELL_SIZE - textRect.height()) / 2 // 添加y坐标偏移
        );
}

void InteractiveGridScene::clearUserPath()
{
    // 保留起点和终点
    QList<QGraphicsItem*> items = this->items();
    for(QGraphicsItem* item : items) {
        if(item->data(0) != "locked") {  // 只删除未锁定的项目
            removeItem(item);
            delete item;
        }
    }

    m_userPath.clear();
    drawGrid();
    drawStartEndMarkers(); // 重新绘制起点终点
}
