#include "Mode.h"
#include "ui_Mode.h"
#include"Map.h"
#include"Workshop.h"
#include"BattlePlay.h"
#include"gamedefine.h"


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

void Mode::setCurrentUser(User* user)
{
    if(m_currentUser)
    {
           delete m_currentUser; // 释放之前的用户
    }

    m_currentUser = user;
}

void Mode::on_pushButton_Mainplay_clicked()
{
    AudioManager::instance()->playEffect();

    this->hide();
    Map* map = new Map(*m_currentUser);
    map->setAttribute(Qt::WA_DeleteOnClose, true);
    map->show();

}

void Mode::on_pushButton_CreateWork_clicked()
{
    AudioManager::instance()->playEffect();

    this->hide();
    Workshop *workshop = new Workshop(*m_currentUser);
    workshop->setAttribute(Qt::WA_DeleteOnClose, true);
    workshop->show();


}

void Mode::on_pushButton_Battle_clicked()
{
    AudioManager::instance()->playEffect();

    this->hide();
    BattlePlay* battlePlay = new BattlePlay(*m_currentUser); // 解引用传递
    battlePlay->setAttribute(Qt::WA_DeleteOnClose, true);
    battlePlay->show();
}

void Mode::on_pushButton_Exit_clicked()
{
    AudioManager::instance()->playEffect();

    exit(0);
}
