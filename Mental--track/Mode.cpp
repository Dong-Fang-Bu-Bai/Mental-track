#include "gamedefine.h"
#include "Mode.h"
#include "ui_Mode.h"

Mode::Mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mode)
{
    ui->setupUi(this);
    this->setWindowTitle("主菜单");
    this->setFixedSize(1200,1200);


    ui->label_Background->setGeometry(0,0,1200,1200);
    ui->label_Background->setPixmap(QPixmap(":/img/Debug/image/Modebackground.fw.png"));
    ui->label_Background->setScaledContents(true);
}

Mode::~Mode()
{
    delete ui;
}

void Mode::on_pushButton_Mainplay_clicked()
{
    this->hide();
    getGlobalMapWindow()->show();
}

void Mode::on_pushButton_CreateWork_clicked()
{

}

void Mode::on_pushButton_Battle_clicked()
{

}
