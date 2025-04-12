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




private:
    static bool calculateRelativePath(
        const QVector<QPoint>& actualPath,
        const QVector<QPoint>& opponentPath,
        QVector<QPoint>& relativePath,
        int gridSize);


     static bool validatePath(const QVector<QPoint>& path, int gridSize);
};

#endif // PATHCALCULATOR_H
