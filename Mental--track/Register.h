#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "User.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_help_clicked();

    void on_pushButton_play_clicked();

private:
    Ui::Register *ui;

    // 新增私有方法
    User* registerNewUser(const QString& username, const QString& password);
    bool validateInput(const QString& username, const QString& password, const QString& confirm);
};

#endif // REGISTER_H
