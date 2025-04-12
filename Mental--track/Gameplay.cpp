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


Gameplay::Gameplay(const QString& levelPath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gameplay),
    m_levelPath(levelPath)
{
    ui->setupUi(this);

    this->setWindowTitle("游戏界面");
    this->setFixedSize(2400,1300);

    QLabel *Label_loginbackground=new QLabel(this);
    Label_loginbackground->setGeometry(0,0,2400,1300);
    Label_loginbackground->setPixmap(QPixmap(":/img/Debug/image/login.png"));
    Label_loginbackground->setScaledContents(true);  // 关键：启用自动缩放



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

        QPushButton*btn=new QPushButton(this);
        btn->setGeometry(1150,1100,100,50);


        connect(btn,&QPushButton::clicked,[=]()
        {
            if( interactiveScene->verifyUserPath())
            {
                qDebug()<<"成功！"<<endl;
            }
            else
            {
                qDebug()<<"失败！"<<endl;
            }

        });
    }

  }
  else
  {
      QMessageBox::critical(nullptr, "错误", "关卡文件不存在");
  }




//    // 置顶显示
//    view->raise();

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

Gameplay::~Gameplay()
{
    delete ui;
}
