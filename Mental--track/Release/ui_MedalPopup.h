/********************************************************************************
** Form generated from reading UI file 'MedalPopup.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDALPOPUP_H
#define UI_MEDALPOPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedalPopup
{
public:

    void setupUi(QWidget *MedalPopup)
    {
        if (MedalPopup->objectName().isEmpty())
            MedalPopup->setObjectName(QString::fromUtf8("MedalPopup"));
        MedalPopup->resize(400, 300);

        retranslateUi(MedalPopup);

        QMetaObject::connectSlotsByName(MedalPopup);
    } // setupUi

    void retranslateUi(QWidget *MedalPopup)
    {
        MedalPopup->setWindowTitle(QCoreApplication::translate("MedalPopup", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedalPopup: public Ui_MedalPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDALPOPUP_H
