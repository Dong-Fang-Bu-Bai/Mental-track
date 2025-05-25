#include "BattlePlay.h"
#include "ui_BattlePlay.h"
#include "BattleGridScene.h"
#include "DifficultyDialog.h"
#include<QLabel>
#include <QPushButton>
#include <QMessageBox>
#include"gamedefine.h"
#include <QDebug>



BattlePlay::BattlePlay(User& user,QWidget *parent) :
    QWidget(parent),
    m_currentUser(&user),  // 初始化当前用户
    m_gameTimer(new QTimer(this)),
    m_timeLeft(0),
    m_timerLabel(new QLabel(this)),
    ui(new Ui::BattlePlay),
    m_battleScene(nullptr),
    m_view(nullptr)
{
    ui->setupUi(this);
    setupUI();
}

void BattlePlay::setCurrentUser(User* user)
{
    m_currentUser = user;
}

void BattlePlay::setupUI()
{

    // 1. 先初始化计时器标签 - 更新为更美观的样式
        m_timerLabel = new QLabel(this);
        m_timerLabel->setAlignment(Qt::AlignCenter);
        m_timerLabel->setGeometry(450, 0, 300, 75); // 你修改后的尺寸

        // 根据新尺寸调整圆角半径（高度的一半）
        int borderRadius = 37; // 75/2 ≈ 37

        m_timerLabel->setStyleSheet(
            QString(
            "QLabel {"
            "   background: qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, "
            "                               stop:0 rgba(20, 20, 50, 220), "
            "                               stop:1 rgba(0, 0, 30, 220));"
            "   border-radius: %1px;"  // 动态设置圆角半径
            "   padding: 10px;"
            "   font-size: 40px;"
            "   font-weight: bold;"
            "   color: #00FFFF;"
            "   border: 3px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, "
            "                                     stop:0 #00FFFF, stop:1 #0080FF);"
            "   min-width: 100px;"
            "}"
            ).arg(borderRadius)
        );

        // 添加发光效果
        QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
        shadowEffect->setBlurRadius(15);
        shadowEffect->setColor(QColor(0, 200, 255, 150));
        shadowEffect->setOffset(0, 0);
        m_timerLabel->setGraphicsEffect(shadowEffect);

        m_timerLabel->raise(); // 确保在最上层
        m_timerLabel->show();  // 显式显示

        // 连接计时器信号
        connect(m_gameTimer, &QTimer::timeout, this, &BattlePlay::onTimerTimeout);


    // 设置窗口属性
    setFixedSize(1200, 1300);
    setWindowTitle("人机对战");

    //设置背景图片
    QLabel *label_Background=new QLabel(this);
    label_Background->setGeometry(0,0,1200,1300);
    label_Background->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    label_Background->setScaledContents(true);


    connect(m_battleScene, &BattleGridScene::gameStarted, this, [this]() {
        startTimer();
    });

    connect(m_battleScene, &BattleGridScene::stateChanged, this, [this]() {
        if(m_battleScene->getState() != BattleGridScene::PlayerTurn) {
            stopTimer();
        }
    });


    //4.暂停按钮
    QPushButton*btn_pause=new QPushButton(this);

    // 设置文字字体和大小
    btn_pause->setGeometry(20,2,200,70);
    btn_pause->setText("暂停");
    QFont font("华文行楷", 25, QFont::Bold);
    btn_pause->setFont(font);

    // 设置样式表（包含正常/悬浮/点击状态）
    btn_pause->setStyleSheet(
        "QPushButton {"
        "     background-color: rgba(44, 162, 222 ,60%);"  // 蓝色背景，80% 透明
        "   color: Black;"               // 文字颜色
        "   border-radius: 10px;"        // 圆角
        "   padding: 5px;"               // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(44, 162, 222 ,70%);"  // 悬浮状态背景色
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(44, 162, 222 ,80%);"  // 点击状态背景色
        "}"
    );

    //暂停按钮连接
     connect(btn_pause, &QPushButton::clicked, this, &BattlePlay::onPauseButtonClicked);

     // 初始化暂停覆盖层（但不显示）
     m_pauseOverlay = new QWidget(this);
     m_pauseOverlay->setGeometry(0, 0, width(), height());
     m_pauseOverlay->setStyleSheet("background-color: rgba(180, 207, 209, 50%);");
     m_pauseOverlay->hide();



 // 创建场景和视图
     m_battleScene = new BattleGridScene(17, this);
     m_view = new QGraphicsView(m_battleScene, this);
     m_view->setGeometry(20, 70, 1160, 1160);
     m_view->setStyleSheet("background: transparent; border: none;");



     // 连接场景信号
  connect(m_battleScene, &BattleGridScene::gameStarted, this, &BattlePlay::startTimer);

  connect(m_battleScene, &BattleGridScene::stateChanged, this, [this]()
  {
                if(m_battleScene->getState() != BattleGridScene::PlayerTurn)
                {
                    stopTimer();
                }
                else
                {
                    startTimer(); // 恢复计时器
                }
  });



    // 创建开始游戏按钮
    QPushButton* btnNewGame = new QPushButton("开始游戏", this);
    btnNewGame->setGeometry(450, 1230, 300, 70);
    //btnNewGame->setGeometry(500, 900, 200, 60);

    btnNewGame->setFont(font);

    // 设置样式表（包含正常/悬浮/点击状态）
    btnNewGame->setStyleSheet(
        "QPushButton {"
        "     background-color: rgba(44, 162, 222 , 60%);"  // 蓝色背景，80% 透明
        "   color: Black;"               // 文字颜色
        "   border-radius: 10px;"        // 圆角
        "   padding: 5px;"               // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(44, 162, 222 , 70%);"  // 悬浮状态背景色
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(44, 162, 222 , 80%);"  // 点击状态背景色
        "}"
    );

    // 修改setupUI中的开始游戏按钮连接
    connect(btnNewGame, &QPushButton::clicked, this, [this]()
    {
        AudioManager::instance()->playEffect();
        showDifficultyDialog();
    });



    // 连接游戏结束信号
    connect(m_battleScene, &BattleGridScene::gameOver, this, &BattlePlay::onGameOver);
}


