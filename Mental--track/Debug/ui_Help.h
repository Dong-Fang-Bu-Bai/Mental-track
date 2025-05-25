/********************************************************************************
** Form generated from reading UI file 'Help.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Help
{
public:
    QLabel *label_Background;
    QTextEdit *textEdit_Help;
    QPushButton *pushButton_Backstart;

    void setupUi(QWidget *Help)
    {
        if (Help->objectName().isEmpty())
            Help->setObjectName(QString::fromUtf8("Help"));
        Help->resize(1200, 1200);
        label_Background = new QLabel(Help);
        label_Background->setObjectName(QString::fromUtf8("label_Background"));
        label_Background->setGeometry(QRect(0, 0, 1200, 1200));
        textEdit_Help = new QTextEdit(Help);
        textEdit_Help->setObjectName(QString::fromUtf8("textEdit_Help"));
        textEdit_Help->setGeometry(QRect(100, 10, 1000, 1098));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\345\275\251\344\272\221"));
        font.setPointSize(18);
        font.setBold(false);
        font.setUnderline(false);
        font.setWeight(50);
        textEdit_Help->setFont(font);
        pushButton_Backstart = new QPushButton(Help);
        pushButton_Backstart->setObjectName(QString::fromUtf8("pushButton_Backstart"));
        pushButton_Backstart->setGeometry(QRect(500, 1144, 200, 56));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        pushButton_Backstart->setFont(font1);
        pushButton_Backstart->setStyleSheet(QString::fromUtf8("/* \351\273\230\350\256\244\347\212\266\346\200\201 */\n"
"QPushButton {\n"
"    background-color: rgba(255,255, 255, 40%);\n"
"    color: black;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234 */\n"
"QPushButton:hover {\n"
"    background-color:rgba(0,150, 255, 40%)\n"
"}"));

        retranslateUi(Help);

        QMetaObject::connectSlotsByName(Help);
    } // setupUi

    void retranslateUi(QWidget *Help)
    {
        Help->setWindowTitle(QCoreApplication::translate("Help", "Form", nullptr));
        label_Background->setText(QCoreApplication::translate("Help", "TextLabel", nullptr));
        textEdit_Help->setHtml(QCoreApplication::translate("Help", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\345\275\251\344\272\221'; font-size:18pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'\346\245\267\344\275\223'; font-size:15pt; font-weight:600;\"><br /></p></body></html>", nullptr));
        pushButton_Backstart->setText(QCoreApplication::translate("Help", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Help: public Ui_Help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
