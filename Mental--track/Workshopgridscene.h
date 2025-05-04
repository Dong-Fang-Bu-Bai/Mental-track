#ifndef WORKSHOPGRIDSCENE_H
#define WORKSHOPGRIDSCENE_H
#include"Gridscene.h"
#include <QPoint>
#include<QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

class Workshopgridscene: public Gridscene
{
     Q_OBJECT

public:
    explicit Workshopgridscene(int gridSize = 10, QObject *parent = nullptr);



};

#endif // WORKSHOPGRIDSCENE_H
