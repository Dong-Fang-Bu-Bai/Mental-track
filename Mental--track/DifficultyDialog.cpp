#include "DifficultyDialog.h"
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include "BattleGridScene.h"
#include <QLabel>
#include "BattlePlay.h"

DifficultyDialog::DifficultyDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowModality(Qt::ApplicationModal); // 设置为应用程序模态
    setupUI();
}

void DifficultyDialog::setupUI()
{
    // 设置无边框和透明背景
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); // 添加Qt::Dialog标志
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedSize(450, 450); // 设置对话框大小

    // 设置对话框样式 - 模拟边框效果
    setStyleSheet(
        "QDialog {"
        "    background-color: rgba(238, 84, 51, 180);"  // 外边框颜色
        "    border-radius: 25px;"
        "}"
    );

    // 创建内容区域背景
    QWidget* contentWidget = new QWidget(this);
    contentWidget->setGeometry(15, 15, 420, 420); // 留出15像素作为边框
    contentWidget->setStyleSheet(
        "background-color: rgba(35, 232, 212  ,210);"  // 内容背景
        "border-radius: 40px;"
    );

    // 添加标题
    QLabel *titleLabel = new QLabel("难度选择", contentWidget);
    titleLabel->setGeometry(0, 30, 420, 50); // 设置位置和大小
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet
    (
        //"color: rgba(232, 148, 35 );"
        "color: black;"
        "font-size: 45px;"
        "font-weight: bold;"
        "background: transparent;"
        "font-family: 华文行楷;"
        "font-weight: bold;"
    );

    // 创建三个难度按钮
    QPushButton* easyBtn = createDifficultyButton("初级难度", Easy);
    easyBtn->setParent(contentWidget);
    easyBtn->move(60, 120); // 设置按钮位置

    QPushButton* mediumBtn = createDifficultyButton("中级难度", Medium);
    mediumBtn->setParent(contentWidget);
    mediumBtn->move(60, 220); // 设置按钮位置

    QPushButton* hardBtn = createDifficultyButton("高级难度", Hard);
    hardBtn->setParent(contentWidget);
    hardBtn->move(60, 320); // 设置按钮位置

    setAttribute(Qt::WA_DeleteOnClose);
}

QPushButton* DifficultyDialog::createDifficultyButton(const QString& text, int difficulty)
{
    QPushButton *button = new QPushButton(text, this);
        button->setFixedSize(300, 80);
        button->setFont(QFont("华文行楷", 22, QFont::Bold));

        button->setStyleSheet(
            "QPushButton {"
            "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,"
            "                                      stop:0 rgba(44, 162, 222, 200),"
            "                                      stop:1 rgba(20, 100, 180, 200));"
            "    color: rgba(239, 201, 55);"
            "    border-radius: 15px;"
            "    border: 2px solid rgba(255, 255, 255, 50);"
            "    padding: 10px;"
            "}"
            "QPushButton:hover {"
            "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,"
            "                                      stop:0 rgba(54, 172, 232, 220),"
            "                                      stop:1 rgba(30, 110, 190, 220));"
            "}"
            "QPushButton:pressed {"
            "    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,"
            "                                      stop:0 rgba(34, 152, 212, 240),"
            "                                      stop:1 rgba(10, 90, 170, 240));"
            "}"
        );

        connect(button, &QPushButton::clicked, [this, difficulty]() {
            emit difficultySelected(difficulty);

            // 修改为更安全的类型转换
                   if (BattlePlay* battlePlay = dynamic_cast<BattlePlay*>(parent())) {
                       battlePlay->stopTimer();
                   }

                   this->accept();
               });

           return button;
}

