#include "gamedefine.h"
#include "ui_Help.h"
#include"Help.h"
#include <QFile>
#include <QTextStream>

Help::Help(QWidget *parent) :
     QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowTitle("帮助");
    this->setFixedSize(1200,1200);

    ui->label_Background->setPixmap(QPixmap(":/img/Debug/image/Modebackground.fw.png"));
    ui->label_Background->setScaledContents(true);  // 关键：启用自动缩放

    QFile file("Help.txt");

    if (file.open(QIODevice::ReadOnly)) {
        ui->textEdit_Help->setText(file.readAll()); // 若文件含HTML标签会被解析
        file.close();
    }
    //ui->textEdit_Help->setStyleSheet("background-color:rgba(111, 159, 225 , 200);");
    ui->textEdit_Help->setStyleSheet("background-color:rgba(255, 255, 255 , 0%);");
    ui->textEdit_Help->setReadOnly(true);
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_Backstart_clicked()
{
    this->parentWidget()->show();  // 显示来源窗口
    this->close();                 // 关闭帮助窗口
}
