#include "gamedefine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    static Start *w = nullptr;
//    if (!w) {
//        w = new Start(); // 关键点
//        w->setAttribute(Qt::WA_DeleteOnClose, true);
//    }
//     w->show();

    getGlobalStartWindow()->show();


    return a.exec();
}
