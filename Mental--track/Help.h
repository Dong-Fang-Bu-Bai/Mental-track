#ifndef HELP_H
#define HELP_H

#include <QWidget>


namespace Ui {
class Help;
}

class Help : public QWidget
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

private slots:
    void on_pushButton_Backstart_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H
