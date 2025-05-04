#include "Workshop.h"
#include "ui_Workshop.h"
#include<QLabel>
#include<QPushButton>

Workshop::Workshop(User& user,QWidget *parent) :
    QWidget(parent),ui(new Ui::Workshop), m_currentUser(&user)// 存储指针
{

    ui->setupUi(this);
    this->setFixedSize(1200,1300);
     this->setWindowTitle("创意工坊");

     //设置背景图片
     QLabel *label_Background=new QLabel(this);
     label_Background->setGeometry(0,0,1200,1300);
     label_Background->setPixmap(QPixmap(":/img/Debug/image/login.png"));
     label_Background->setScaledContents(true);


     // 1.创建 返回 按钮
      QPushButton *pushButton_backMode=new QPushButton(this);

      // 设置按钮位置和大小 (x, y, width, height)
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
  connect(pushButton_backMode, &QPushButton::clicked, [=](){

      this->hide();
      getGlobalModeWindow()->show();
  });


  // 1. 创建视图和场景
  //元素--> 场景 --> 视图 -->窗口
  //创建视图视图
  QGraphicsView *view1 = new QGraphicsView(this);
   // 场景直接传入网格尺寸

  workshopgridscene=new Workshopgridscene(17);


   // 3. 关联场景和视图
  view1->setScene(workshopgridscene);

  // 在创建视图后添加：
  view1->setStyleSheet("QGraphicsView { background: transparent; border: none; }");
  view1->setFrameShape(QFrame::NoFrame);

  // 4. 手动设置视图位置和大小 (x, y, width, height)
  view1->setGeometry(20, 70, 1160, 1160);

}


Workshop::~Workshop()
{
    delete ui;
}