void BattlePlay::showDifficultyDialog()
{
    // 清除可能的暂停状态
    if (m_pauseOverlay)
    {
        m_pauseOverlay->hide();
    }

    // 暂停游戏进程和计时器
        if(m_battleScene)
        {
            m_battleScene->stopGame();
        }

        // 创建遮罩效果
        QGraphicsColorizeEffect* colorEffect = new QGraphicsColorizeEffect;
        colorEffect->setColor(Qt::black);
        colorEffect->setStrength(0.9);
        m_view->setGraphicsEffect(colorEffect);

        DifficultyDialog *dialog = new DifficultyDialog(this);
        dialog->setModal(true);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        dialog->setWindowFlags(dialog->windowFlags() | Qt::WindowStaysOnTopHint);

        // 居中显示
        QPoint centerPos = mapToGlobal(rect().center());
        centerPos -= QPoint(dialog->width()/2, dialog->height()/2);
        dialog->move(centerPos);

        connect(dialog, &DifficultyDialog::difficultySelected, this, [this](int diff)
        {
            if(m_battleScene) stopTimer();
            onDifficultySelected(diff);

            // 对话框关闭后恢复计时器标签
            m_timerLabel->show();
            m_timerLabel->raise();
        });

        connect(dialog, &QDialog::finished, this, [this]()
        {
            m_view->setGraphicsEffect(nullptr);

            // 确保计时器标签可见
            m_timerLabel->show();
            m_timerLabel->raise();
        });

        dialog->exec();

}

void BattlePlay::onDifficultySelected(int difficulty)
{
    qDebug() << "onDifficultySelected - Begin";

       // 1. 先停止所有可能的活动
       if(m_battleScene) {
           qDebug() << "Stopping scene activities";
           stopTimer();
       }

       // 2. 启动新游戏
       if(m_battleScene)
       {
           qDebug() << "Starting new game";
           m_battleScene->startNewGame(static_cast<BattleGridScene::Difficulty>(difficulty));
           m_pausedTimeLeft = 0; // 重置暂停时间记录
           startTimer(); // 游戏开始后立即启动计时器
       }

       qDebug() << "onDifficultySelected - End";

}

