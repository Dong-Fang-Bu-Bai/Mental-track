#ifndef INTERACTIVEGRIDSCENE_H
#define INTERACTIVEGRIDSCENE_H
#include"Gridscene.h"



class InteractiveGridScene : public Gridscene
{
    Q_OBJECT
public:
    explicit InteractiveGridScene(int gridSize = 10, QObject *parent = nullptr);
    void setStartEnd(const QPoint& start, const QPoint& end);

    const QVector<QPoint>& playerPath() const { return m_playerPath; }

    void clearPlayerPath();

signals:
     void pathPointAdded(int,int); // 发送信号
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override ;

private:
    QVector<QPoint> m_playerPath;
    void updateLastCellColor();
};



#endif // INTERACTIVEGRIDSCENE_H
