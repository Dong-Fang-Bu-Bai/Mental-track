#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<User.h>

namespace Ui
{
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



    void on_pushButton_back_clicked();

    void on_pushButton_help_clicked();



    void on_checkBox_clicked(bool checked);

private:
    Ui::Login *ui;
    User* getValidatedUser(const QString& username, const QString& password);
};

#endif // LOGIN_H
