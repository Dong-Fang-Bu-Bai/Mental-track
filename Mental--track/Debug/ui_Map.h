/********************************************************************************
** Form generated from reading UI file 'Map.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_H
#define UI_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Map
{
public:

    void setupUi(QWidget *Map)
    {
        if (Map->objectName().isEmpty())
            Map->setObjectName(QString::fromUtf8("Map"));
        Map->resize(1200, 1200);

        retranslateUi(Map);

        QMetaObject::connectSlotsByName(Map);
    } // setupUi

    void retranslateUi(QWidget *Map)
    {
        Map->setWindowTitle(QCoreApplication::translate("Map", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Map: public Ui_Map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_H
