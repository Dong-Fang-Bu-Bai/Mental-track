#include "gamedefine.h"
#include "Setting.h"
#include "ui_Setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_Back_clicked()
{
    this->parentWidget()->show();  // 显示来源窗口
    this->close();                 // 关闭帮助窗口
}
