#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include"Hexagonbutton.h"
#include"User.h"
#include"Gameplay.h"
#include<QPointer>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(User&,QWidget *parent = nullptr);
    ~Map();

   HexagonButton* getButton(int index)
   {
        return m_buttons.value(index); // QVector版

   }

   void setupLevelButtons();

public slots:
    void refreshUserData();

//private slots:
//    void handleLevelCompleted(int levelId);

private:
    Ui::Map *ui;
    User *m_currentUser;// 改为指针
    QVector<HexagonButton*> m_buttons; // 通过vector按创建顺序存储按钮
    QPointer<Gameplay> m_currentGameplay; // 自动置空当窗口被删除时

};

#endif // MAP_H
