#ifndef MEDALPOPUP_H
#define MEDALPOPUP_H

#include <QDialog>
#include "MedalType.h"
#include<User.h>

namespace Ui {
class MedalPopup;
}

class MedalPopup : public QDialog
{
    Q_OBJECT

public:
    explicit MedalPopup(MedalType medalType, QWidget *parent = nullptr);
    ~MedalPopup();

    static void checkAndShowUnlockedMedals(class User& user, QWidget *parent);

private slots:
    void onConfirmClicked();

private:
    Ui::MedalPopup *ui;
    MedalType m_medalType;

    void setupUI();
    QString getMedalDescription() const;

    // 新增勋章检测方法
    static bool checkMedalUnlock(const class User& user, MedalType type);
    static std::vector<int> getRequiredLevels(MedalType type);
};

#endif // MEDALPOPUP_H
