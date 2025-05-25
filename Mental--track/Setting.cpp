#include "gamedefine.h"
#include "Setting.h"
#include "ui_Setting.h"
#include <QSlider>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QApplication>

Setting::Setting(QWidget *parent, User* currentUser) :
    QWidget(parent),
    ui(new Ui::Setting),
    m_currentUser(currentUser)
{
    ui->setupUi(this);

    // 背景音乐列表
        m_backgroundMusics =
        {
            {"qrc:/audio/Debug/music/music_DeepTheme_Audio_Spring_Hazes_34.mp3", "Spring Hazes"},
            {"qrc:/audio/Debug/music/Happyday.mp3", "Happy day"},
            {"qrc:/audio/Debug/music/Mushroom.mp3", "Mushroom"},
            {"qrc:/audio/Debug/music/Running.mp3", "Running!"}
        };

        // 获取当前播放的音乐索引
         m_currentMusicIndex = findCurrentMusicIndex();


    QLabel*label_Background=new QLabel(this);
    label_Background->setGeometry(0,0,1200,1200);
    label_Background->setPixmap(QPixmap(":/img/Debug/image/Modebackground.fw.png"));
    label_Background->setScaledContents(true);  // 关键：启用自动缩放

    ui->pushButton_Back->raise();
    ui->pushButton_Change->raise();
    ui->pushButton_Delete->raise();

    // ================= 背景音乐控制 =================
        // 音乐标签
        QLabel *musicLabel = new QLabel("背景音量:", this);
        musicLabel->setGeometry(300, 300, 150, 40); // x, y, width, height
        musicLabel->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
        musicLabel->setStyleSheet("color: #333333;");

        // 音乐滑动条
        QSlider *musicSlider = new QSlider(Qt::Horizontal, this);
        musicSlider->setGeometry(450, 300, 400, 40);
        musicSlider->setRange(0, 100);
        musicSlider->setValue(static_cast<int>(AudioManager::instance()->musicVolume() * 100));
        musicSlider->setStyleSheet
        (
            "QSlider::groove:horizontal {"
            "    height: 10px;"
            "    background: #e0e0e0;"
            "    border-radius: 5px;"
            "}"
            "QSlider::sub-page:horizontal {"
            "    background: #4CAF50;"
            "    border-radius: 5px;"
            "}"
            "QSlider::handle:horizontal {"
            "    width: 20px;"
            "    height: 20px;"
            "    margin: -5px 0;"
            "    background: white;"
            "    border: 2px solid #4CAF50;"
            "    border-radius: 10px;"
            "}"
        );

        // 音乐数值显示
        QLabel *musicValueLabel = new QLabel(QString::number(musicSlider->value()), this);
        musicValueLabel->setGeometry(870, 300, 50, 40);
        musicValueLabel->setFont(QFont("Microsoft YaHei", 14));
        musicValueLabel->setStyleSheet("color: #666666;");
        musicValueLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // ================= 音乐切换控制 =================
            // 当前音乐名称显示
            m_currentMusicLabel = new QLabel(this);
            m_currentMusicLabel->setGeometry(300, 350, 400, 40);
            m_currentMusicLabel->setFont(QFont("Microsoft YaHei", 14));
            m_currentMusicLabel->setStyleSheet("color: #333333;");
            updateCurrentMusicLabel();

            // 上一首按钮
            QPushButton *prevButton = new QPushButton("◀", this);
            prevButton->setGeometry(450, 400, 60, 40);
            prevButton->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
            prevButton->setStyleSheet(
                "QPushButton {"
                "    background-color: #4CAF50;"
                "    color: white;"
                "    border-radius: 5px;"
                "}"
                "QPushButton:hover {"
                "    background-color: #3e8e41;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #2d6a2f;"
                "}"
            );


            // 下一首按钮
            QPushButton *nextButton = new QPushButton("▶", this);
            nextButton->setGeometry(520, 400, 60, 40);
            nextButton->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
            nextButton->setStyleSheet(prevButton->styleSheet());

        // ================= 音效控制 =================
        // 音效标签
        QLabel *effectLabel = new QLabel("点击音量:", this);
        effectLabel->setGeometry(300, 500, 150, 40);
        effectLabel->setFont(QFont("Microsoft YaHei", 16, QFont::Bold));
        effectLabel->setStyleSheet("color: #333333;");

        // 音效滑动条
        QSlider *effectSlider = new QSlider(Qt::Horizontal, this);
        effectSlider->setGeometry(450, 500, 400, 40);
        effectSlider->setRange(0, 100);
        effectSlider->setValue(static_cast<int>(AudioManager::instance()->effectsVolume() * 100));
        effectSlider->setStyleSheet(
            "QSlider::groove:horizontal {"
            "    height: 10px;"
            "    background: #e0e0e0;"
            "    border-radius: 5px;"
            "}"
            "QSlider::sub-page:horizontal {"
            "    background: #2196F3;"
            "    border-radius: 5px;"
            "}"
            "QSlider::handle:horizontal {"
            "    width: 20px;"
            "    height: 20px;"
            "    margin: -5px 0;"
            "    background: white;"
            "    border: 2px solid #2196F3;"
            "    border-radius: 10px;"
            "}"
        );

        // 音效数值显示
        QLabel *effectValueLabel = new QLabel(QString::number(effectSlider->value()), this);
        effectValueLabel->setGeometry(870, 500, 50, 40);
        effectValueLabel->setFont(QFont("Microsoft YaHei", 14));
        effectValueLabel->setStyleSheet("color: #666666;");
        effectValueLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        // ================= 测试按钮 =================
            QPushButton *testButton = new QPushButton("测试音效", this);
            testButton->setGeometry(450, 600, 200, 60);
            testButton->setFont(QFont("Microsoft YaHei", 14, QFont::Bold));
            testButton->setStyleSheet(
                "QPushButton {"
                "    background-color: #2196F3;"
                "    color: white;"
                "    border-radius: 10px;"
                "    padding: 10px;"
                "}"
                "QPushButton:hover {"
                "    background-color: #0b7dda;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #0a68ba;"
                "}"
            );

        // ================= 连接信号槽 =================

        connect(musicSlider, &QSlider::valueChanged, this, &Setting::onMusicVolumeChanged);

        connect(effectSlider, &QSlider::valueChanged, this, &Setting::onEffectVolumeChanged);

        connect(musicSlider, &QSlider::valueChanged, [musicValueLabel](int value){
            musicValueLabel->setText(QString::number(value));
        });

        connect(effectSlider, &QSlider::valueChanged, [effectValueLabel](int value){
            effectValueLabel->setText(QString::number(value));
        });

        connect(testButton, &QPushButton::clicked, [=](){
               AudioManager::instance()->playEffect(); // 使用当前设置的音效音量播放
           });

        connect(prevButton, &QPushButton::clicked, [=](){
              m_currentMusicIndex = (m_currentMusicIndex - 1 + m_backgroundMusics.size()) % m_backgroundMusics.size();
              updateCurrentMusicLabel();
              AudioManager::instance()->playMusic(m_backgroundMusics[m_currentMusicIndex].first, true);
          });

          connect(nextButton, &QPushButton::clicked, [=](){
              m_currentMusicIndex = (m_currentMusicIndex + 1) % m_backgroundMusics.size();
              updateCurrentMusicLabel();
              AudioManager::instance()->playMusic(m_backgroundMusics[m_currentMusicIndex].first, true);
          });
}