void BattlePlay::onGameOver(bool playerWon)
{

    if(m_currentUser) {
            int points = 0;
            switch(m_battleScene->getDifficulty()) {
                case BattleGridScene::Easy: points = 10; break;
                case BattleGridScene::Medium: points = 20; break;
                case BattleGridScene::Hard: points = 30; break;
            }

            // 直接通过指针更新用户数据
            m_currentUser->addBattleResult(playerWon, points);

            // 添加调试输出
            qDebug() << "Updating battle stats - Wins:" << m_currentUser->getBattleWins()
                     << " Total:" << m_currentUser->getBattleTotal()
                     << " Points:" << m_currentUser->getBattlePoints();

            // 保存用户数据
            bool saveSuccess = UserFileManager::saveUser(*m_currentUser, "users.dat");

            if(!saveSuccess) {
                qDebug() << "Failed to save user data!";
                QMessageBox::warning(this, "错误", "无法保存用户数据");
            }
            else
            {
                qDebug() << "User data saved successfully";

                // 验证保存结果
                std::vector<User> users;
                if(UserFileManager::loadUsers(users, "users.dat"))
                {
                    for(const auto& u : users)
                    {
                        if(u.getUsername() == m_currentUser->getUsername())
                       {
                            qDebug() << "Verified save - Wins:" << u.getBattleWins()
                                     << " Total:" << u.getBattleTotal()
                                     << " Points:" << u.getBattlePoints();
                        }
                    }
                }
            }
        }

    // 确保游戏完全停止
    if(m_battleScene)
    {
        m_battleScene->stopGame();
    }

    QMessageBox msgBox;
    msgBox.setText(playerWon ? "恭喜你获胜了！" : "电脑获得了胜利");
    msgBox.setInformativeText("是否再来一局？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    int result = msgBox.exec();

    if(result == QMessageBox::Yes)
    {
       showDifficultyDialog();
    }
    else
    {
       this->close();
       getGlobalModeWindow()->show();
    }
}

void BattlePlay::startTimer()
{
    qDebug() << "Attempting to start timer";
        stopTimer();

        if(!m_battleScene)
        {
            qDebug() << "No battle scene, cannot start timer";
            return;
        }

        // 确保标签可见
        m_timerLabel->show();
        m_timerLabel->raise();

        // 根据难度设置时间
        switch(m_battleScene->getDifficulty()) {
            case BattleGridScene::Easy: m_timeLeft = 10; break;
            case BattleGridScene::Medium: m_timeLeft = 8; break;
            case BattleGridScene::Hard: m_timeLeft = 6; break;
        }

        m_pausedTimeLeft = m_timeLeft; // 重置暂停时间记录

        qDebug() << "Timer started with:" << m_timeLeft << "seconds";
        updateTimerDisplay();
        m_gameTimer->start(1000);
}

void BattlePlay::stopTimer()
{
    m_gameTimer->stop();
    m_timerLabel->setText("");
}

void BattlePlay::updateTimerDisplay()
{
    // 根据新尺寸调整圆角半径
       int borderRadius = 37;

       // 更新计时器显示，根据剩余时间改变样式
       QString styleSheet = QString(
           "QLabel {"
           "   background: qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, "
           "                               stop:0 %1, "
           "                               stop:1 %2);"
           "   border-radius: %3px;"
           "   padding: 10px;"
           "   font-size: 40px;"
           "   font-weight: bold;"
           "   color: %4;"
           "   border: 3px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, "
           "                                     stop:0 %5, stop:1 %6);"
           "}"
       );

       if(m_timeLeft <= 3) {
           // 紧急状态样式（红色闪烁效果）
           styleSheet = styleSheet.arg(
               "rgba(80, 0, 0, 220)",  // 渐变开始颜色
               "rgba(50, 0, 0, 220)",  // 渐变结束颜色
               QString::number(borderRadius),
               "#FF6060",               // 文字颜色
               "#FF0000",              // 边框渐变开始
               "#FF8000"               // 边框渐变结束
           );
       } else {
           // 正常状态样式
           styleSheet = styleSheet.arg(
               "rgba(20, 20, 50, 220)",
               "rgba(0, 0, 30, 220)",
               QString::number(borderRadius),
               "#00FFFF",
               "#00FFFF",
               "#0080FF"
           );
       }

       m_timerLabel->setStyleSheet(styleSheet);
       m_timerLabel->setText(QString::number(m_timeLeft));
}

void BattlePlay::onTimerTimeout()
{

    qDebug() << "Timer timeout, time left:" << m_timeLeft;

       if(!m_battleScene || m_battleScene->getState() != BattleGridScene::PlayerTurn) {
           qDebug() << "Not player turn or no scene, stopping timer";
           stopTimer();
           return;
       }

       m_timeLeft--;
       updateTimerDisplay();

       if(m_timeLeft <= 0) {
           qDebug() << "Time out, handling player move";
           stopTimer();
           if(m_battleScene) {
               m_battleScene->handleTimeout();
           }
       }
}

void BattlePlay::onPauseButtonClicked()
{
    AudioManager::instance()->playEffect();

    // 如果已经暂停，则继续游戏
        if (m_pauseOverlay && m_pauseOverlay->isVisible())
        {
            resumeGame();
            return;
        }

        // 暂停游戏
        m_pausedTimeLeft = m_timeLeft; // 保存当前剩余时间
        stopTimer();  // 停止计时器

        // 显示半透明覆盖层
        m_pauseOverlay->show();
        m_pauseOverlay->raise();

        // 创建暂停菜单容器
        QWidget* pauseContainer = new QWidget(m_pauseOverlay);
        pauseContainer->setGeometry(0, 0, width(), height());
        pauseContainer->setStyleSheet("background: transparent;");

        // 创建居中菜单
        QWidget* pauseMenu = new QWidget(pauseContainer);
        pauseMenu->setFixedSize(450, 400);
        pauseMenu->move(width()/2 - 225, height()/2 - 200);
        pauseMenu->setStyleSheet(
            "background-color: rgba(37, 169, 230, 90%);"
            "border-radius: 95px;"
        );

        // 设置暂停界面标题
        QLabel* title = new QLabel(pauseMenu);
        title->setGeometry(75,0,300,75);
        QFont font("华文行楷", 20, QFont::Bold);
        title->setFont(font);
        title->setText("游戏已暂停");
        title->setStyleSheet("color: black;");
        title->setAlignment(Qt::AlignCenter);

        QFont btnFont("华文行楷", 17);

        // 1.继续游戏按钮
        QPushButton* resumeBtn = new QPushButton("继续游戏", pauseMenu);
        resumeBtn->setFont(btnFont);
        resumeBtn->setGeometry(112,70, 225, 60);
        resumeBtn->setStyleSheet(
            "QPushButton {"
            "   background-color: rgba(119, 187, 140, 80%);"
            "   border-radius: 16px;"
            "   color: black;"
            "   padding: 10px;"
            "}"
            "QPushButton:hover { background-color: rgba(119, 187, 140, 100%); }"
        );
        connect(resumeBtn, &QPushButton::clicked, this, &BattlePlay::resumeGame);

        // 2.重新开始按钮
        QPushButton* restartBtn = new QPushButton("重新开始", pauseMenu);
        restartBtn->setFont(btnFont);
        restartBtn->setGeometry(112, 150, 225, 60);
        restartBtn->setStyleSheet(resumeBtn->styleSheet());
        connect(restartBtn, &QPushButton::clicked, this, &BattlePlay::restartLevel);

        // 3.退出游戏按钮
        QPushButton* exitBtn = new QPushButton("退出游戏", pauseMenu);
        exitBtn->setFont(btnFont);
        exitBtn->setGeometry(112, 230, 225, 60);
        exitBtn->setStyleSheet(resumeBtn->styleSheet());
        connect(exitBtn, &QPushButton::clicked, [this]()
        {
            AudioManager::instance()->playEffect();
            this->close();
            getGlobalModeWindow()->show();
        });

        // 4.帮助按钮
        QPushButton* helpBtn = new QPushButton("帮助", pauseMenu);
        helpBtn->setFont(btnFont);
        helpBtn->setGeometry(112, 310, 225, 60);
        helpBtn->setStyleSheet(resumeBtn->styleSheet());
        connect(helpBtn, &QPushButton::clicked, [pauseMenu]()
        {
            AudioManager::instance()->playEffect();
            Help* help = new Help(pauseMenu);
            help->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
            help->setAttribute(Qt::WA_DeleteOnClose, true);
            pauseMenu->hide();
            help->show();
        });

        // 确保菜单可见
        pauseContainer->show();
        pauseMenu->show();
}

void BattlePlay::resumeGame()
{
    AudioManager::instance()->playEffect();

    // 隐藏暂停覆盖层
        if (m_pauseOverlay) {
            m_pauseOverlay->hide();
        }

        // 如果是玩家回合则重新启动计时器
        if (m_battleScene && m_battleScene->getState() == BattleGridScene::PlayerTurn)
        {
            m_timeLeft = m_pausedTimeLeft; // 恢复暂停时的剩余时间
            updateTimerDisplay(); // 更新显示
            m_gameTimer->start(1000); // 重新启动计时器
        }
}

void BattlePlay::restartLevel()
{
    AudioManager::instance()->playEffect();

    // 关闭暂停菜单
    m_pauseOverlay->hide();
    // 显示难度选择界面
    showDifficultyDialog();
}



BattlePlay::~BattlePlay()
{
    qDebug() << "~BattlePlay - Begin";

        // 删除遮罩层（如果存在）
        if (m_mask) {
            m_mask->deleteLater();
            m_mask = nullptr;
        }

        // 删除暂停覆盖层
        if (m_pauseOverlay) {
            m_pauseOverlay->deleteLater();
            m_pauseOverlay = nullptr;
        }

        // 1. 停止所有活动
        stopTimer();

        // 2. 先删除视图(会自动删除场景)
        if (m_view) {
            qDebug() << "Deleting view";
            delete m_view;  // 这会自动删除m_battleScene
            m_view = nullptr;
            m_battleScene = nullptr;
        }

        // 4. 最后删除UI
        delete ui;

        qDebug() << "~BattlePlay - End";
}
