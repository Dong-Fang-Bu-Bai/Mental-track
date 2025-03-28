#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_play_clicked();

    void on_pushButton_play_2_clicked();

    void on_pushButton_play_3_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_help_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
