#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QVector>
#include <QPair>
#include <QString>
#include<QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include "AudioManager.h"
#include "User.h"
#include "UserFileManager.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr, User* currentUser = nullptr);
    ~Setting();

private slots:
    void on_pushButton_Back_clicked();
    void onMusicVolumeChanged(int value);    // 音乐音量滑动条槽函数
    void onEffectVolumeChanged(int value);   // 音效音量滑动条槽函数

    void on_pushButton_Change_clicked();

    void on_pushButton_Delete_clicked();

private:
    Ui::Setting *ui;
    User* m_currentUser;

    // 背景音乐列表和当前索引
      QVector<QPair<QString, QString>> m_backgroundMusics;
      int m_currentMusicIndex;
    // 当前音乐名称显示标签
      QLabel *m_currentMusicLabel;

      // 更新当前音乐显示
      void updateCurrentMusicLabel();
      int findCurrentMusicIndex() const;

      bool changePassword();
      bool deleteAccount();
      void updateUserData(bool deleteUser = false);
};

#endif // SETTING_H
