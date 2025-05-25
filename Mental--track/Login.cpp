#include "gamedefine.h"
#include "ui_Login.h"
#include"Login.h"
#include<UserFileManager.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->setWindowTitle("登录");
    this->setFixedSize(800,800);

    ui->Label_loginbackground->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    ui->Label_loginbackground->setScaledContents(true);  // 关键：启用自动缩放

}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_play_clicked()
{
    AudioManager::instance()->playEffect();
        QString username = ui->lineEdit_User->text();
        QString password = ui->lineEdit_Pass->text();

        if(username.isEmpty() || password.isEmpty())
        {
            QMessageBox::warning(this, "警告", "用户名和密码不能为空");
            return;
        }

        User* currentUser = getValidatedUser(username, password);
        // User* currentUser = getValidatedUser("Alex", "1234");
        if(currentUser)
        {
            QMessageBox::information(this, "提示", "登录成功！");
            // 将用户对象传递给Mode窗口
            getGlobalModeWindow()->setCurrentUser(currentUser); // 需要添加此方法
            this->hide();
            getGlobalModeWindow()->show();
        }
        else
        {
            QMessageBox::critical(this, "失败", "用户名或密码错误");
            return;
        }


    this->hide();
    getGlobalModeWindow()->show();

}



void Login::on_pushButton_back_clicked()
{

    AudioManager::instance()->playEffect();
    this->hide();
    getGlobalStartWindow()->show();
}

void Login::on_pushButton_help_clicked()
{

    AudioManager::instance()->playEffect();
    Help *help = new Help(this);  // 关键：传递当前窗口指针
    help->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);  // 强制设为对话框
    help->setAttribute(Qt::WA_DeleteOnClose, true);
    this->hide();
    help->show();

}


void Login::on_checkBox_clicked(bool checked)
{
    if(!checked)
    {
        ui->lineEdit_Pass->setEchoMode(QLineEdit::Password);
    }
    else
    {
        ui->lineEdit_Pass->setEchoMode(QLineEdit::Normal);
    }
}

//用户验证函数
User* Login::getValidatedUser(const QString& username, const QString& password)
{
    std::vector<User> users;
    if(!UserFileManager::loadUsers(users, "users.dat"))
    {
        QMessageBox::critical(nullptr, "错误", "用户数据文件读取失败");
        return nullptr;
    }

    for(auto& user : users)
    {
        if(user.getUsername() == username.toStdString() &&
           user.verifyPassword(password.toStdString()))
        {
            return new User(user); // 返回堆分配的副本
        }
    }

    return nullptr;
}







