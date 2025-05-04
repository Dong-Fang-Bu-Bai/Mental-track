#include "Workshopgridscene.h"

Workshopgridscene::Workshopgridscene(int gridSize, QObject *parent)
    : Gridscene(gridSize, parent)
{
    drawGrid();
}
