#ifndef INTERACTIVEGRIDSCENE_H
#define INTERACTIVEGRIDSCENE_H
#include"Gridscene.h"
#include <QPoint>
#include<QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QDebug>


class InteractiveGridScene : public Gridscene
{
    Q_OBJECT
public:
    explicit InteractiveGridScene(int gridSize = 10, QObject *parent = nullptr);

    void setStartEnd(const QPoint& start, const QPoint& end, const QVector<QPoint>& correctPath);

    bool  verifyUserPath();  // 修改为主动验证函数


    const QVector<QPoint>& userPath() const { return m_userPath; }
     void clearUserPath();

signals:
    void pathPointAdded(int x, int y);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    void updateLastCellWithStepNumber();
    void drawStartEndMarkers();
    bool isAdjacent(const QPoint& p1, const QPoint& p2) const;

    QPoint m_start;
    QPoint m_end;
    QVector<QPoint> m_userPath;
    QVector<QPoint> m_correctPath;
    QGraphicsRectItem* m_startItem = nullptr;
    QGraphicsRectItem* m_endItem = nullptr;
};



#endif // INTERACTIVEGRIDSCENE_H
