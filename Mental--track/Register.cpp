#include "gamedefine.h"
#include "ui_Register.h"
#include"Register.h"
#include<User.h>
#include<UserFileManager.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    this->setWindowTitle("注册");
    this->setFixedSize(800,800);

    ui->label_RegisterBack->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    ui->label_RegisterBack->setScaledContents(true);  // 关键：启用自动缩放

    // 设置密码框回显模式
    ui->lineEdit_Pass->setEchoMode(QLineEdit::Password);
    ui->lineEdit_passconfirm->setEchoMode(QLineEdit::Password);

}


Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_back_clicked()
{
    this->hide();
    getGlobalStartWindow()->show();
}

void Register::on_pushButton_help_clicked()
{
    Help *help = new Help(this);  // 关键：传递当前窗口指针
    help->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);  // 强制设为对话框
    help->setAttribute(Qt::WA_DeleteOnClose, true);
    this->hide();
    help->show();

}

// 修改on_pushButton_play_clicked函数
void Register::on_pushButton_play_clicked()
{
    QString username = ui->lineEdit_User->text().trimmed();
    QString password = ui->lineEdit_Pass->text().trimmed();
    QString confirm = ui->lineEdit_passconfirm->text().trimmed();

    if(!validateInput(username, password, confirm))
    {
           return;
    }

    User* newUser = registerNewUser(username, password);
        if(newUser)
        {
            QMessageBox::information(this, "成功", "注册成功！");

            // 获取Mode窗口并设置当前用户
            Mode* modeWindow = getGlobalModeWindow();
            modeWindow->setCurrentUser(newUser); // 需要确保Mode类有这个方法

            this->hide();
            modeWindow->show();
        } else
        {
            QMessageBox::critical(this, "错误", "用户名已存在或注册失败");
        }

//    if(username.isEmpty() || password.isEmpty()) {
//        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
//        return;
//    }

//    if(password != confirm) {
//        QMessageBox::critical(this, "错误", "两次输入的密码不一致");
//        return;
//    }

//    if(saveUserCredentials(username, password)) {
//        QMessageBox::information(this, "成功", "注册成功！");
//        this->hide();
//        getGlobalModeWindow()->show();
//    } else {
//        QMessageBox::critical(this, "错误", "用户名已存在或注册失败");
//    }


}

bool Register::validateInput(const QString& username, const QString& password, const QString& confirm) {
    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return false;
    }

    if(password != confirm) {
        QMessageBox::critical(this, "错误", "两次输入的密码不一致");
        return false;
    }

    // 可以添加更多验证规则，如密码强度等
    return true;
}

User* Register::registerNewUser(const QString& username, const QString& password) {
    std::vector<User> users;
    if(!UserFileManager::loadUsers(users, "users.dat")) {
        // 文件不存在时创建新文件
        users.clear();
    }

    // 检查用户名是否已存在
    for(const auto& user : users)
    {
        if(user.getUsername() == username.toStdString()) {
            return nullptr;
        }
    }

    // 创建新用户
    User* newUser = User::createNewUser(username.toStdString(), password.toStdString());
    users.push_back(*newUser);

    // 保存所有用户
    if(UserFileManager::saveUsers(users, "users.dat")) {
        return newUser;
    }

    delete newUser;
    return nullptr;
}
