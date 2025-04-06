#include "Pathcalculator.h"
#include<QDebug>
#include <QtGlobal>
#include <QTime>

//核心  计算相对路径的函数
bool Pathcalculator::calculateRelativePath(
    const QVector<QPoint>& actualPath,
    const QVector<QPoint>& opponentPath,
    QVector<QPoint>& relativePath,
    int gridSize)
{
    relativePath.clear();

    // 1. 检查空路径
    if(actualPath.isEmpty() || opponentPath.isEmpty()) {
        qWarning() << "Empty path detected!";
        return false;
    }

//    // 2. 检查路径长度匹配
//    if(actualPath.size() != opponentPath.size()) {
//        qWarning() << "Path lengths don't match!";
//        return false;
//    }

    // 3. 检查终点是否相同
    if(actualPath.last() != opponentPath.last()) {
        qWarning() << "Paths don't end at same point!";
        return false;
    }

    // 4. 计算并验证相对路径
    for(int i = 0; i < actualPath.size(); ++i) {
        QPoint delta = opponentPath[i] - actualPath[i];

        // 验证相对移动不越界
        if(qAbs(delta.x()) > 1 || qAbs(delta.y()) > 1) {
            qWarning() << "Invalid relative move at step" << i
                      << ":" << delta << "(Max allowed: 1 step)";
            return false;
        }

        // 验证相对移动后的位置是否在网格内
        QPoint newPos = actualPath[i] + delta;
        if(newPos.x() < 0 || newPos.y() < 0 ||
           newPos.x() >= gridSize || newPos.y() >= gridSize) {
            qWarning() << "Relative move out of grid at step" << i
                      << ":" << newPos << "(Grid size:" << gridSize << ")";
            return false;
        }

        relativePath.append(delta);
    }

    return true;
}

//用于手动设置时
bool Pathcalculator::setPaths
(
    const QVector<QPoint>& actualPath,
    const QVector<QPoint>& opponentPath,
    QVector<QPoint>& relativePath,
    int gridSize)
{
    // 先检查非空再调用其他方法
    if(actualPath.isEmpty() || opponentPath.isEmpty())
    {
        qWarning() << "Cannot set empty paths!";
        return false;
    }
    // 验证输入路径
    if(!validatePath(actualPath, gridSize) || !validatePath(opponentPath, gridSize)) {
        qWarning() << "Invalid path detected!";
        return false;
    }

    if(actualPath.last() != opponentPath.last()) {
        qWarning() << "Paths don't have same end point!";
        return false;
    }

    return calculateRelativePath(actualPath, opponentPath, relativePath, gridSize);
}

bool Pathcalculator::generateRandomPaths(
    int gridSize,
    QVector<QPoint>& actualPath,
    QVector<QPoint>& opponentPath,
    QVector<QPoint>& relativePath)
{
    qsrand(QTime::currentTime().msec());

    // 共同的终点（右下角）
    QPoint end(gridSize-1, gridSize-1);

    // 生成不同的起点
    QPoint actualStart = generateRandomStartPoint(gridSize);
    QPoint opponentStart = generateRandomStartPoint(gridSize);
    while(opponentStart == actualStart) {
        opponentStart = generateRandomStartPoint(gridSize);
    }

    // 生成路径
    if(!generateRandomPath(gridSize, actualStart, end, actualPath) ||
       !generateRandomPath(gridSize, opponentStart, end, opponentPath))
    {
        qWarning() << "Failed to generate paths!";
        return false;
    }

    // 确保路径非空再计算相对路径
    if(actualPath.isEmpty() || opponentPath.isEmpty()) {
        return false;
    }

    return calculateRelativePath(actualPath, opponentPath, relativePath, gridSize);
}








bool Pathcalculator::generateRandomPath(
    int gridSize,
    const QPoint& start,
    const QPoint& end,
    QVector<QPoint>& path)
{
    path.clear();
    path.append(start);

    QPoint current = start;
    int maxSteps = gridSize * 3; // 防止无限循环

    while(current != end && path.size() < maxSteps) {
        // 70%概率向终点移动
        if(qrand() % 10 < 7) {
            int dx = qBound(-1, end.x() - current.x(), 1);
            int dy = qBound(-1, end.y() - current.y(), 1);

            if(dx != 0 && (qrand() % 2 || dy == 0)) {
                current.rx() += dx;
            } else if(dy != 0) {
                current.ry() += dy;
            }
        }
        // 30%概率随机移动
        else {
            switch(qrand() % 4) {
                case 0: current.rx() += 1; break;
                case 1: current.rx() -= 1; break;
                case 2: current.ry() += 1; break;
                case 3: current.ry() -= 1; break;
            }
        }

        // 边界检查
        if(current.x() < 0 || current.y() < 0 ||
           current.x() >= gridSize || current.y() >= gridSize) {
            continue;
        }

        path.append(current);
    }

    // 确保到达终点
    if(current != end) {
        path.append(end);
    }

    return validatePath(path, gridSize);
}

QPoint Pathcalculator::generateRandomStartPoint(int gridSize) {
    int side = qrand() % 4;
    int pos = qrand() % gridSize;

    switch(side) {
        case 0: return QPoint(pos, 0);          // 上边界
        case 1: return QPoint(gridSize-1, pos); // 右边界
        case 2: return QPoint(pos, gridSize-1); // 下边界
        default: return QPoint(0, pos);         // 左边界
    }
}

bool Pathcalculator::validatePath(const QVector<QPoint>& path, int gridSize) {
    if(path.isEmpty()) return false;

    // 检查所有点是否在网格内
    for(const QPoint& p : path) {
        if(p.x() < 0 || p.y() < 0 || p.x() >= gridSize || p.y() >= gridSize) {
            return false;
        }
    }

    // 检查是否连续移动
    for(int i = 1; i < path.size(); ++i) {
        int dx = qAbs(path[i].x() - path[i-1].x());
        int dy = qAbs(path[i].y() - path[i-1].y());
        if(dx + dy != 1) {
            return false;
        }
    }

    return true;
}
