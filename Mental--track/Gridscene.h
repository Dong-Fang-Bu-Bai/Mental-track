#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QVector>


class Gridscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Gridscene(int gridSize = 10, QObject *parent = nullptr);

     // 公共方法
    void drawGrid();
    void clearGrid();


protected:
    int m_gridSize;      // 网格尺寸（10/15/20）

    const int CELL_SIZE = 68;// 统一常量命名



};

#endif // GRIDSCENE_H
