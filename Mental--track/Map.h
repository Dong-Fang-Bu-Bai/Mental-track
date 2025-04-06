#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include"Hexagonbutton.h"

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

   HexagonButton* getButton(int index)
   {
        return m_buttons.value(index); // QVector版

   }

private:
    Ui::Map *ui;

    QVector<HexagonButton*> m_buttons; // 通过vector按创建顺序存储按钮
};

#endif // MAP_H
