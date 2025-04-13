#include "gamedefine.h"
#include "Map.h"
#include "ui_Map.h"
#include <QGridLayout>
#include <cmath>
#include <QFont>
#include <QMessageBox>
#include<QPushButton>

Map::Map(User& user,QWidget *parent) :
    QWidget(parent),ui(new Ui::Map), m_currentUser(&user)// 存储指针
{
    ui->setupUi(this);


    this->setFixedSize(1200,1200);
    this->setWindowTitle("脑力地图--冒险旅程");

    //设置背景图片
    QLabel *label_Background=new QLabel(this);
    label_Background->setGeometry(0,0,1200,1200);
    label_Background->setPixmap(QPixmap(":/img/Debug/image/Mapbackground1.png"));
    label_Background->setScaledContents(true);

    //设置功能按钮

   // 1.创建 返回 按钮
    {
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
        "     background-color: rgba(230,180, 94, 60%);"  // 蓝色背景，80% 透明
        "   color: Black;"               // 文字颜色
        "   border-radius: 10px;"        // 圆角
        "   padding: 5px;"               // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(230,180, 94, 70%);"  // 悬浮状态背景色
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(230,180, 94, 80%);"  // 点击状态背景色
        "}"
    );

 // 连接带编号的信号槽
connect(pushButton_backMode, &QPushButton::clicked, [=](){

    this->hide();
    getGlobalModeWindow()->show();
});





   // 2.创建 设置 按钮

   QPushButton *pushButton_Setting=new QPushButton(this);

   // 设置按钮位置和大小 (x, y, width, height)
   pushButton_Setting->setGeometry(20, 1130, 200, 60);
   pushButton_Setting->setText("设置");

   // 设置文字字体和大小
   pushButton_Setting->setFont(font);

   // 设置样式表（包含正常/悬浮/点击状态）
   pushButton_Setting->setStyleSheet(
       "QPushButton {"
       "     background-color: rgba(230,180, 94, 60%);"  // 蓝色背景，80% 透明
       "   color: Black;"               // 文字颜色
       "   border-radius: 10px;"        // 圆角
       "   padding: 5px;"               // 内边距
       "}"
       "QPushButton:hover {"
       "   background-color: rgba(230,180, 94, 70%);"  // 悬浮状态背景色
       "}"
       "QPushButton:pressed {"
       "   background-color: rgba(230,180, 94, 80%);"  // 点击状态背景色
       "}"
   );

   // 连接带编号的信号槽
   connect(pushButton_Setting, &QPushButton::clicked, [=](){

       this->hide();
       Setting *setting = new Setting(this);  // 关键：传递当前窗口指针
       setting->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);  // 强制设为对话框
       setting->setAttribute(Qt::WA_DeleteOnClose, true);
       this->hide();
       setting->show();

   });




   // 3.创建 帮助 按钮

  QPushButton *pushButton_Help=new QPushButton(this);

  // 设置按钮位置和大小 (x, y, width, height)
  pushButton_Help->setGeometry(980, 1130, 200, 60);
  pushButton_Help->setText("帮助");

  // 设置文字字体和大小
  pushButton_Help->setFont(font);

  // 设置样式表（包含正常/悬浮/点击状态）
  pushButton_Help->setStyleSheet(
      "QPushButton {"
      "     background-color: rgba(230,180, 94, 60%);"  // 蓝色背景，80% 透明
      "   color: Black;"               // 文字颜色
      "   border-radius: 10px;"        // 圆角
      "   padding: 5px;"               // 内边距
      "}"
      "QPushButton:hover {"
      "   background-color: rgba(230,180, 94, 70%);"  // 悬浮状态背景色
      "}"
      "QPushButton:pressed {"
      "   background-color: rgba(230,180, 94, 80%);"  // 点击状态背景色
      "}"
  );

  // 连接带编号的信号槽
  connect(pushButton_Help, &QPushButton::clicked, [=](){

      Help *help = new Help(this);  // 关键：传递当前窗口指针
      help->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);  // 强制设为对话框
      help->setAttribute(Qt::WA_DeleteOnClose, true);
      this->hide();
      help->show();

  });




   // 4.创建文字标签


  QLabel *label_text=new QLabel(this);

  // 设置标签位置和大小 (x, y, width, height)
  label_text->setGeometry(1043, 187, 60, 500);

  // 将字符串逐字拆分并用换行符连接
  QString verticalText = "冒険の旅路";
  verticalText.replace("", "\n");  // 每个字符后加换行符

  label_text->setText(verticalText);
  label_text->setAlignment(Qt::AlignTop);  // 顶部对齐

  // 设置文字字体和大小
  label_text->setFont(font);

  // 设置样式表（包含正常/悬浮/点击状态）
  label_text->setStyleSheet
  (
      "QPushButton {"
      "     background-color: rgba(255,255, 255, 0%);"  // 蓝色背景，80% 透明
      "   color: Black;"               // 文字颜色

      "}"

  );

   }




    //创建地图
{
    // 六边形参数（匹配按钮大小）
       const int hexRadius = 57; // 半径（直径=100，匹配按钮大小）
       const qreal hexWidth = hexRadius * sqrt(3); // 水平间距 = 半径 * √3
       const qreal hexHeight = hexRadius * 1.5;    // 垂直间距 = 半径 * 1.5

       // 蜂巢中心坐标(以窗口中心为参考)
       const int centerX = width() / 2;
       const int centerY = height() / 2;

       // 蜂巢层数（从中心向外）
       const int layers = 4;
       int buttonIndex = 0;

       // 创建蜂巢网格
       for (int layer = 0; layer <= layers; ++layer)
       {
           // 创建中心六边形
           if (layer == 0)
           {
               HexagonButton *btn = new HexagonButton(this);
               btn->setIcon(QIcon(":/img/Debug/image/Diamond.fw.png"));
               btn->move(centerX - hexRadius, centerY - hexRadius);
               // 存储到容器
               m_buttons.append(btn);
               btn->setText(QString::number(buttonIndex++));
               continue;
           }

           // 创建当前层的六边形
           // 六个方向：从右上开始顺时针
           for (int direction = 0; direction < 6; ++direction)
           {
               // 计算当前方向的起始位置
               qreal angle = M_PI / 3 * direction - M_PI / 6; // 偏移30度
               int startX = centerX + layer * hexWidth * cos(angle);
               int startY = centerY + layer * hexHeight * sin(angle);

               // 沿当前方向创建layer个六边形
               for (int step = 1; step <= layer; ++step)
               {
                   // 计算垂直方向（与当前方向垂直）
                   qreal perpAngle = angle + M_PI / 2;
                   int x = startX + step * hexWidth * cos(perpAngle);
                   int y = startY + step * hexHeight * sin(perpAngle);

                   // 调整到六边形左上角
                   x -= hexRadius;
                   y -= hexRadius;

                   // 创建按钮
                   HexagonButton *btn = new HexagonButton(this);
                   btn->move(x, y);
                   // 存储到容器
                   m_buttons.append(btn);
                   btn->setText(QString::number(buttonIndex++));
               }
           }
       }

}

    // 设置特定按钮属性（图标、点击逻辑）

    setupLevelButtons();

}

