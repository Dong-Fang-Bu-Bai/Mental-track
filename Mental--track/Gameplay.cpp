#include "Gameplay.h"
#include "ui_Gameplay.h"
#include"Gridscene.h"
#include"Displaygridscene.h"
#include"Interactivegridscene.h"
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
    m_elapsedTime(0)
{
    ui->setupUi(this);

    this->setWindowTitle("游戏界面");
    this->setFixedSize(2400,1300);

    // 设置背景
    QLabel *Label_loginbackground=new QLabel(this);
    Label_loginbackground->setGeometry(0,0,2400,1300);
    Label_loginbackground->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    Label_loginbackground->setScaledContents(true);  // 关键：启用自动缩放

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
       m_timeLabel->setText("时间: 00:00");
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

        DisplayGridScene *displayScene = new DisplayGridScene(17);
        InteractiveGridScene *interactiveScene = new InteractiveGridScene(17);

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

        QPushButton*btn=new QPushButton("提交",this);
        btn->setGeometry(1150,1100,100,50);


        connect(btn,&QPushButton::clicked,[=]()
        {


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

                 QMessageBox::information(this, "成功", "路径验证成功！\n" + timeStr);

                qDebug() << "成功！用时:" << m_elapsedTime << "秒";
            }
            else
            {
                QMessageBox::warning(this, "失败", "路径验证失败！");
                qDebug()<<"失败！"<<endl;
            }

        });
    }

  }
  else
  {
      QMessageBox::critical(nullptr, "错误", "关卡文件不存在");
  }



  // 添加返回按钮
     m_returnButton = new QPushButton("返回地图", this);
     m_returnButton->setGeometry(2000, 1200, 100, 50); // 调整位置
     connect(m_returnButton, &QPushButton::clicked, this, &Gameplay::onReturnButtonClicked);

}

void Gameplay::updateTimer() {
    m_elapsedTime++;

    // 更新显示 (格式: 分钟:秒)
    int seconds = m_elapsedTime % 60;
    int minutes = m_elapsedTime / 60;
    m_timeLabel->setText(QString("时间: %1:%2")
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

        in.setCodec("UTF-8"); // 旧版Qt用法


       enum Section { None, Player, Enemy };
       Section current = None;

       while (!in.atEnd()) {
           QString line = in.readLine().trimmed();

           // 跳过空行和纯注释行
           if (line.isEmpty() || line.startsWith("#")) {
               continue;
           }

           // 处理章节标记
           if (line == "[Player]") {
               current = Player;
               continue;
           } else if (line == "[Enemy]") {
               current = Enemy;
               continue;
           }

           // 解析坐标行（支持"x,y"或"x,y #注释"格式）
           QString coordStr = line.split("#")[0].trimmed(); // 移除右侧注释
           QStringList coords = coordStr.split(",");

           if (coords.size() == 2) {
               bool okX, okY;
               int x = coords[0].trimmed().toInt(&okX);
               int y = coords[1].trimmed().toInt(&okY);

               if (okX && okY) {
                   QPoint pt(x, y);
                   if (current == Player) {
                       playerPath.append(pt);
                   } else if (current == Enemy) {
                       enemyPath.append(pt);
                   }
               }
           }
       }

       // 调试输出
       qDebug() << "Player path:" << playerPath;
       qDebug() << "Enemy path:" << enemyPath;

       return !playerPath.isEmpty() && !enemyPath.isEmpty();
}

void Gameplay::onReturnButtonClicked()
{
    emit returnToMapRequested();// 先发射信号
    this->close(); // 然后关闭窗口
}

Gameplay::~Gameplay()
{
    delete ui;
    delete m_timer;
    delete m_timeLabel;
}
