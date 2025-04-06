#include "Displaygridscene.h"
#include <QPainterPath>
#include <QGraphicsRectItem>

DisplayGridScene::DisplayGridScene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent)
{
    drawGrid();// 初始化时绘制网格
}

void DisplayGridScene::setPaths
(
    const QVector<QPoint>& actualPath,
    const QVector<QPoint>& relativePath)
{
    clearGrid(); // 清空场景

    // 1. 绘制己方实际路径（红色格子）
       for(const QPoint& p : actualPath) {
           updateCellColor(p, Qt::red);
       }

     //2. 绘制对方相对路径（蓝色格子）
       QPoint current(0, 0);
       for(const QPoint& delta : relativePath) {
           current += delta;
           updateCellColor(current, Qt::blue);
       }

}




void DisplayGridScene::updateCellColor(
    const QPoint& pos,
    const QColor& color)
{
    QGraphicsRectItem* cell = new QGraphicsRectItem(
        pos.x() * CELL_SIZE,   // x坐标
        pos.y() * CELL_SIZE,    // y坐标
        CELL_SIZE, CELL_SIZE);  // 宽高
    cell->setBrush(color);
    addItem(cell);
}




