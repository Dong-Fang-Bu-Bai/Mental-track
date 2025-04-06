#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>

namespace Ui {
class Gameplay;
}

class Gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit Gameplay(QWidget *parent = nullptr);
    ~Gameplay();

private:
    Ui::Gameplay *ui;
};

#endif // GAMEPLAY_H
