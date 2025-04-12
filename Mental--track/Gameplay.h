#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QVector>
#include <QPoint>

namespace Ui {
class Gameplay;
}

class Gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit Gameplay(const QString& levelPath = ":/leveldata/Debug/levels/level1/level1.txt",
                     QWidget *parent = nullptr);
    ~Gameplay();

private:
    Ui::Gameplay *ui;
    QString m_levelPath; // 存储关卡路径


    bool loadLevel(const QString& filePath ,
                            QVector<QPoint>& playerPath,
                            QVector<QPoint>& enemyPath) ;
};

#endif // GAMEPLAY_H
