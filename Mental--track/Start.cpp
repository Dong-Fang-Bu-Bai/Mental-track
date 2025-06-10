#include "gamedefine.h"
#include "ui_Start.h"
#include"Start.h"



Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    this->setWindowTitle("开始界面");
    this->setFixedSize(1024,1024);


    ui->Label_Name->setPixmap(QPixmap(":/img/Debug/image/Name.png"));
    ui->Label_Name->setScaledContents(true);  // 关键：启用自动缩放

    UserFileManager manager;
   manager.generateDeveloperReport("users.dat", "users_info.txt");


}

Start::~Start()
{
    delete ui;
}

void Start::on_Btn_login_clicked()
{
    AudioManager::instance()->playEffect();
    this->hide();
    getGlobalLoginWindow()->show();
}

void Start::on_Btn_Register_clicked()
{

    AudioManager::instance()->playEffect();
    this->hide();
    getGlobalRegisterWindow()->show();
}

void Start::on_Btn_Exit_clicked()
{

    AudioManager::instance()->playEffect();
    this->close();

}
