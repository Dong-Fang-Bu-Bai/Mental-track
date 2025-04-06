/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *Label_loginbackground;
    QCheckBox *checkBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_user;
    QLineEdit *lineEdit_User;
    QLabel *label_pass;
    QLineEdit *lineEdit_Pass;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_play;
    QPushButton *pushButton_help;
    QPushButton *pushButton_back;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(800, 800);
        Label_loginbackground = new QLabel(Login);
        Label_loginbackground->setObjectName(QString::fromUtf8("Label_loginbackground"));
        Label_loginbackground->setGeometry(QRect(0, 0, 800, 800));
        Label_loginbackground->setAutoFillBackground(false);
        checkBox = new QCheckBox(Login);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(574, 335, 111, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(11);
        checkBox->setFont(font);
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(230, 270, 331, 111));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_user = new QLabel(layoutWidget);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(13);
        label_user->setFont(font1);
        label_user->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}\n"
""));
        label_user->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_user, 0, 0, 1, 1);

        lineEdit_User = new QLineEdit(layoutWidget);
        lineEdit_User->setObjectName(QString::fromUtf8("lineEdit_User"));

        gridLayout->addWidget(lineEdit_User, 0, 1, 1, 1);

        label_pass = new QLabel(layoutWidget);
        label_pass->setObjectName(QString::fromUtf8("label_pass"));
        label_pass->setFont(font1);
        label_pass->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: black;\n"
"}\n"
""));
        label_pass->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_pass, 1, 0, 1, 1);

        lineEdit_Pass = new QLineEdit(layoutWidget);
        lineEdit_Pass->setObjectName(QString::fromUtf8("lineEdit_Pass"));
        lineEdit_Pass->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_Pass, 1, 1, 1, 1);

        layoutWidget1 = new QWidget(Login);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 510, 431, 51));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_play = new QPushButton(layoutWidget1);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font2.setPointSize(15);
        pushButton_play->setFont(font2);
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

        gridLayout_2->addWidget(pushButton_play, 0, 0, 1, 1);

        pushButton_help = new QPushButton(layoutWidget1);
        pushButton_help->setObjectName(QString::fromUtf8("pushButton_help"));
        pushButton_help->setFont(font2);
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

        gridLayout_2->addWidget(pushButton_help, 0, 4, 1, 1);

        pushButton_back = new QPushButton(layoutWidget1);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        pushButton_back->setFont(font2);
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

        gridLayout_2->addWidget(pushButton_back, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 3, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Form", nullptr));
        Label_loginbackground->setText(QCoreApplication::translate("Login", "TextLabel", nullptr));
        checkBox->setText(QCoreApplication::translate("Login", "\346\230\276\347\244\272", nullptr));
        label_user->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_pass->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        pushButton_play->setText(QCoreApplication::translate("Login", "\350\277\233\345\205\245\346\270\270\346\210\217", nullptr));
        pushButton_help->setText(QCoreApplication::translate("Login", "\345\270\256\345\212\251", nullptr));
        pushButton_back->setText(QCoreApplication::translate("Login", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
