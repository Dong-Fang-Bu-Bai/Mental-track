#include "gamedefine.h"
#include "ui_Register.h"
#include"Register.h"
#include<User.h>
#include<UserFileManager.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    this->setWindowTitle("注册");
    this->setFixedSize(800,800);

    ui->label_RegisterBack->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    ui->label_RegisterBack->setScaledContents(true);  // 关键：启用自动缩放


}

// 替换原有的saveUserCredentials函数
bool saveUserCredentials(const QString& username, const QString& password)
{
    std::vector<User> users;
    UserFileManager::loadUsers(users, "users.dat"); // 尝试加载现有用户

    // 检查用户名是否已存在
    for(const auto& user : users)
    {
        if(user.getUsername() == username.toStdString()) {
            return false;
        }
    }

    // 添加新用户
    users.emplace_back(username.toStdString(), password.toStdString());

    return UserFileManager::saveUsers(users, "users.dat");
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

    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "警告", "用户名和密码不能为空");
        return;
    }

    if(password != confirm) {
        QMessageBox::critical(this, "错误", "两次输入的密码不一致");
        return;
    }

    if(saveUserCredentials(username, password)) {
        QMessageBox::information(this, "成功", "注册成功！");
        this->hide();
        getGlobalModeWindow()->show();
    } else {
        QMessageBox::critical(this, "错误", "用户名已存在或注册失败");
    }
}
