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
}

Start::~Start()
{
    delete ui;
}

void Start::on_Btn_login_clicked()
{
//    // 检查是否已存在实例
//    static Login *w = nullptr;
//    if (!w) {
//        w = new Login(); // 关键点
//        w->setAttribute(Qt::WA_DeleteOnClose, true);
//    }
//    w->show();
//    this->close();

//    Login *w=new Login();

//    w->show();
//    w->setAttribute(Qt::WA_DeleteOnClose, true);
//    this->hide();

    this->hide();
    getGlobalLoginWindow()->show();
}

void Start::on_Btn_Register_clicked()
{
//     //检查是否已存在实例
//    static Register *w = nullptr;
//    if (!w) {
//        w = new Register(); // 关键点
//        w->setAttribute(Qt::WA_DeleteOnClose, true);
//    }
//    w->show();
//    this->close();

//    Register *w=new Register();

//    w->show();
//    w->setAttribute(Qt::WA_DeleteOnClose, true);
//    this->hide();

    this->hide();
    getGlobalRegisterWindow()->show();
}

void Start::on_Btn_Exit_clicked()
{

    this->close();

}
