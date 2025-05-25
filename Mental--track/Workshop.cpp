#include "Workshop.h"
#include "ui_Workshop.h"
#include<QLabel>
#include<QPushButton>
#include <QMessageBox>
#include<QRegularExpression>
#include"gamedefine.h"


Workshop::Workshop(User& user,QWidget *parent) :
    QWidget(parent),ui(new Ui::Workshop), m_currentUser(&user),// 存储指针
    m_isPlayerPathDone(false)
{

    ui->setupUi(this);
    this->setFixedSize(1200,1300);
     this->setWindowTitle("创意工坊");

     //设置背景图片
     QLabel *label_Background=new QLabel(this);
     label_Background->setGeometry(0,0,1200,1300);
     label_Background->setPixmap(QPixmap(":/img/Debug/image/login.png"));
     label_Background->setScaledContents(true);


     // 创建 返回主菜单 按钮
      QPushButton *pushButton_backMode=new QPushButton(this);
      pushButton_backMode->setGeometry(20, 10, 200, 60);
      pushButton_backMode->setText("主菜单");

      // 设置文字字体和大小
      QFont font("华文行楷", 25, QFont::Bold);

      pushButton_backMode->setFont(font);

      // 设置样式表（包含正常/悬浮/点击状态）
      pushButton_backMode->setStyleSheet(
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

   // 连接带编号的信号槽
  connect(pushButton_backMode, &QPushButton::clicked, [=]()
  {
      AudioManager::instance()->playEffect();
      this->hide();
      getGlobalModeWindow()->show();
  });


  // 1. 创建视图和场景
  //元素--> 场景 --> 视图 -->窗口
  //创建视图视图
  QGraphicsView *view = new QGraphicsView(this);
  m_workshopScene=new Workshopgridscene(17);
   // 2. 关联场景和视图
  view->setScene(m_workshopScene);

  // 在创建视图后添加：
  view->setStyleSheet("QGraphicsView { background: transparent; border: none; }");
  view->setFrameShape(QFrame::NoFrame);

  // 3. 手动设置视图位置和大小 (x, y, width, height)
  view->setGeometry(20, 70, 1160, 1160);

  //连接场景信号
  //connect(m_workshopScene, &Workshopgridscene::pathCompleted, this, &Workshop::onPathCompleted);
  connect(m_workshopScene, &Workshopgridscene::errorOccurred, this, &Workshop::onErrorOccurred);


  //创建确认按钮
  QPushButton*btn_confirm=new QPushButton(this);
  // 设置文字字体和大小
  btn_confirm->setGeometry(500,1230,200,70);
  //btn_confirm->setGeometry(500,850,200,70);
  btn_confirm->setText("确认");
  btn_confirm->setFont(font);

  // 设置样式表（包含正常/悬浮/点击状态）
  btn_confirm->setStyleSheet(
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
   connect(btn_confirm, &QPushButton::clicked, this, &Workshop::onConfirmClicked);

  //创建后退按钮
  QPushButton*btn_back=new QPushButton(this);
  // 设置文字字体和大小
  btn_back->setGeometry(250,1230,200,70);
  //btn_back->setGeometry(250,850,200,70);
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

  //设置点击逻辑
  connect(btn_back, &QPushButton::clicked, [=]()
  {
      AudioManager::instance()->playEffect();
      if (m_isPlayerPathDone) {
          if (m_workshopScene->getEnemyPath().isEmpty())
          {
              // 敌人路径已空，切换回玩家路径编辑
              m_isPlayerPathDone = false;
              m_workshopScene->setEditMode(Workshopgridscene::PlayerPath);
          } else
          {
              m_workshopScene->undoLastStep();
          }
      }
      else
      {
          m_workshopScene->undoLastStep();
      }
  });




  //创建清空按钮
  QPushButton*btn_clear=new QPushButton(this);
  // 设置文字字体和大小
  btn_clear->setGeometry(750,1230,200,70);
  //btn_clear->setGeometry(750,850,200,70);
  btn_clear->setText("清空");
  btn_clear->setFont(font);

  // 设置样式表（包含正常/悬浮/点击状态）
  btn_clear->setStyleSheet(
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
  connect(btn_clear, &QPushButton::clicked, [=]()
  {
      AudioManager::instance()->playEffect();
      m_workshopScene->clearPaths();
      m_isPlayerPathDone = false;
  });

}


void Workshop::onConfirmClicked()
{
    AudioManager::instance()->playEffect();

    if (!m_isPlayerPathDone)
    {
        // First confirm - switch to enemy path editing
        if (m_workshopScene->getPlayerPath().size() < 3)
        {
            QMessageBox::warning(this, "提示", "路径太短，请至少设置3个点");
            return;
        }

        m_workshopScene->setEditMode(Workshopgridscene::EnemyPath);
        m_isPlayerPathDone = true;
        m_workshopScene->updateGridDisplay(); // 更新显示
    }
    else
    {
        // Second confirm - verify and save
        if (!m_workshopScene->verifyPaths())
        {
            return;
        }

        // 在获取文件名前评估难度
        Workshopgridscene::Difficulty difficulty = m_workshopScene->evaluateDifficulty();
        QString difficultyStr;
        switch(difficulty)
        {
            case Workshopgridscene::Beginner: difficultyStr = "初级"; break;
            case Workshopgridscene::Intermediate: difficultyStr = "中级"; break;
            case Workshopgridscene::Advanced: difficultyStr = "高级"; break;
        }


        // 修改获取文件名的提示信息
        bool ok;
        QString fileName = QInputDialog::getText(this, "保存路径",
            QString("当前路径难度: %1\n请输入关卡名称(仅限英文字母):").arg(difficultyStr),
            QLineEdit::Normal, "", &ok);

        if (!ok || fileName.isEmpty()) {
            return;
        }

        // Validate filename
        if (!fileName.contains(QRegularExpression("^[a-zA-Z0-9_]+$"))) {
            QMessageBox::warning(this, "错误", "文件名只能包含字母和数字");
            return;
        }

        // Save to file
        if (m_workshopScene->saveToFile(fileName.toStdString(), m_currentUser->getUsername()))
        {

            // 更新用户数据
               m_currentUser->incrementCreatedMaps();

               // 根据难度增加积分
               switch(difficulty) {
                   case Workshopgridscene::Beginner:
                       m_currentUser->addWorkshopPoints(10); break;
                   case Workshopgridscene::Intermediate:
                       m_currentUser->addWorkshopPoints(20); break;
                   case Workshopgridscene::Advanced:
                       m_currentUser->addWorkshopPoints(30); break;
               }

               // 保存用户数据
               UserFileManager::saveUser(*m_currentUser);


            QMessageBox::information(this, "成功", "路径创建成功！");
            m_workshopScene->clearPaths();
            m_isPlayerPathDone = false;

        }
    }
}


void Workshop::onErrorOccurred(const QString& message)
{
    QMessageBox::warning(this, "错误", message);
}


Workshop::~Workshop()
{
    delete ui;
}