void Map::setupLevelButtons()
{


   //设置图标
   for(int i=1;i<5;i++)
    {
      for(int j=0;j<i;j++)
        {
         if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j))
           {
             getButton(3*i*i-3*i+1+j)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
           }
          else
           {
             getButton(3*i*i-3*i+1+j)->setIcon(QIcon(":/img/Debug/image/flame_lock.fw.png"));
           }
        }
    }

     for(int i=1;i<5;i++)
      {
         for(int j=0;j<i;j++)
         {
             if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j+i))
             {
                getButton(3*i*i-3*i+1+j+i)->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
             }
             else
             {
               getButton(3*i*i-3*i+1+j+i)->setIcon(QIcon(":/img/Debug/image/lightning_lock.fw.png"));
             }
         }
      }


      for(int i=1;i<5;i++)
      {
        for(int j=0;j<i;j++)
         {
            if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j+2*i))
            {
               getButton(3*i*i-3*i+1+j+2*i)->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
            }
            else
            {
              getButton(3*i*i-3*i+1+j+2*i)->setIcon(QIcon(":/img/Debug/image/shadow_lock.fw.png"));
            }


         }
      }



      for(int i=1;i<5;i++)
      {
        for(int j=0;j<i;j++)
         {

          if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j+3*i))
          {
             getButton(3*i*i-3*i+1+j+3*i)->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
          }
            else
          {
             getButton(3*i*i-3*i+1+j+3*i)->setIcon(QIcon(":/img/Debug/image/ice_lock.fw.png"));
          }

          }
      }



     for(int i=1;i<5;i++)
     {
      for(int j=0;j<i;j++)
       {
          if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j+4*i))
          {
              getButton(3*i*i-3*i+1+j+4*i)->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
          }
          else
          {
              getButton(3*i*i-3*i+1+j+4*i)->setIcon(QIcon(":/img/Debug/image/nature_lock.fw.png"));
          }
       }
     }



     for(int i=1;i<5;i++)
     {
       for(int j=0;j<i;j++)
        {
           if(m_currentUser->isLevelPassed(3*i*i-3*i+1+j+5*i))
           {
              getButton(3*i*i-3*i+1+j+5*i)->setIcon(QIcon(":/img/Debug/image/devine.fw.png"));
           }
           else
           {
              getButton(3*i*i-3*i+1+j+5*i)->setIcon(QIcon(":/img/Debug/image/devine_lock.fw.png"));
           }
        }
     }


     // 为不同按钮指定不同关卡

     //设置映射表
     QMap<int, QString> levelMap = {
         {0, ":/leveldata/Debug/levels/level1/level1.txt"},
         {1, ":/leveldata/Debug/levels/level1/level1.txt"},
         {2, ":/leveldata/Debug/levels/level1/level1.txt"},
         {3, ":/leveldata/Debug/levels/level1/level1.txt"},
         {4, ":/leveldata/Debug/levels/level1/level1.txt"},
         {5, ":/leveldata/Debug/levels/level1/level1.txt"},
         {6, ":/leveldata/Debug/levels/level1/level1.txt"},
         {7, ":/leveldata/Debug/levels/level1/level1.txt"},
         {8, ":/leveldata/Debug/levels/level1/level1.txt"},
         {9, ":/leveldata/Debug/levels/level1/level1.txt"},
         {10, ":/leveldata/Debug/levels/level1/level1.txt"},
         {11, ":/leveldata/Debug/levels/level1/level1.txt"},
         {12, ":/leveldata/Debug/levels/level1/level1.txt"},
         {13, ":/leveldata/Debug/levels/level1/level1.txt"},
         {14, ":/leveldata/Debug/levels/level1/level1.txt"},
         {15, ":/leveldata/Debug/levels/level1/level1.txt"},
         {16, ":/leveldata/Debug/levels/level1/level1.txt"},
         {17, ":/leveldata/Debug/levels/level1/level1.txt"},
         {18, ":/leveldata/Debug/levels/level1/level1.txt"},
         {19, ":/leveldata/Debug/levels/level1/level1.txt"},
         {20, ":/leveldata/Debug/levels/level1/level1.txt"},
         {21, ":/leveldata/Debug/levels/level1/level1.txt"},
         {22, ":/leveldata/Debug/levels/level1/level1.txt"},
         {23, ":/leveldata/Debug/levels/level1/level1.txt"},
         {24, ":/leveldata/Debug/levels/level1/level1.txt"},
         {25, ":/leveldata/Debug/levels/level1/level1.txt"},
         {26, ":/leveldata/Debug/levels/level1/level1.txt"},
         {27, ":/leveldata/Debug/levels/level1/level1.txt"},
         {28, ":/leveldata/Debug/levels/level1/level1.txt"},
         {29, ":/leveldata/Debug/levels/level1/level1.txt"},
         {30, ":/leveldata/Debug/levels/level1/level1.txt"},
         {31, ":/leveldata/Debug/levels/level1/level1.txt"},
         {32, ":/leveldata/Debug/levels/level1/level1.txt"},
         {33, ":/leveldata/Debug/levels/level1/level1.txt"},
         {34, ":/leveldata/Debug/levels/level1/level1.txt"},
         {35, ":/leveldata/Debug/levels/level1/level1.txt"},
         {36, ":/leveldata/Debug/levels/level1/level1.txt"},
         {37, ":/leveldata/Debug/levels/level1/level1.txt"},
         {38, ":/leveldata/Debug/levels/level1/level1.txt"},
         {39, ":/leveldata/Debug/levels/level1/level1.txt"},
         {40, ":/leveldata/Debug/levels/level1/level1.txt"},
         {41, ":/leveldata/Debug/levels/level1/level1.txt"},
         {42, ":/leveldata/Debug/levels/level1/level1.txt"},
         {43, ":/leveldata/Debug/levels/level1/level1.txt"},
         {44, ":/leveldata/Debug/levels/level1/level1.txt"},
         {45, ":/leveldata/Debug/levels/level1/level1.txt"},
         {46, ":/leveldata/Debug/levels/level1/level1.txt"},
         {47, ":/leveldata/Debug/levels/level1/level1.txt"},
         {48, ":/leveldata/Debug/levels/level1/level1.txt"},
         {49, ":/leveldata/Debug/levels/level1/level1.txt"},
         {50, ":/leveldata/Debug/levels/level1/level1.txt"},
         {51, ":/leveldata/Debug/levels/level1/level1.txt"},
         {52, ":/leveldata/Debug/levels/level1/level1.txt"},
         {53, ":/leveldata/Debug/levels/level1/level1.txt"},
         {54, ":/leveldata/Debug/levels/level1/level1.txt"},
         {55, ":/leveldata/Debug/levels/level1/level1.txt"},
         {56, ":/leveldata/Debug/levels/level1/level1.txt"},
         {57, ":/leveldata/Debug/levels/level1/level1.txt"},
         {58, ":/leveldata/Debug/levels/level1/level1.txt"},
         {59, ":/leveldata/Debug/levels/level1/level1.txt"},
         {60, ":/leveldata/Debug/levels/level1/level1.txt"},


     };


     //设置点击逻辑

     //连接带编号的信号槽
     for(int i=0;i<61;i++)
     {
         connect(m_buttons[i], &HexagonButton::clicked, [=]()
         {
             if(levelMap.contains(i))
             {
                 // 如果已有窗口则先关闭
                 if(m_currentGameplay)
                 {
                     m_currentGameplay->close();
                 }

                 m_currentGameplay = new Gameplay(levelMap[i], i, m_currentUser);
                 m_currentGameplay->setAttribute(Qt::WA_DeleteOnClose, true);

//                 // 关键修改1：设置为独立窗口
//                 m_currentGameplay->setWindowFlags(Qt::Window);

//                // 关键修改2：断开与父窗口的隐藏关联
//                m_currentGameplay->setParent(nullptr, Qt::Window);


                // 修改这里：直接连接信号到Map的显示函数
                 connect(m_currentGameplay, &Gameplay::returnToMapRequested, this, [this]()
                 {
                    this->refreshUserData();
                    this->show();
                    this->activateWindow(); // 确保窗口获得焦点
                    });

                 this->hide();
                 m_currentGameplay->show();
             }
             else
             {
                 QMessageBox::critical(nullptr, "错误", "未找到映射！");
             }
         });
     }
 }



void Map::refreshUserData()
{
    // 不再需要reloadCurrentUser，因为m_currentUser是指针，外部修改会直接反映
    setupLevelButtons(); // 这会根据最新用户数据更新所有按钮图标
}


Map::~Map()
{
    delete ui;
}
