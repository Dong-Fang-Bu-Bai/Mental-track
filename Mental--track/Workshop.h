#ifndef WORKSHOP_H
#define WORKSHOP_H

#include <QWidget>
#include"User.h"
#include"Workshopgridscene.h"
#include <QInputDialog>

namespace Ui
{
    class Workshop;
}

class Workshop : public QWidget
{
    Q_OBJECT

public:
    explicit Workshop(User&,QWidget *parent = nullptr);
    ~Workshop();

private slots:
    void onConfirmClicked();
    //void onPathCompleted();
    void onErrorOccurred(const QString& message);


private:
    Ui::Workshop *ui;
    User *m_currentUser;// 改为指针
    Workshopgridscene* m_workshopScene;
    bool m_isPlayerPathDone;

};

#endif // WORKSHOP_H
