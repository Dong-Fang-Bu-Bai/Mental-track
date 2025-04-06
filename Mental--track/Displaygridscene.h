#ifndef DISPLAYGRIDSCENE_H
#define DISPLAYGRIDSCENE_H
#include"Gridscene.h"
#include <QPen>

class DisplayGridScene : public Gridscene
{
public:
    explicit DisplayGridScene(int gridSize = 10, QObject *parent = nullptr);

    void setPaths(const QVector<QPoint>& actualPath,
                 const QVector<QPoint>& relativePath);

protected:

    void updateCellColor(const QPoint& pos, const QColor& color);
};

#endif // DISPLAYGRIDSCENE_H
