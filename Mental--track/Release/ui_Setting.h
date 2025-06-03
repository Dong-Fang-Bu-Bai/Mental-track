/********************************************************************************
** Form generated from reading UI file 'Setting.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QPushButton *pushButton_Back;
    QPushButton *pushButton_Change;
    QPushButton *pushButton_Delete;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QString::fromUtf8("Setting"));
        Setting->resize(1200, 1200);
        pushButton_Back = new QPushButton(Setting);
        pushButton_Back->setObjectName(QString::fromUtf8("pushButton_Back"));
        pushButton_Back->setGeometry(QRect(500, 800, 200, 56));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(14);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        font.setKerning(true);
        pushButton_Back->setFont(font);
        pushButton_Back->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));
        pushButton_Change = new QPushButton(Setting);
        pushButton_Change->setObjectName(QString::fromUtf8("pushButton_Change"));
        pushButton_Change->setGeometry(QRect(230, 800, 200, 56));
        pushButton_Change->setFont(font);
        pushButton_Change->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));
        pushButton_Delete = new QPushButton(Setting);
        pushButton_Delete->setObjectName(QString::fromUtf8("pushButton_Delete"));
        pushButton_Delete->setGeometry(QRect(770, 800, 200, 56));
        pushButton_Delete->setFont(font);
        pushButton_Delete->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));

        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QCoreApplication::translate("Setting", "Form", nullptr));
        pushButton_Back->setText(QCoreApplication::translate("Setting", "\350\277\224\345\233\236", nullptr));
        pushButton_Change->setText(QCoreApplication::translate("Setting", "\345\257\206\347\240\201\344\277\256\346\224\271", nullptr));
        pushButton_Delete->setText(QCoreApplication::translate("Setting", "\346\263\250\351\224\200\350\264\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
