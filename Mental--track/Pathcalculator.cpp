#include "Pathcalculator.h"
#include<QDebug>
#include <QtGlobal>
#include <QTime>

//计算相对路径的函数
bool Pathcalculator::calculateRelativePath(
    const QVector<QPoint>& actualPath,
    const QVector<QPoint>& opponentPath,
    QVector<QPoint>& relativePath,
    int gridSize)
{
    relativePath.clear();

    if(actualPath.isEmpty() || opponentPath.isEmpty())
    {
        qWarning() << "空路径！";
        return false;
    }

    // 添加初始位置（第0步）
    relativePath.append(opponentPath[0]);


    // 获取双方路径的最大长度
        int maxSteps = qMax(actualPath.size(), opponentPath.size());

        // 计算每一步的相对移动
        for(int i = 1; i < maxSteps; ++i)
        {
            // 计算对方移动方向（如果对方已到达终点则保持不动）
            QPoint opponentMove = (i < opponentPath.size()) ?
                                (opponentPath[i] - opponentPath[i-1]) : QPoint(0, 0);

            // 计算己方移动方向（如果己方已到达终点则保持不动）
            QPoint actualMove = (i < actualPath.size()) ?
                              (actualPath[i] - actualPath[i-1]) : QPoint(0, 0);

            // 计算新的相对位置 = 上一步相对位置 + (对方移动 - 己方移动)
            QPoint newPos = relativePath.last() + (opponentMove - actualMove);

            // 验证新位置是否在网格内
            if(newPos.x() < 0 || newPos.y() < 0 ||
               newPos.x() >= gridSize || newPos.y() >= gridSize)
            {
                qWarning() << "相对位置超出网格范围 at step" << i;
                return false;
            }

            relativePath.append(newPos);
        }

        return true;
}


//手动导入路径并检验
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
    if(!validatePath(actualPath, gridSize) || !validatePath(opponentPath, gridSize))
    {
        qWarning() << "Invalid path detected!";
        return false;
    }

    if(actualPath.last() != opponentPath.last())
    {
        qWarning() << "Paths don't have same end point!";
        return false;
    }

    return calculateRelativePath(actualPath, opponentPath, relativePath, gridSize);
}



bool Pathcalculator::validatePath(const QVector<QPoint>& path, int gridSize)
{
    if(path.isEmpty()) return false;

    // 检查所有点是否在网格内
    for(const QPoint& p : path)
    {
        if(p.x() < 0 || p.y() < 0 || p.x() >= gridSize || p.y() >= gridSize)
        {
            return false;
        }
    }

    // 检查是否连续移动
    for(int i = 1; i < path.size(); ++i)
    {
        int dx = qAbs(path[i].x() - path[i-1].x());
        int dy = qAbs(path[i].y() - path[i-1].y());
        if(dx + dy != 1)
        {
            return false;
        }
    }

    return true;
}
