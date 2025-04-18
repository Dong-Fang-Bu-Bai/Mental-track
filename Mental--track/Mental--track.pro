QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Displaygridscene.cpp \
    Gameplay.cpp \
    Gridscene.cpp \
    Help.cpp \
    Hexagonbutton.cpp \
    Interactivegridscene.cpp \
    LevelRecord.cpp \
    Login.cpp \
    Map.cpp \
    MedalType.cpp \
    Mode.cpp \
    Pathcalculator.cpp \
    Register.cpp \
    Setting.cpp \
    Start.cpp \
    User.cpp \
    UserFileManager.cpp \
    gamedefine.cpp \
    gameobject.cpp \
    main.cpp

HEADERS += \
    Displaygridscene.h \
    Gameplay.h \
    Gridscene.h \
    Help.h \
    Hexagonbutton.h \
    Interactivegridscene.h \
    LevelRecord.h \
    Login.h \
    Map.h \
    MedalType.h \
    Mode.h \
    Pathcalculator.h \
    Register.h \
    Setting.h \
    Start.h \
    User.h \
    UserFileManager.h \
    gamedefine.h \
    gameobject.h

FORMS += \
    Gameplay.ui \
    Help.ui \
    Login.ui \
    Map.ui \
    Mode.ui \
    Register.ui \
    Setting.ui \
    Start.ui \
    Widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
