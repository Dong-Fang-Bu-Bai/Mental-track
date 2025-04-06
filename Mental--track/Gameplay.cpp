#include "Gameplay.h"
#include "ui_Gameplay.h"
#include"Gridscene.h"
#include"Displaygridscene.h"
#include"Interactivegridscene.h"
#include"Pathcalculator.h"
#include<QGraphicsView>


Gameplay::Gameplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gameplay)
{
    ui->setupUi(this);

    this->setWindowTitle("游戏界面");
    this->setFixedSize(2400,1200);

//    ui->Label_loginbackground->setPixmap(QPixmap(":/img/Debug/image/login.png"));
//    ui->Label_loginbackground->setScaledContents(true);  // 关键：启用自动缩放

    //可选：禁用布局自动调整
    this->setLayout(nullptr); // 确保没有布局管理器干扰

    // 生成路径、导入路径
    //QVector<QPoint> actualPath, opponentPath, relativePath;
    //Pathcalculator::generateRandomPaths(25, actualPath, opponentPath, relativePath);
        QVector<QPoint> manualActualPath = {...}; // 填入己方路径
        QVector<QPoint> manualOpponentPath = {...}; // 填入对方路径
        QVector<QPoint> manualRelativePath;

    if(Pathcalculator::setPaths(manualActualPath, manualOpponentPath,
                              manualRelativePath, 25))
    {
        // 1. 创建视图和场景
        //元素--> 场景 --> 视图 -->窗口
        QGraphicsView *view1 = new QGraphicsView(this); //视图
        DisplayGridScene *displayScene = new DisplayGridScene(25); // 场景  直接传入网格尺寸
        QGraphicsView *view2 = new QGraphicsView(this); //视图

        // 场景直接传入网格尺寸
        InteractiveGridScene *interactiveScene = new InteractiveGridScene(25);

        //2. 设置场景尺寸（单位：像素）
         displayScene->setSceneRect(0, 0, 25 * 30, 25 * 30); // 假设每个格子30x30像素
         interactiveScene->setSceneRect(0, 0, 25 * 30, 25 * 30); // 假设每个格子30x30像素

         // 设置显示场景、交互场景
         displayScene->setPaths(manualActualPath, manualRelativePath);
         interactiveScene->setStartEnd(manualOpponentPath.first(), manualOpponentPath.last());
        // 3. 关联场景和视图
        view1->setScene(displayScene);
        view2->setScene(interactiveScene);

        // 4. 手动设置视图位置和大小 (x, y, width, height)
        view1->setGeometry(20, 20, 1160, 1160);
        view2->setGeometry(1220, 20, 1160, 1160);
    }


//    // 置顶显示
//    view->raise();



}

Gameplay::~Gameplay()
{
    delete ui;
}
