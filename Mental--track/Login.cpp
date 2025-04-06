#include "gamedefine.h"
#include "ui_Login.h"
#include"Login.h"
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

bool validateUserCredentials(const QString& username, const QString& password, const QString& filePath = "users.dat")
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "错误", "用户数据文件不存在");
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");

        if (parts.size() == 2 && parts[0] == username && parts[1] == password)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}



void Login::on_pushButton_play_clicked()
{
//    if(validateUserCredentials(ui->lineEdit_User->text(),ui->lineEdit_Pass->text()))
//    {
//        QMessageBox::information(this, "提示", "登录成功！");
//        this->hide();
//        getGlobalModeWindow()->show();
//    }
//    else
//    {
//        QMessageBox::critical(this, "失败", "用户名或密码错误");
//    }

            QMessageBox::information(this, "提示", "登录成功！");
            this->hide();
            getGlobalModeWindow()->show();

}



void Login::on_pushButton_back_clicked()
{
//    Start *w=new Start();

//    w->show();
//    w->setAttribute(Qt::WA_DeleteOnClose, true);
//    this->hide();

//    //检查是否已存在实例
//   static Start *w = nullptr;
//   if (!w) {
//       w = new Start(); // 关键点
//       w->setAttribute(Qt::WA_DeleteOnClose, true);
//   }
//   w->show();
//   this->close();

    this->hide();
    getGlobalStartWindow()->show();
}

void Login::on_pushButton_help_clicked()
{
//    Help *w=new Help();

//    w->show();
//    w->setAttribute(Qt::WA_DeleteOnClose, true);
//    this->hide();

//    //检查是否已存在实例
//   static Help *w = nullptr;
//   if (!w) {
//       w = new Help(); // 关键点
//       w->setAttribute(Qt::WA_DeleteOnClose, true);
//   }
//   w->show();
//   this->close();

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







