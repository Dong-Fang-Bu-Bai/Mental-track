/********************************************************************************
** Form generated from reading UI file 'Register.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QLabel *label_RegisterBack;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton_play;
    QPushButton *pushButton_help;
    QPushButton *pushButton_back;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QGridLayout *gridLayout1;
    QLabel *label_passconfirm;
    QLabel *label_pass;
    QLineEdit *lineEdit_Pass;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_User;
    QLineEdit *lineEdit_passconfirm;
    QLabel *label_user;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(800, 800);
        label_RegisterBack = new QLabel(Register);
        label_RegisterBack->setObjectName(QString::fromUtf8("label_RegisterBack"));
        label_RegisterBack->setGeometry(QRect(0, 0, 800, 800));
        layoutWidget_2 = new QWidget(Register);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(200, 570, 431, 51));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_play = new QPushButton(layoutWidget_2);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(15);
        pushButton_play->setFont(font);
        pushButton_play->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));

        gridLayout->addWidget(pushButton_play, 0, 0, 1, 1);

        pushButton_help = new QPushButton(layoutWidget_2);
        pushButton_help->setObjectName(QString::fromUtf8("pushButton_help"));
        pushButton_help->setFont(font);
        pushButton_help->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));

        gridLayout->addWidget(pushButton_help, 0, 4, 1, 1);

        pushButton_back = new QPushButton(layoutWidget_2);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setFont(font);
        pushButton_back->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));

        gridLayout->addWidget(pushButton_back, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        widget = new QWidget(Register);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(220, 290, 351, 111));
        gridLayout1 = new QGridLayout(widget);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        gridLayout1->setContentsMargins(0, 0, 0, 0);
        label_passconfirm = new QLabel(widget);
        label_passconfirm->setObjectName(QString::fromUtf8("label_passconfirm"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(13);
        label_passconfirm->setFont(font1);
        label_passconfirm->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}\n"
""));
        label_passconfirm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_passconfirm, 4, 0, 1, 1);

        label_pass = new QLabel(widget);
        label_pass->setObjectName(QString::fromUtf8("label_pass"));
        label_pass->setFont(font1);
        label_pass->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}\n"
""));
        label_pass->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_pass, 2, 0, 1, 1);

        lineEdit_Pass = new QLineEdit(widget);
        lineEdit_Pass->setObjectName(QString::fromUtf8("lineEdit_Pass"));

        gridLayout1->addWidget(lineEdit_Pass, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(verticalSpacer, 1, 0, 1, 1);

        lineEdit_User = new QLineEdit(widget);
        lineEdit_User->setObjectName(QString::fromUtf8("lineEdit_User"));

        gridLayout1->addWidget(lineEdit_User, 0, 1, 1, 1);

        lineEdit_passconfirm = new QLineEdit(widget);
        lineEdit_passconfirm->setObjectName(QString::fromUtf8("lineEdit_passconfirm"));

        gridLayout1->addWidget(lineEdit_passconfirm, 4, 1, 1, 1);

        label_user = new QLabel(widget);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        label_user->setFont(font1);
        label_user->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}\n"
""));
        label_user->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout1->addWidget(label_user, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout1->addItem(verticalSpacer_2, 3, 0, 1, 1);


        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        label_RegisterBack->setText(QCoreApplication::translate("Register", "TextLabel", nullptr));
        pushButton_play->setText(QCoreApplication::translate("Register", "\350\277\233\345\205\245\346\270\270\346\210\217", nullptr));
        pushButton_help->setText(QCoreApplication::translate("Register", "\345\270\256\345\212\251", nullptr));
        pushButton_back->setText(QCoreApplication::translate("Register", "\350\277\224\345\233\236", nullptr));
        label_passconfirm->setText(QCoreApplication::translate("Register", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_pass->setText(QCoreApplication::translate("Register", "\345\257\206\347\240\201", nullptr));
        label_user->setText(QCoreApplication::translate("Register", "\347\224\250\346\210\267\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