Setting::~Setting()
{
    delete ui;
}

int Setting::findCurrentMusicIndex() const
{
    QString currentPath = AudioManager::instance()->currentMusicPath();
    for(int i = 0; i < m_backgroundMusics.size(); ++i) {
        if(m_backgroundMusics[i].first == currentPath) {
            return i;
        }
    }
    return 0; // 默认返回第一个
}


void Setting::updateCurrentMusicLabel()
{
    m_currentMusicLabel->setText("当前音乐: " + m_backgroundMusics[m_currentMusicIndex].second);
}

void Setting::on_pushButton_Back_clicked()
{
    AudioManager::instance()->playEffect();
    this->parentWidget()->show();  // 显示来源窗口
    this->close();                 // 关闭帮助窗口
}


void Setting::onMusicVolumeChanged(int value)
{
    // 将滑动条的0-100转换为0.0-1.0
    float volume = value / 100.0f;
    AudioManager::instance()->setMusicVolume(volume);
}

void Setting::onEffectVolumeChanged(int value)
{
    float volume = value / 100.0f;
    AudioManager::instance()->setEffectsVolume(volume);
}

void Setting::on_pushButton_Change_clicked()
{
    if (changePassword())
    {
           QMessageBox::information(this, "成功", "密码修改成功！");
    }
}

