#ifndef MODE_H
#define MODE_H

#include <QWidget>
#include"User.h"


// 前向声明
//class Workshop;

//class PVPPlay;

namespace Ui
{
class Mode;
}

class Mode : public QWidget
{
    Q_OBJECT

public:
    void setCurrentUser(User* user);
    explicit Mode(QWidget *parent = nullptr);
    ~Mode();

private slots:
    void on_pushButton_Mainplay_clicked();

    void on_pushButton_CreateWork_clicked();

    void on_pushButton_Battle_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_OnlineBattle_clicked();

private:
    Ui::Mode *ui;
    User* m_currentUser = nullptr;
};

#endif // MODE_H
