#ifndef MODE_H
#define MODE_H

#include <QWidget>

namespace Ui {
class Mode;
}

class Mode : public QWidget
{
    Q_OBJECT

public:
    explicit Mode(QWidget *parent = nullptr);
    ~Mode();

private slots:
    void on_pushButton_Mainplay_clicked();

    void on_pushButton_CreateWork_clicked();

    void on_pushButton_Battle_clicked();

private:
    Ui::Mode *ui;
};

#endif // MODE_H
