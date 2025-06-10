#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include<QMessageBox>

class CustomDialog : public QDialog {
    Q_OBJECT
public:
    explicit CustomDialog(QWidget *parent = nullptr);

    void setMessage(const QString &message);
    void setInformativeText(const QString &text);
    void addButton(const QString &text, QMessageBox::ButtonRole role);

private:
    QLabel *m_messageLabel;
    QLabel *m_infoLabel;
    QVBoxLayout *m_layout;
    QHBoxLayout *m_buttonLayout;
};
#endif // CUSTOMDIALOG_H
