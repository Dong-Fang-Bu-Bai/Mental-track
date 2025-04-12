#include "Displaygridscene.h"
#include <QPainterPath>
#include <QGraphicsRectItem>

DisplayGridScene::DisplayGridScene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent)
{
    drawGrid();// 初始化时绘制网格
}

void DisplayGridScene::setPaths(
    const QVector<QPoint>& actualPath,
    const QVector<QPoint>& relativePath)
{
    clearGrid(); // 清空场景

    // 1. 找出所有重叠的格子
    QSet<QPoint> overlapCells;
    for (const QPoint& p : actualPath) {
        if (relativePath.contains(p)) {
            overlapCells.insert(p);
        }
    }

    // 2. 分析相对路径中的静止点（多步停留在同一位置）
    // 将QMap改为QHash
    QHash<QPoint, QVector<int>> stationarySteps;// <位置, 步数列表>
    for (int i = 0; i < relativePath.size(); ++i)
    {
        const QPoint& p = relativePath[i];
        stationarySteps[p].append(i + 1); // 记录步数（从1开始）
    }

    // 3. 绘制非重叠部分
    // 己方路径（蓝色）
    for (int i = 0; i < actualPath.size(); ++i) {
        const QPoint& p = actualPath[i];
        if (!overlapCells.contains(p)) {
            updateCellColor(p, Qt::blue);
            addStepNumber(p, i + 1, Qt::white, QPointF(5, 5)); // 蓝色路径步数（左上）
        }
    }

    // 对方路径（绿色）
    for (int i = 0; i < relativePath.size(); ++i) {
        const QPoint& p = relativePath[i];
        if (!overlapCells.contains(p)) {
            // 检查是否是静止点（有多步停留）
            if (stationarySteps[p].size() > 1) {
                // 绘制绿色背景
                updateCellColor(p, Qt::green);

                // 添加所有步数（自上而下排列）
                addMultipleStepNumbers(p, stationarySteps[p], Qt::black);
            } else {
                // 普通移动点
                updateCellColor(p, Qt::green);
                addStepNumber(p, i + 1, Qt::black, QPointF(CELL_SIZE - 15, 5));
            }
        }
    }

    // 4. 绘制重叠部分（灰色+双步数+对方多步静止）
       for (const QPoint& p : overlapCells) {
           // 灰色背景
           updateCellColor(p, Qt::gray);

           // 获取双方步数
           int actualStep = actualPath.indexOf(p) + 1;
           QVector<int> relativeSteps = stationarySteps[p];

           // 蓝色步数（左上）- 己方步数
           addStepNumber(p, actualStep, Qt::blue, QPointF(5, 5));

           // 绿色步数（右侧）- 对方所有步数
           if (relativeSteps.size() > 1) {
               // 对方多步静止，在右侧显示所有步数
               const int stepHeight = 15;
               const int rightMargin = 5;

               for (int i = 0; i < relativeSteps.size(); ++i) {
                   QGraphicsSimpleTextItem* textItem =
                       new QGraphicsSimpleTextItem(QString::number(relativeSteps[i]));

                   QFont font;
                   font.setPointSize(9);
                   textItem->setFont(font);
                   textItem->setBrush(QBrush(Qt::green));

                   textItem->setPos(
                       p.x() * CELL_SIZE + CELL_SIZE -
                               textItem->boundingRect().width() -
                               rightMargin,
                       p.y() * CELL_SIZE + 5 + i * stepHeight
                   );

                   addItem(textItem);
               }
           } else {
               // 单一步数，正常显示在右上
               addStepNumber(p, relativeSteps.first(), Qt::green,
                             QPointF(CELL_SIZE - 15, 5));
           }
       }
}

// 新增方法：添加多个步数标记（自上而下排列）
void DisplayGridScene::addMultipleStepNumbers(
    const QPoint& pos,
    const QVector<int>& steps,
    const QColor& textColor)
{
    const int stepHeight = 15; // 每个步数标记的高度
    const int startY = 5;     // 起始Y坐标
    const int rightMargin = 5; // 右侧边距

    for (int i = 0; i < steps.size(); ++i) {
        QGraphicsSimpleTextItem* textItem =
                new QGraphicsSimpleTextItem(QString::number(steps[i]));

        QFont font;
        font.setPointSize(12);
        textItem->setFont(font);
        textItem->setBrush(QBrush(textColor));

        // 计算位置（靠右对齐，垂直方向依次排列）
        textItem->setPos(
            pos.x() * CELL_SIZE + CELL_SIZE - textItem->boundingRect().width() - rightMargin,
            pos.y() * CELL_SIZE + startY + i * stepHeight
        );

        addItem(textItem);
    }
}



   void DisplayGridScene::addStepNumber(const QPoint& pos, int step, const QColor& textColor, const QPointF& offset)
   {
       QGraphicsSimpleTextItem* textItem = new QGraphicsSimpleTextItem(QString::number(step));

       QFont font;
       font.setPointSize(12); // 稍小一点的字体
       textItem->setFont(font);
       textItem->setBrush(QBrush(textColor));

       // 使用offset参数控制位置
       textItem->setPos(
           pos.x() * CELL_SIZE + offset.x(),
           pos.y() * CELL_SIZE + offset.y()
       );

       addItem(textItem);
   }

   void DisplayGridScene::updateCellColor(const QPoint& pos, const QColor& color)
   {
       QGraphicsRectItem* cell = new QGraphicsRectItem(
           pos.x() * CELL_SIZE,
           pos.y() * CELL_SIZE,
           CELL_SIZE, CELL_SIZE);
       cell->setBrush(color);
       addItem(cell);
   }





