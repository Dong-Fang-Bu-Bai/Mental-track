#ifndef DISPLAYGRIDSCENE_H
#define DISPLAYGRIDSCENE_H
#include"Gridscene.h"
#include <QSet>  // 添加这行
#include <QPen>

// 添加QPoint的哈希函数声明
inline uint qHash(const QPoint &key, uint seed = 0) {
    return qHash(qMakePair(key.x(), key.y()), seed);
}

class DisplayGridScene : public Gridscene
{
public:
    explicit DisplayGridScene(int gridSize = 10, QObject *parent = nullptr);

    void setPaths(const QVector<QPoint>& actualPath,
                 const QVector<QPoint>& relativePath);

protected:

    void updateCellColor(const QPoint& pos, const QColor& color);

       void addStepNumber(const QPoint& pos, int step, const QColor& textColor
                          ,const QPointF& offset);

       void addMultipleStepNumbers(
               const QPoint& pos,
               const QVector<int>& steps,
               const QColor& textColor);
};

#endif // DISPLAYGRIDSCENE_H
