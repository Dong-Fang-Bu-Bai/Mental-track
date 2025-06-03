/********************************************************************************
** Form generated from reading UI file 'BattlePlay.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BATTLEPLAY_H
#define UI_BATTLEPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BattlePlay
{
public:

    void setupUi(QWidget *BattlePlay)
    {
        if (BattlePlay->objectName().isEmpty())
            BattlePlay->setObjectName(QString::fromUtf8("BattlePlay"));
        BattlePlay->resize(400, 300);

        retranslateUi(BattlePlay);

        QMetaObject::connectSlotsByName(BattlePlay);
    } // setupUi

    void retranslateUi(QWidget *BattlePlay)
    {
        BattlePlay->setWindowTitle(QCoreApplication::translate("BattlePlay", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BattlePlay: public Ui_BattlePlay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BATTLEPLAY_H
