#include "Widget.h"
#include "ui_Widget.h"

//图形元素 -->  场景 --> 视图 --> 窗口
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(2000,1200);
}

Widget::~Widget()
{
    delete ui;
}

