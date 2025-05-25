#include "gamedefine.h"
#include"AudioManager.h"

#include <QApplication>
#include <QSoundEffect>


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);



    // 初始化音频系统（单例会自动创建）
    AudioManager::instance();

    AudioManager::instance()->playMusic();



    getGlobalStartWindow()->show();



    return a.exec();
}
