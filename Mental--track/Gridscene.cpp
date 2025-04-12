#include "Gridscene.h"
#include <QGraphicsRectItem>

Gridscene::Gridscene(int gridSize, QObject *parent)
    : QGraphicsScene(parent), m_gridSize(gridSize) {}

void Gridscene::drawGrid()
{
     QColor customColor(93, 155, 213,220);
    for (int y = 0; y < m_gridSize; ++y)
    {
        for (int x = 0; x < m_gridSize; ++x)
        {
            QGraphicsRectItem *cell = new QGraphicsRectItem
             (x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
            cell->setBrush(customColor);
            addItem(cell);
        }
    }
}

void Gridscene::clearGrid()
{
    clear();
    drawGrid();
}







