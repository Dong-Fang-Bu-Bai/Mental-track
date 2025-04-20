/********************************************************************************
** Form generated from reading UI file 'Mode.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODE_H
#define UI_MODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mode
{
public:
    QLabel *label_Background;
    QLabel *label_Select;
    QPushButton *pushButton_Mainplay;
    QPushButton *pushButton_CreateWork;
    QPushButton *pushButton_Battle;
    QPushButton *pushButton_Exit;

    void setupUi(QWidget *Mode)
    {
        if (Mode->objectName().isEmpty())
            Mode->setObjectName(QString::fromUtf8("Mode"));
        Mode->resize(1200, 1200);
        label_Background = new QLabel(Mode);
        label_Background->setObjectName(QString::fromUtf8("label_Background"));
        label_Background->setGeometry(QRect(120, 230, 54, 12));
        label_Select = new QLabel(Mode);
        label_Select->setObjectName(QString::fromUtf8("label_Select"));
        label_Select->setGeometry(QRect(190, 60, 820, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(40);
        label_Select->setFont(font);
        label_Select->setLayoutDirection(Qt::LeftToRight);
        label_Select->setTextFormat(Qt::AutoText);
        label_Select->setAlignment(Qt::AlignCenter);
        pushButton_Mainplay = new QPushButton(Mode);
        pushButton_Mainplay->setObjectName(QString::fromUtf8("pushButton_Mainplay"));
        pushButton_Mainplay->setGeometry(QRect(450, 250, 300, 91));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font1.setPointSize(35);
        pushButton_Mainplay->setFont(font1);
        pushButton_Mainplay->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(230,180, 94, 100%)\n"
"}"));
        pushButton_CreateWork = new QPushButton(Mode);
        pushButton_CreateWork->setObjectName(QString::fromUtf8("pushButton_CreateWork"));
        pushButton_CreateWork->setGeometry(QRect(450, 560, 300, 91));
        pushButton_CreateWork->setFont(font1);
        pushButton_CreateWork->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(230,180, 94, 100%)\n"
"}"));
        pushButton_Battle = new QPushButton(Mode);
        pushButton_Battle->setObjectName(QString::fromUtf8("pushButton_Battle"));
        pushButton_Battle->setGeometry(QRect(450, 870, 300, 91));
        pushButton_Battle->setFont(font1);
        pushButton_Battle->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(230,180, 94, 100%)\n"
"}"));
        pushButton_Exit = new QPushButton(Mode);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(450, 1109, 300, 91));
        pushButton_Exit->setFont(font1);
        pushButton_Exit->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(230,180, 94, 100%)\n"
"}"));

        retranslateUi(Mode);

        QMetaObject::connectSlotsByName(Mode);
    } // setupUi

    void retranslateUi(QWidget *Mode)
    {
        Mode->setWindowTitle(QCoreApplication::translate("Mode", "Form", nullptr));
        label_Background->setText(QCoreApplication::translate("Mode", "TextLabel", nullptr));
        label_Select->setText(QCoreApplication::translate("Mode", "\350\257\267\351\200\211\346\213\251\346\270\270\346\210\217\346\250\241\345\274\217\357\274\232", nullptr));
        pushButton_Mainplay->setText(QCoreApplication::translate("Mode", "\344\270\273\347\272\277\345\211\247\346\203\205", nullptr));
        pushButton_CreateWork->setText(QCoreApplication::translate("Mode", "\345\210\233\346\204\217\345\267\245\345\235\212", nullptr));
        pushButton_Battle->setText(QCoreApplication::translate("Mode", "\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
        pushButton_Exit->setText(QCoreApplication::translate("Mode", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mode: public Ui_Mode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODE_H
