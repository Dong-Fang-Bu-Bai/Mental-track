#include "gamedefine.h"
#include "ui_Register.h"
#include"Register.h"
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

bool saveUserCredentials(const QString& username, const QString& password, const QString& filePath = "users.dat")
{
    QFile file(filePath);

    // 以追加模式打开文件（不存在则创建）
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "错误", "无法打开用户数据文件");
        return false;
    }

    QTextStream out(&file);

    out << username<< "," << password << "\n";
    file.close();
    return true;
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

void Register::on_pushButton_play_clicked()
{
    if(ui->lineEdit_User->text().trimmed().isEmpty()||ui->lineEdit_Pass->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "失败", "用户名或密码为空！");
        return;
    }
    if(ui->lineEdit_Pass->text()!=ui->lineEdit_passconfirm->text())
    {
        QMessageBox::critical(this, "失败", "请重新确认密码！");
        return;
    }

    if(saveUserCredentials(ui->lineEdit_User->text(),ui->lineEdit_Pass->text()))
    {
        QMessageBox::information(this, "提示", "注册成功！");
        this->hide();
        getGlobalModeWindow()->show();
    }


}
