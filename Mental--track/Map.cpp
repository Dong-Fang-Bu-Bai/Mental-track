#include "gamedefine.h"
#include "Map.h"
#include "ui_Map.h"
#include <QGridLayout>
#include <cmath>
#include <QFont>
#include <QMessageBox>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
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





  // 创建文字标签
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
  label_text->setStyleSheet(
      "QPushButton {"
      "     background-color: rgba(255,255, 255, 0%);"  // 蓝色背景，80% 透明
      "   color: Black;"               // 文字颜色

      "}"

  );



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
       for (int layer = 0; layer <= layers; ++layer) {
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
           for (int direction = 0; direction < 6; ++direction) {
               // 计算当前方向的起始位置
               qreal angle = M_PI / 3 * direction - M_PI / 6; // 偏移30度
               int startX = centerX + layer * hexWidth * cos(angle);
               int startY = centerY + layer * hexHeight * sin(angle);

               // 沿当前方向创建layer个六边形
               for (int step = 1; step <= layer; ++step) {
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


       // 设置特定按钮属性（图标、点击逻辑）


    //设置图标
       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j);
               btn->setIcon(QIcon(":/img/Debug/image/flame.fw.png"));
           }
       }

       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j+i);
               btn->setIcon(QIcon(":/img/Debug/image/lightning.fw.png"));
           }
       }


       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j+2*i);
               btn->setIcon(QIcon(":/img/Debug/image/shadow.fw.png"));
           }
       }

       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j+3*i);
               btn->setIcon(QIcon(":/img/Debug/image/ice.fw.png"));
           }
       }

       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j+4*i);
               btn->setIcon(QIcon(":/img/Debug/image/nature.fw.png"));
           }
       }

       for(int i=1;i<5;i++)
       {
           for(int j=0;j<i;j++)
           {
               auto btn = getButton(3*i*i-3*i+1+j+5*i);
               btn->setIcon(QIcon(":/img/Debug/image/devine.fw.png"));
           }
       }



       //设置点击逻辑

       //连接带编号的信号槽
         connect(m_buttons[0], &HexagonButton::clicked, [=]()
         {

             Gameplay *gameplay = new Gameplay();  // 关键：传递当前窗口指针
             gameplay->setAttribute(Qt::WA_DeleteOnClose, true);
             this->hide();
             gameplay->show();
         });

//       connect(m_buttons[0], &HexagonButton::clicked, [=]()
//       {
//            qDebug()<<"点击";
//       }
//       );




}

Map::~Map()
{
    delete ui;
}
