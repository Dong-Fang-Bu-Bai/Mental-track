#ifndef PATHCALCULATOR_H
#define PATHCALCULATOR_H

#include <QPoint>
#include <QVector>

class Pathcalculator
{
public:

    // 手动设置路径
    static bool setPaths(
        const QVector<QPoint>& actualPath,
        const QVector<QPoint>& opponentPath,
        QVector<QPoint>& relativePath,
        int gridSize);


    // 随机生成路径
    static bool generateRandomPaths(
        int gridSize,
        QVector<QPoint>& actualPath,
        QVector<QPoint>& opponentPath,
        QVector<QPoint>& relativePath);

private:
    static bool calculateRelativePath(
        const QVector<QPoint>& actualPath,
        const QVector<QPoint>& opponentPath,
        QVector<QPoint>& relativePath,
        int gridSize);

    static bool generateRandomPath(
        int gridSize,
        const QPoint& start,
        const QPoint& end,
        QVector<QPoint>& path);

    static QPoint generateRandomStartPoint(int gridSize);

     static bool validatePath(const QVector<QPoint>& path, int gridSize);
};

#endif // PATHCALCULATOR_H
