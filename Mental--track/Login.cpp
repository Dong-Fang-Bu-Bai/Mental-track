#include "gamedefine.h"
#include "ui_Login.h"
#include"Login.h"

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

}



void Login::on_pushButton_back_clicked()
{
    Start *w=new Start();

    w->show();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    this->hide();
}

void Login::on_pushButton_help_clicked()
{
    Help *w=new Help();

    w->show();
    w->setAttribute(Qt::WA_DeleteOnClose, true);
    this->hide();
}
