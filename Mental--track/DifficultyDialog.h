#ifndef DIFFICULTYDIALOG_H
#define DIFFICULTYDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsEffect>

class BattlePlay;


class DifficultyDialog : public QDialog
{
    Q_OBJECT
public:
 enum Difficulty { Easy = 0, Medium = 1, Hard = 2 };  // 明确指定枚举值

    explicit DifficultyDialog(QWidget *parent = nullptr);

signals:
    void difficultySelected(int difficulty);  // 改为int类型以便更好兼容

private:
    void setupUI();
    QPushButton* createDifficultyButton(const QString& text, int difficulty);
};

#endif // DIFFICULTYDIALOG_H
