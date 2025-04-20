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
               btn->setIcon(QIcon(":/img/Debug/image/Diamond_lock.fw.png"));
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
          if((3*i*i-3*i+1+j)==37)
          {
            getButton(37)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
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
             if((3*i*i-3*i+1+j+i)==41)
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
            if((3*i*i-3*i+1+j+2*i)==45)
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
         if((3*i*i-3*i+1+j+3*i)==49)
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
          if((3*i*i-3*i+1+j+4*i)==53)
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
           if((3*i*i-3*i+1+j+5*i)==57)
           {
              getButton(3*i*i-3*i+1+j+5*i)->setIcon(QIcon(":/img/Debug/image/divine.fw.png"));
            }
           else
           {
              getButton(3*i*i-3*i+1+j+5*i)->setIcon(QIcon(":/img/Debug/image/divine_lock.fw.png"));
           }
        }
     }






     //设置点击逻辑
     //连接带编号的信号槽
     for(int i=0;i<61;i++)
     {

         if(i==37||i==41||i==45||i==49||i==53||i==57)
         {
             gamebtn(i);

         }

         if
         (
          ((37<=i&&i<=39)||(41<=i&&i<=43)||(45<=i&&i<=47)||(49<=i&&i<=51)||(53<=i&&i<=55)||(57<=i&&i<=59)||
           (19<=i&&i<=20)||(22<=i&&i<=23)||(25<=i&&i<=26)||(28<=i&&i<=29)||(31<=i&&i<=32)||(34<=i&&i<=35)||
            i==7||i==9||i==11||i==13||i==15||i==17)&&m_currentUser->isLevelPassed(i)
         )
         {
            gamebtn(i+1);
            if((37<=i&&i<=39)||(19<=i&&i<=20)||i==7)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
            }
            else if((41<=i&&i<=43)||(22<=i&&i<=23)||i==9)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
            }
            else if((45<=i&&i<=47)||(25<=i&&i<=26)||i==11)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
            }
            else if((49<=i&&i<=51)||(28<=i&&i<=29)||i==13)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
            }
            else if((53<=i&&i<=55)||(31<=i&&i<=32)||i==15)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
            }
            else if((57<=i&&i<=59)||(34<=i&&i<=35)||i==17)
            {
                getButton(i+1)->setIcon(QIcon(":/img/Debug/image/divine.fw.png"));
            }
         }

         if(i==40&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(19);
            getButton(19)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
         }
         else if(i==44&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(22);
            getButton(22)->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
         }

         if(i==48&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(25);
            getButton(25)->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
         }

         if(i==52&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(28);
            getButton(28)->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
         }

         if(i==56&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(31);
            getButton(31)->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
         }

         if(i==60&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(34);
            getButton(34)->setIcon(QIcon(":/img/Debug/image/divine.fw.png"));
         }

         if(i==21&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(7);
            getButton(7)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
         }

         if(i==24&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(9);
            getButton(9)->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
         }

         if(i==27&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(11);
            getButton(11)->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
         }

         if(i==30&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(13);
            getButton(13)->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
         }

         if(i==33&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(15);
            getButton(15)->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
         }

         if(i==36&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(17);
            getButton(17)->setIcon(QIcon(":/img/Debug/image/divine.fw.png"));
         }

         if(i==8&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(1);
            getButton(1)->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
         }

         if(i==10&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(2);
            getButton(2)->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
         }

         if(i==12&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(3);
            getButton(3)->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
         }

         if(i==14&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(4);
            getButton(4)->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
         }

         if(i==16&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(5);
            getButton(5)->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
         }

         if(i==18&&m_currentUser->isLevelPassed(i))
         {
            gamebtn(6);
            getButton(6)->setIcon(QIcon(":/img/Debug/image/divine.fw.png"));
         }

         if(m_currentUser->isLevelPassed(1)&&m_currentUser->isLevelPassed(2)&&
            m_currentUser->isLevelPassed(3)&&m_currentUser->isLevelPassed(4)&&
           m_currentUser->isLevelPassed(5)&&m_currentUser->isLevelPassed(6))
         {
              gamebtn(0);
              getButton(0)->setIcon(QIcon(":/img/Debug/image/Diamond.fw.png"));
         }
     }
 }

void Map::gamebtn(int i)
{
    // 先断开之前的连接（如果有）
    disconnect(m_buttons[i], &HexagonButton::clicked, nullptr, nullptr);

    connect(m_buttons[i], &HexagonButton::clicked, [=]()
    {
        // 如果已有窗口且未关闭，则直接激活它
        if(m_currentGameplay && !m_currentGameplay.isNull())
        {
            m_currentGameplay->activateWindow();
            return;
        }

        // 检查映射是否存在
          if(!levelMap.contains(i))
          {
              QMessageBox::critical(this, "错误", "未找到关卡映射！");
              return;
          }


            m_currentGameplay = new Gameplay(levelMap[i], i, m_currentUser);
            m_currentGameplay->setAttribute(Qt::WA_DeleteOnClose, true);



           // 直接连接信号到Map的显示函数
            connect(m_currentGameplay, &Gameplay::returnToMapRequested, this, &Map::onGameplayFinished);

            this->hide();
            m_currentGameplay->show();

    });
}

void Map::refreshUserData()
{
    // 不再需要reloadCurrentUser，因为m_currentUser是指针，外部修改会直接反映
    setupLevelButtons(); // 这会根据最新用户数据更新所有按钮图标
}

void Map::onGameplayFinished()
{
    this->refreshUserData();
    this->show();
    this->activateWindow();


}


Map::~Map()
{
    delete ui;
}
