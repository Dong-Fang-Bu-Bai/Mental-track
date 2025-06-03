/********************************************************************************
** Form generated from reading UI file 'Start.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QLabel *Label_Name;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *Btn_Exit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Btn_Register;
    QPushButton *Btn_login;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName(QString::fromUtf8("Start"));
        Start->resize(1024, 1024);
        Start->setLayoutDirection(Qt::LeftToRight);
        Label_Name = new QLabel(Start);
        Label_Name->setObjectName(QString::fromUtf8("Label_Name"));
        Label_Name->setGeometry(QRect(0, 0, 1024, 1024));
        widget = new QWidget(Start);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(260, 830, 481, 61));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Btn_Exit = new QPushButton(widget);
        Btn_Exit->setObjectName(QString::fromUtf8("Btn_Exit"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(19);
        Btn_Exit->setFont(font);
        Btn_Exit->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0,100, 255, 80%); /* \347\272\242\350\211\262\350\203\214\346\231\257\357\274\21480% \351\200\217\346\230\216 */\n"
"    color: Black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"}"));

        gridLayout->addWidget(Btn_Exit, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        Btn_Register = new QPushButton(widget);
        Btn_Register->setObjectName(QString::fromUtf8("Btn_Register"));
        Btn_Register->setFont(font);
        Btn_Register->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0,100, 255, 80%); /* \347\272\242\350\211\262\350\203\214\346\231\257\357\274\21480% \351\200\217\346\230\216 */\n"
"    color: Black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"}"));

        gridLayout->addWidget(Btn_Register, 0, 2, 1, 1);

        Btn_login = new QPushButton(widget);
        Btn_login->setObjectName(QString::fromUtf8("Btn_login"));
        Btn_login->setFont(font);
        Btn_login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(0,100, 255, 80%); /* \347\272\242\350\211\262\350\203\214\346\231\257\357\274\21480% \351\200\217\346\230\216 */\n"
"    color: Black; /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"}"));

        gridLayout->addWidget(Btn_login, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


        retranslateUi(Start);

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QWidget *Start)
    {
        Start->setWindowTitle(QCoreApplication::translate("Start", "Form", nullptr));
        Label_Name->setText(QCoreApplication::translate("Start", "TextLabel", nullptr));
        Btn_Exit->setText(QCoreApplication::translate("Start", "\351\200\200\345\207\272", nullptr));
        Btn_Register->setText(QCoreApplication::translate("Start", "\346\263\250\345\206\214", nullptr));
        Btn_login->setText(QCoreApplication::translate("Start", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
