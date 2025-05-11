#ifndef WORKSHOPGRIDSCENE_H
#define WORKSHOPGRIDSCENE_H
#include"Gridscene.h"
#include <QPoint>
#include<QGraphicsSceneMouseEvent>
#include <QVector>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

class Workshopgridscene: public Gridscene
{
     Q_OBJECT

public:
    explicit Workshopgridscene(int gridSize = 10, QObject *parent = nullptr);
    enum EditMode { PlayerPath, EnemyPath };


        void setEditMode(EditMode mode);
        void clearPaths();
        bool verifyPaths();
        bool saveToFile(const std::string& fileName, const  std::string&  userName);

        QVector<QPoint> getPlayerPath() const;
        QVector<QPoint> getEnemyPath() const;

    void updateGridDisplay(); // 新增网格更新函数
    void undoLastStep(); // 添加这个方法

    enum Difficulty { Beginner, Intermediate, Advanced };
    Difficulty evaluateDifficulty() const;

    signals:
        //void pathCompleted();
        void errorOccurred(const QString& message);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    EditMode m_currentMode;
    QVector<QPoint> m_playerPath;
    QVector<QPoint> m_enemyPath;

   void drawPathCell(const QPoint& pos, int step, const QColor& color);
    bool isAdjacent(const QPoint& p1, const QPoint& p2) const;



};

#endif // WORKSHOPGRIDSCENE_H
