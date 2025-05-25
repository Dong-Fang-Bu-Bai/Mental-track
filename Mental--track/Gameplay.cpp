#include "Gameplay.h"
#include "ui_Gameplay.h"
#include"Gridscene.h"
#include"Pathcalculator.h"
#include<QGraphicsView>
#include<QPushButton>
#include<QFile>
#include<QMessageBox>
#include"gamedefine.h"

Gameplay::Gameplay(const QString& levelPath, int levelId, User* currentUser, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gameplay),
    m_levelPath(levelPath),
    m_levelId(levelId),
    m_currentUser(currentUser),
    m_elapsedTime(0),
    m_isPaused(false)
{
    ui->setupUi(this);

    this->setWindowTitle("游戏界面");
    this->setFixedSize(2400,1300);

    // 设置背景
    QLabel *Label_playbackground=new QLabel(this);
    Label_playbackground->setGeometry(0,0,2400,1300);
    Label_playbackground->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    Label_playbackground->setScaledContents(true);  // 关键：启用自动缩放

    // 创建并设置计时器标签
       m_timeLabel = new QLabel(this);
       m_timeLabel->setGeometry(2000, 20, 300, 50); // 右上角位置
       m_timeLabel->setStyleSheet("QLabel {"
                                  "font-size: 24px;"
                                  "color: white;"
                                  "background-color: rgba(0,0,0,50%);"
                                  "border-radius: 10px;"
                                  "padding: 5px;"
                                  "}");
       m_timeLabel->setText("用时: 00:00");
       m_timeLabel->setAlignment(Qt::AlignCenter);

       // 初始化计时器
       m_timer = new QTimer(this);
       connect(m_timer, &QTimer::timeout, this, &Gameplay::updateTimer);
       m_timer->start(1000); // 每秒触发一次



    // 加载关卡
      QVector<QPoint> playerPath, enemyPath;

  if (loadLevel(m_levelPath, playerPath, enemyPath))
   {

    QVector<QPoint> relativePath;
    // 计算相对路径
    if(Pathcalculator::setPaths(playerPath, enemyPath,relativePath, 17))
    {
        // 1. 创建视图和场景
        //元素--> 场景 --> 视图 -->窗口
        //创建视图视图
        QGraphicsView *view1 = new QGraphicsView(this);
        QGraphicsView *view2 = new QGraphicsView(this);
         // 场景直接传入网格尺寸

        displayScene = new DisplayGridScene(17);
        interactiveScene = new InteractiveGridScene(17);

         // 设置显示场景、交互场景
         displayScene->setPaths(playerPath, relativePath);

         interactiveScene->setStartEnd(enemyPath.first(),
                                       enemyPath.last(),
                                       enemyPath);

         // 3. 关联场景和视图
        view1->setScene(displayScene);
        view2->setScene(interactiveScene);

        // 在创建视图后添加：
        view1->setStyleSheet("QGraphicsView { background: transparent; border: none; }");
        view2->setStyleSheet("QGraphicsView { background: transparent; border: none; }");
        view1->setFrameShape(QFrame::NoFrame);
        view2->setFrameShape(QFrame::NoFrame);

        // 4. 手动设置视图位置和大小 (x, y, width, height)
        view1->setGeometry(20, 70, 1160, 1160);
        view2->setGeometry(1220, 70, 1160, 1160);


        //1.验证按钮
        QPushButton*btn_check=new QPushButton(this);
        // 设置文字字体和大小
        QFont font("华文行楷", 25, QFont::Bold);
        btn_check->setGeometry(1100,1230,200,70);
        //btn_check->setGeometry(1100,800,200,70);
        btn_check->setText("提交");
        btn_check->setFont(font);

        // 设置样式表（包含正常/悬浮/点击状态）
        btn_check->setStyleSheet(
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

        //设置点击逻辑
        connect(btn_check,&QPushButton::clicked,[=]()
        {
            AudioManager::instance()->playEffect();

            if( interactiveScene->verifyUserPath())
            {
                // 在验证成功后添加
                emit levelCompleted(m_levelId);

                m_timer->stop(); // 停止计时器
                // 计算用时(秒)
                float completionTime = static_cast<float>(m_elapsedTime);


                // 更新用户数据
                if(m_currentUser)
                {
                    m_currentUser->setLevelPassed(m_levelId, true);
                    m_currentUser->setLevelCompletionTime(m_levelId, completionTime);

                    // 保存用户数据（使用新增的saveUser方法）
                    if(!UserFileManager::saveUser(*m_currentUser))
                    {
                        QMessageBox::warning(this, "警告", "用户数据保存失败！");
                    }
                }

                // 计算用时(分钟:秒),显示完成信息
                 int seconds = m_elapsedTime % 60;
                 int minutes = m_elapsedTime / 60;
                 QString timeStr = QString("完成时间: %1:%2")
                 .arg(minutes, 2, 10, QChar('0'))
                 .arg(seconds, 2, 10, QChar('0'));

                 QMessageBox::information(this, "成功", "恭喜您成功通关！\n" + timeStr);

                //qDebug() << "成功！用时:" << m_elapsedTime << "秒";

                onReturnButtonClicked();
            }
            else
            {
                QMessageBox::warning(this, "失败", "路径验证失败！");
                qDebug()<<"失败！"<<endl;
            }

        });


        //2.步数后退按钮
        QPushButton*btn_back=new QPushButton(this);

        // 设置文字字体和大小
        btn_back->setGeometry(700,1230,200,70);
        btn_back->setText("后退");
        btn_back->setFont(font);

        // 设置样式表（包含正常/悬浮/点击状态）
        btn_back->setStyleSheet(
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

        // 在Gameplay.cpp中修改后退按钮连接逻辑
        connect(btn_back, &QPushButton::clicked, [=]()
        {
            AudioManager::instance()->playEffect();
            // 调用场景的后退方法
            interactiveScene->undoLastStep();

            // 增加5秒计时
            m_elapsedTime += 5;
            updateTimer(); // 立即更新显示

            qDebug() << "后退一步，增加5秒惩罚时间";
        });


        //3.清空按钮
        QPushButton*btn_clear=new QPushButton(this);

        // 设置文字字体和大小
        btn_clear->setGeometry(1500,1230,200,70);
        btn_clear->setText("清空");
        btn_clear->setFont(font);

        // 设置样式表（包含正常/悬浮/点击状态）
        btn_clear->setStyleSheet(
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

        // 修改清空按钮连接逻辑
        connect(btn_clear, &QPushButton::clicked, [=]()
        {
            AudioManager::instance()->playEffect();
            interactiveScene->clearUserPath();
            qDebug() << "路径已清空";
        });


        //4.暂停按钮
        QPushButton*btn_pause=new QPushButton(this);

        // 设置文字字体和大小
        btn_pause->setGeometry(20,2,200,70);
        btn_pause->setText("暂停");
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
         connect(btn_pause, &QPushButton::clicked, this, &Gameplay::onPauseButtonClicked);

         // 初始化暂停覆盖层（但不显示）
         m_pauseOverlay = new QWidget(this);
         m_pauseOverlay->setGeometry(0, 0, width(), height());
         m_pauseOverlay->setStyleSheet("background-color: rgba(180, 207, 209, 50%);");
         m_pauseOverlay->hide();

    }

  }
  else
  {
      QMessageBox::critical(nullptr, "错误", "关卡文件不存在");
  }





}

void Gameplay::updateTimer() {
    m_elapsedTime++;

    // 更新显示 (格式: 分钟:秒)
    int seconds = m_elapsedTime % 60;
    int minutes = m_elapsedTime / 60;
    m_timeLabel->setText(QString("用时: %1:%2")
                        .arg(minutes, 2, 10, QChar('0'))
                        .arg(seconds, 2, 10, QChar('0')));
}

bool Gameplay::loadLevel(const QString& filePath,
                        QVector<QPoint>& playerPath,
                        QVector<QPoint>& enemyPath)
{
    playerPath.clear();
       enemyPath.clear();

       QFile file(filePath);
       if (!file.open(QIODevice::ReadOnly)) {
           qWarning() << "Cannot open:" << filePath << "Error:" << file.errorString();
           return false;
       }

       QTextStream in(&file);
   #if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
       in.setCodec("UTF-8"); // 旧版Qt用法
   #else
       in.setEncoding(QStringConverter::Utf8); // Qt6+用法
   #endif

       enum Section { None, Player, Enemy };
       Section current = None;

       int lineNumber = 0;
       bool hasPlayerSection = false;
       bool hasEnemySection = false;

       while (!in.atEnd()) {
           lineNumber++;
           QString line = in.readLine().trimmed();

           // 跳过空行和纯注释行
           if (line.isEmpty() || line.startsWith("#")) {
               continue;
           }

           // 处理章节标记
           if (line == "[Player]") {
               current = Player;
               hasPlayerSection = true;
               continue;
           } else if (line == "[Enemy]") {
               current = Enemy;
               hasEnemySection = true;
               continue;
           }

           // 检查是否在有效的章节中
           if (current == None)
           {
               qWarning() << "Line" << lineNumber << ": Coordinate found outside of any section";
               continue;
           }

           // 解析坐标行（支持"x,y"或"x,y #注释"格式）
           QString coordStr = line.split("#")[0].trimmed(); // 移除右侧注释
           QStringList coords = coordStr.split(",", Qt::SkipEmptyParts);

           if (coords.size() != 2) {
               qWarning() << "Line" << lineNumber << ": Invalid coordinate format:" << line;
               continue;
           }

           bool okX, okY;
           int x = coords[0].trimmed().toInt(&okX);
           int y = coords[1].trimmed().toInt(&okY);

           if (!okX || !okY) {
               qWarning() << "Line" << lineNumber << ": Invalid coordinate values:" << line;
               continue;
           }

           QPoint pt(x, y);
           if (current == Player) {
               playerPath.append(pt);
           } else if (current == Enemy) {
               enemyPath.append(pt);
           }
       }

       file.close();

       // 调试输出
       qDebug() << "Player path:" << playerPath;
       qDebug() << "Enemy path:" << enemyPath;

       // 检查是否有必要的章节
       if (!hasPlayerSection || !hasEnemySection) {
           qWarning() << "Missing required sections in level file";
           return false;
       }

       return !playerPath.isEmpty() && !enemyPath.isEmpty();
}

void Gameplay::onReturnButtonClicked()
{
    AudioManager::instance()->playEffect();
    emit returnToMapRequested();// 先发射信号
    this->close(); // 然后关闭窗口
}

void Gameplay::onPauseButtonClicked()
{
    AudioManager::instance()->playEffect();
    if (m_isPaused)
    {
        resumeGame();
    } else
    {
        // 暂停游戏
        m_isPaused = true;
        m_timer->stop();  // 停止计时器

        // 显示半透明覆盖层
        m_pauseOverlay->show();
        m_pauseOverlay->raise(); // 确保在最上层

        // 创建暂停菜单容器
        QWidget* pauseContainer = new QWidget(m_pauseOverlay);
        pauseContainer->setGeometry(0, 0, m_pauseOverlay->width(), m_pauseOverlay->height());
        pauseContainer->setStyleSheet("background: transparent;");

        // 创建居中菜单
        QWidget* pauseMenu = new QWidget(pauseContainer);
        pauseMenu->setFixedSize(900, 800);
        pauseMenu->move(width()/2 - 450, height()/2 - 400);
        pauseMenu->setStyleSheet
        (
            "background-color: rgba(37, 169, 230, 90%);"
            "border-radius: 190px;"

        );


        //设置暂停界面标题
        QLabel* title = new QLabel(pauseMenu);
        title->setGeometry(150,0,600,150);
        QFont font("华文行楷", 40, QFont::Bold);
        title->setFont(font);
        title->setText("游戏已暂停");
        title->setStyleSheet("color: black;");
        title->setAlignment(Qt::AlignCenter);  // 关键：文字居中



         QFont font1("华文行楷", 33 );//QFont::Bold
        //1.继续游戏按钮
        QPushButton* resumeBtn = new QPushButton("继续游戏", pauseMenu);
        resumeBtn->setFont(font1);
        resumeBtn->setGeometry(225,140, 450, 120); // 调整位置
        resumeBtn->setStyleSheet
        (
            "QPushButton {"
            "   background-color: rgba(119, 187, 140  , 80%);"
            "  border-radius: 32px;"
            "   color: black;"
            "   padding: 10px;"

            "}"
            "QPushButton:hover { background-color:rgba(119, 187, 140 , 100%); }"
        );

         connect(resumeBtn, &QPushButton::clicked, this, &Gameplay::resumeGame);

         //2.重新开始按钮
           QPushButton* m_restartButton = new QPushButton("重新开始", pauseMenu);
            m_restartButton->setFont(font1);
            m_restartButton->setGeometry(225, 300, 450, 120); // 调整位置

            m_restartButton->setStyleSheet
            (
                        "QPushButton {"
                        "   background-color: rgba(119, 187, 140  , 80%);"
                        "  border-radius: 32px;"
                        "   color: black;"
                        "   padding: 10px;"

                        "}"
                        "QPushButton:hover { background-color:rgba(119, 187, 140 , 100%); }"
            );

            connect(m_restartButton, &QPushButton::clicked, this, &Gameplay::restartLevel);


         //3.返回地图按钮（退出当前关卡）
            m_returnButton = new QPushButton("返回地图", pauseMenu);
            m_returnButton->setFont(font1);
            m_returnButton->setGeometry(225, 460, 450, 120); // 调整位置

            m_returnButton->setStyleSheet
            (
             "QPushButton {"
             "   background-color: rgba(119, 187, 140  , 80%);"
             "  border-radius: 32px;"
             "   color: black;"
             "   padding: 10px;"
             "}"
             "QPushButton:hover { background-color:rgba(119, 187, 140 , 100%); }"
            );

            connect(m_returnButton, &QPushButton::clicked, this, &Gameplay::onReturnButtonClicked);

            //4.帮助按钮
               QPushButton* m_HelpButton = new QPushButton("帮助", pauseMenu);
               m_HelpButton->setFont(font1);
               m_HelpButton->setGeometry(225, 620, 450, 120); // 调整位置

               m_HelpButton->setStyleSheet
               (
                           "QPushButton {"
                           "   background-color: rgba(119, 187, 140  , 80%);"
                           "  border-radius: 32px;"
                           "   color: black;"
                           "   padding: 10px;"

                           "}"
                           "QPushButton:hover { background-color:rgba(119, 187, 140 , 100%); }"
               );

               connect(m_HelpButton, &QPushButton::clicked, [=]()
               {
                   AudioManager::instance()->playEffect();
                   Help *help = new Help(pauseMenu);  // 关键：传递当前窗口指针
                   help->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);  // 强制设为对话框
                   help->setAttribute(Qt::WA_DeleteOnClose, true);
                   pauseMenu->hide();
                   help->show();
               });



        // 确保菜单可见
        pauseContainer->show();
        pauseMenu->show();
        pauseMenu->raise();
    }
}

void Gameplay::resumeGame()
{
    AudioManager::instance()->playEffect();

    if (m_isPaused)
    {
        m_isPaused = false;
        m_timer->start();  // 恢复计时器
        setEnabled(true);  // 恢复交互

        // 隐藏覆盖层（会自动删除所有子控件）
        m_pauseOverlay->hide();

        // 显式删除所有子控件
        QList<QWidget*> children = m_pauseOverlay->findChildren<QWidget*>();
        for (QWidget* child : children)
        {
            child->deleteLater();
        }
    }
}

void Gameplay::restartLevel()
{
    AudioManager::instance()->playEffect();

    // 1. 停止计时器
     m_timer->stop();

     // 2. 重置计时器
     m_elapsedTime = 0;
     updateTimer();

     // 3. 清空场景
     if (interactiveScene)
     {
         interactiveScene->clearUserPath();

         // 重新设置起点终点
         QVector<QPoint> playerPath, enemyPath;
         if (loadLevel(m_levelPath, playerPath, enemyPath))
         {
             QVector<QPoint> relativePath;
             if (Pathcalculator::setPaths(playerPath, enemyPath, relativePath, 17))
             {
                 interactiveScene->setStartEnd
                 (
                     enemyPath.first(),
                     enemyPath.last(),
                     enemyPath
                 );
                 displayScene->setPaths(playerPath, relativePath);
             }
         }
     }

     // 4. 恢复游戏状态
     if (m_isPaused)
     {
         resumeGame();
     } else
     {
         m_timer->start();
     }
}


Gameplay::~Gameplay()
{
    delete ui;
    delete m_timer;
    delete m_timeLabel;
}
