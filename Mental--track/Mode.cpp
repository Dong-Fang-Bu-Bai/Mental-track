#include "Mode.h"
#include "ui_Mode.h"
#include"Map.h"
#include"Workshop.h"
#include"BattlePlay.h"
#include"gamedefine.h"
#include<QVBoxLayout>
#include<QFormLayout>
#include<QSpinBox>
#include<QDialogButtonBox>
#include"PVPPlay.h"


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

void Mode::on_pushButton_OnlineBattle_clicked()
{
    AudioManager::instance()->playEffect();
        this->hide();

        // 创建PVP模式选择对话框
        QDialog dialog(this);
        dialog.setWindowTitle("谁与争锋");
        dialog.setFixedSize(400, 300);

        QVBoxLayout layout(&dialog);

        QLabel title("选择对战方式", &dialog);
        title.setAlignment(Qt::AlignCenter);
        title.setStyleSheet("font-size: 20px; font-weight: bold;");
        layout.addWidget(&title);

        QPushButton createRoomBtn("创建房间", &dialog);
        QPushButton joinRoomBtn("加入房间", &dialog);

        // 设置按钮样式
        QString buttonStyle = "QPushButton { padding: 10px; font-size: 16px; }";
        createRoomBtn.setStyleSheet(buttonStyle);
        joinRoomBtn.setStyleSheet(buttonStyle);

        layout.addWidget(&createRoomBtn);
        layout.addWidget(&joinRoomBtn);

        connect(&createRoomBtn, &QPushButton::clicked, [&]() {
            // 获取房间设置
            QDialog settingsDialog(&dialog);
            settingsDialog.setWindowTitle("房间设置");
            QFormLayout form(&settingsDialog);

            QLineEdit passwordEdit;
            passwordEdit.setEchoMode(QLineEdit::Password);
            QSpinBox timeoutSpinBox;
            timeoutSpinBox.setRange(3, 9);
            timeoutSpinBox.setValue(6);

            form.addRow("房间密码:", &passwordEdit);
            form.addRow("回合时间(秒):", &timeoutSpinBox);

            QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            form.addRow(&buttons);

            connect(&buttons, &QDialogButtonBox::accepted, &settingsDialog, &QDialog::accept);
            connect(&buttons, &QDialogButtonBox::rejected, &settingsDialog, &QDialog::reject);

            if(settingsDialog.exec() == QDialog::Accepted) {
                PVPPlay* pvpPlay = new PVPPlay(*m_currentUser);
                pvpPlay->setAttribute(Qt::WA_DeleteOnClose, true);
                pvpPlay->startAsHost(passwordEdit.text(), timeoutSpinBox.value());
                pvpPlay->show();
                connect(pvpPlay, &PVPPlay::returnToLobby, this,[](){getGlobalModeWindow()->show();});
                dialog.accept();
            }
        });

        connect(&joinRoomBtn, &QPushButton::clicked, [&]() {
            QDialog joinDialog(&dialog);
            joinDialog.setWindowTitle("加入房间");
            QFormLayout form(&joinDialog);

            QLineEdit ipEdit("127.0.0.1");
            QLineEdit passwordEdit;
            passwordEdit.setEchoMode(QLineEdit::Password);

            form.addRow("主机IP:", &ipEdit);
            form.addRow("房间密码:", &passwordEdit);

            QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
            form.addRow(&buttons);

            connect(&buttons, &QDialogButtonBox::accepted, &joinDialog, &QDialog::accept);
            connect(&buttons, &QDialogButtonBox::rejected, &joinDialog, &QDialog::reject);

            if(joinDialog.exec() == QDialog::Accepted)
            {
                PVPPlay* pvpPlay = new PVPPlay(*m_currentUser);
                pvpPlay->setAttribute(Qt::WA_DeleteOnClose, true);
                pvpPlay->connectAsClient(ipEdit.text(), 12345, passwordEdit.text());
                pvpPlay->show();
                connect(pvpPlay, &PVPPlay::returnToLobby, this,[](){getGlobalModeWindow()->show();});
                dialog.accept();
            }
        });

        dialog.exec();


}


void Mode::on_pushButton_Exit_clicked()
{
    AudioManager::instance()->playEffect();

    exit(0);
}

