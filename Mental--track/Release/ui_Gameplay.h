/********************************************************************************
** Form generated from reading UI file 'Gameplay.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPLAY_H
#define UI_GAMEPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gameplay
{
public:

    void setupUi(QWidget *Gameplay)
    {
        if (Gameplay->objectName().isEmpty())
            Gameplay->setObjectName(QString::fromUtf8("Gameplay"));
        Gameplay->resize(400, 300);

        retranslateUi(Gameplay);

        QMetaObject::connectSlotsByName(Gameplay);
    } // setupUi

    void retranslateUi(QWidget *Gameplay)
    {
        Gameplay->setWindowTitle(QCoreApplication::translate("Gameplay", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gameplay: public Ui_Gameplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPLAY_H
