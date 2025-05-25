#ifndef AISTRATEGIES_H
#define AISTRATEGIES_H


#include <QPoint>
#include <QVector>
#include <memory>

class IAIStrategy
{
public:
    virtual ~IAIStrategy() = default;
    virtual QPoint calculateMove(const QPoint& currentPos,
                               const QVector<QPoint>& possibleMoves,
                               const QVector<QPoint>& playerPath,
                               const QVector<QPoint>& aiPath) = 0;
};

class RandomStrategy : public IAIStrategy
{
public:
    QPoint calculateMove(const QPoint& currentPos,
                       const QVector<QPoint>& possibleMoves,
                       const QVector<QPoint>& playerPath,
                       const QVector<QPoint>& aiPath) override;
};

class IntermediateStrategy : public IAIStrategy
{
public:
    QPoint calculateMove(const QPoint& currentPos,
                       const QVector<QPoint>& possibleMoves,
                       const QVector<QPoint>& playerPath,
                       const QVector<QPoint>& aiPath) override;
};

class AdvancedStrategy : public IAIStrategy
{
public:
    QPoint calculateMove(const QPoint& currentPos,
                       const QVector<QPoint>& possibleMoves,
                       const QVector<QPoint>& playerPath,
                       const QVector<QPoint>& aiPath) override;
private:
    int evaluatePosition(const QPoint& pos) const;
    QVector<QPoint> predictPlayerMoves(const QPoint& playerPos, int depth) const;
};
#endif // AISTRATEGIES_H
