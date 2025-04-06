#include "Interactivegridscene.h"
#include<QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

InteractiveGridScene::InteractiveGridScene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent)
{
     drawGrid();
}


void InteractiveGridScene::setStartEnd(const QPoint& start, const QPoint& end)
{
    clearGrid();
    m_playerPath.clear();

    // 标记起点（绿色）
     addRect(
         start.x() * CELL_SIZE, start.y() * CELL_SIZE,
         CELL_SIZE, CELL_SIZE,
         Qt::NoPen, Qt::green
     );

     // 标记终点（红色）
     addRect(
         end.x() * CELL_SIZE, end.y() * CELL_SIZE,
         CELL_SIZE, CELL_SIZE,
         Qt::NoPen, Qt::red
     );
}


void InteractiveGridScene::mousePressEvent
(QGraphicsSceneMouseEvent* event)
{
    // 将点击位置转换为网格坐标
    int x = static_cast<int>(event->scenePos().x()) / CELL_SIZE;
    int y = static_cast<int>(event->scenePos().y()) / CELL_SIZE;

    if(x >= 0 && y >= 0 && x < m_gridSize && y < m_gridSize) {
        // 检查是否与上一格相邻（曼哈顿距离为1）
        if(!m_playerPath.isEmpty())
        {
            QPoint last = m_playerPath.last();
            if(qAbs(x - last.x()) + qAbs(y - last.y()) != 1)
            {
                return; // 不是相邻格子，忽略点击
            }
        }

         // 记录路径并更新显示

        m_playerPath.append(QPoint(x, y));
        updateLastCellColor();
        emit pathPointAdded(x, y);
    }
}


void InteractiveGridScene::updateLastCellColor()
{
    if(m_playerPath.isEmpty())
    {
        return;
    }

    // 获取最后点击的格子位置
    QPoint p = m_playerPath.last();

    // 创建黄色格子表示路径
    QGraphicsRectItem* cell = new QGraphicsRectItem
      (p.x() * CELL_SIZE,
       p.y() * CELL_SIZE,
       CELL_SIZE, CELL_SIZE);

    cell->setBrush(Qt::yellow); // 玩家路径用黄色表示

    addItem(cell);
}

void InteractiveGridScene::clearPlayerPath()
{
    m_playerPath.clear();  // 清空路径记录
    clearGrid();            // 清空场景
    drawGrid();           // 重新绘制网格
}