void Setting::on_pushButton_Delete_clicked()
{
    if (deleteAccount())
    {
      QMessageBox::information(this, "注销成功", "账户已注销，即将退出游戏");
      QApplication::quit(); // 退出游戏
   }
}

bool Setting::changePassword()
{
    bool ok;
    QString currentPassword = QInputDialog::getText(this, "修改密码",
                                                  "请输入当前密码:",
                                                  QLineEdit::Password, "", &ok);

    if (!ok) return false; // 用户取消

    // 验证当前密码
    if (!m_currentUser->verifyPassword(currentPassword.toStdString())) {
        QMessageBox::warning(this, "错误", "当前密码不正确！");
        return false;
    }

    // 获取新密码
    QString newPassword1 = QInputDialog::getText(this, "修改密码",
                                               "新密码:",
                                               QLineEdit::Password, "", &ok);
    if (!ok) return false;

    QString newPassword2 = QInputDialog::getText(this, "修改密码",
                                               "再次输入新密码:",
                                               QLineEdit::Password, "", &ok);
    if (!ok) return false;

    // 验证两次输入一致
    if (newPassword1 != newPassword2) {
        QMessageBox::warning(this, "错误", "两次输入的密码不一致！");
        return false;
    }

    // 验证新密码有效性
    if (newPassword1.isEmpty()) {
        QMessageBox::warning(this, "错误", "密码不能为空！");
        return false;
    }

    // 修改密码
    *m_currentUser = *User::createNewUser(m_currentUser->getUsername(),
                                        newPassword1.toStdString(),
                                        61); // 假设总关卡数为61

    updateUserData();
    return true;
}

bool Setting::deleteAccount()
{
    // 二次确认
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "注销账户",
                                "确定要注销账户吗？此操作不可撤销！",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes) {
        return false;
    }

    // 验证密码
    bool ok;
    QString currentPassword = QInputDialog::getText(this, "注销账户",
                                                  "请输入当前密码确认:",
                                                  QLineEdit::Password, "", &ok);

    if (!ok) return false; // 用户取消

    // 验证当前密码
    if (!m_currentUser->verifyPassword(currentPassword.toStdString())) {
        QMessageBox::warning(this, "错误", "密码不正确！");
        return false;
    }

    updateUserData(true); // 删除用户
    return true;
}

void Setting::updateUserData(bool deleteUser)
{
    // 加载所有用户
    std::vector<User> users;
    UserFileManager::loadUsers(users, "users.dat");

    // 更新或删除当前用户
    bool found = false;
    for (auto it = users.begin(); it != users.end(); ) {
        if (it->getUsername() == m_currentUser->getUsername()) {
            if (!deleteUser) {
                *it = *m_currentUser; // 更新用户
            } else {
                it = users.erase(it); // 注销账户
                continue;
            }
            found = true;
        }
        ++it;
    }

    if (!found && !deleteUser) {
        users.push_back(*m_currentUser);
    }

    // 保存用户数据
    UserFileManager::saveUsers(users, "users.dat");
    UserFileManager manager;
    manager.generateDeveloperReport("users.dat", "users_info.txt");
}
