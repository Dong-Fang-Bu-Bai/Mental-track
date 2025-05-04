/********************************************************************************
** Form generated from reading UI file 'Workshop.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSHOP_H
#define UI_WORKSHOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Workshop
{
public:

    void setupUi(QWidget *Workshop)
    {
        if (Workshop->objectName().isEmpty())
            Workshop->setObjectName(QString::fromUtf8("Workshop"));
        Workshop->resize(400, 300);

        retranslateUi(Workshop);

        QMetaObject::connectSlotsByName(Workshop);
    } // setupUi

    void retranslateUi(QWidget *Workshop)
    {
        Workshop->setWindowTitle(QCoreApplication::translate("Workshop", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Workshop: public Ui_Workshop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSHOP_H
