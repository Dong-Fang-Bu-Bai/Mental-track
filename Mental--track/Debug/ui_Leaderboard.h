/********************************************************************************
** Form generated from reading UI file 'Leaderboard.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEADERBOARD_H
#define UI_LEADERBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Leaderboard
{
public:
    QTableWidget *tableWidget;
    QPushButton *btnPassedLevels;
    QPushButton *btnBestTimes;
    QPushButton *btnMedals;
    QPushButton *btnWorkshop;
    QPushButton *btnBattle;
    QPushButton *OnlineBattle;

    void setupUi(QWidget *Leaderboard)
    {
        if (Leaderboard->objectName().isEmpty())
            Leaderboard->setObjectName(QString::fromUtf8("Leaderboard"));
        Leaderboard->resize(1200, 1200);
        Leaderboard->setLayoutDirection(Qt::LeftToRight);
        Leaderboard->setAutoFillBackground(false);
        Leaderboard->setStyleSheet(QString::fromUtf8(""));
        tableWidget = new QTableWidget(Leaderboard);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(100, 70, 1000, 1030));
        tableWidget->setAutoFillBackground(false);
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        tableWidget->setLineWidth(1);
        btnPassedLevels = new QPushButton(Leaderboard);
        btnPassedLevels->setObjectName(QString::fromUtf8("btnPassedLevels"));
        btnPassedLevels->setGeometry(QRect(100, 0, 167, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(14);
        btnPassedLevels->setFont(font);
        btnPassedLevels->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4CAF50;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #45a049;\n"
"}"));
        btnBestTimes = new QPushButton(Leaderboard);
        btnBestTimes->setObjectName(QString::fromUtf8("btnBestTimes"));
        btnBestTimes->setGeometry(QRect(267, 0, 167, 70));
        btnBestTimes->setFont(font);
        btnBestTimes->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2196F3;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #0b7dda;\n"
"}"));
        btnMedals = new QPushButton(Leaderboard);
        btnMedals->setObjectName(QString::fromUtf8("btnMedals"));
        btnMedals->setGeometry(QRect(434, 0, 167, 70));
        btnMedals->setFont(font);
        btnMedals->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ff9800;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e68a00;\n"
"}"));
        btnWorkshop = new QPushButton(Leaderboard);
        btnWorkshop->setObjectName(QString::fromUtf8("btnWorkshop"));
        btnWorkshop->setGeometry(QRect(601, 0, 167, 70));
        btnWorkshop->setFont(font);
        btnWorkshop->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ea648e;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e12660;\n"
"}"));
        btnBattle = new QPushButton(Leaderboard);
        btnBattle->setObjectName(QString::fromUtf8("btnBattle"));
        btnBattle->setGeometry(QRect(768, 0, 167, 70));
        btnBattle->setFont(font);
        btnBattle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #ebe624 ;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #dfdb2a ;\n"
"}"));
        OnlineBattle = new QPushButton(Leaderboard);
        OnlineBattle->setObjectName(QString::fromUtf8("OnlineBattle"));
        OnlineBattle->setGeometry(QRect(935, 0, 167, 70));
        OnlineBattle->setFont(font);
        OnlineBattle->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #a549d9 ;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #900fd5 ;\n"
"}"));

        retranslateUi(Leaderboard);

        QMetaObject::connectSlotsByName(Leaderboard);
    } // setupUi

    void retranslateUi(QWidget *Leaderboard)
    {
        Leaderboard->setWindowTitle(QCoreApplication::translate("Leaderboard", "Form", nullptr));
        btnPassedLevels->setText(QCoreApplication::translate("Leaderboard", "\351\200\232\345\205\263\345\205\263\345\215\241\346\225\260", nullptr));
        btnBestTimes->setText(QCoreApplication::translate("Leaderboard", "\345\205\263\345\215\241\346\234\200\344\275\263\346\227\266\351\227\264", nullptr));
        btnMedals->setText(QCoreApplication::translate("Leaderboard", "\345\213\213\347\253\240\350\216\267\345\276\227\346\225\260", nullptr));
        btnWorkshop->setText(QCoreApplication::translate("Leaderboard", "\345\210\233\346\204\217\345\267\245\345\235\212", nullptr));
        btnBattle->setText(QCoreApplication::translate("Leaderboard", "\344\272\272\346\234\272\345\257\271\346\210\230", nullptr));
        OnlineBattle->setText(QCoreApplication::translate("Leaderboard", "\350\260\201\344\270\216\344\272\211\351\224\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Leaderboard: public Ui_Leaderboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEADERBOARD_H
