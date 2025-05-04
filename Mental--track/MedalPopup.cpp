#include "MedalPopup.h"
#include "ui_MedalPopup.h"
#include <QPushButton>
#include <QLabel>
#include <algorithm>
#include<UserFileManager.h>

MedalPopup::MedalPopup(MedalType medalType, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedalPopup),
    m_medalType(medalType)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setModal(true);
    setupUI();
}

MedalPopup::~MedalPopup()
{
    delete ui;
}

// 静态方法：检查并显示所有已解锁的勋章
void MedalPopup::checkAndShowUnlockedMedals(User& user, QWidget *parent)
{
    // 保存原始勋章数量
    int originalMedalCount = user.getMedalsCount();
    int newMedalsCount = 0;

    // 定义所有勋章类型
    const std::vector<MedalType> allMedals = {
        MedalType::BlazeMaster,
        MedalType::FrostLord,
        MedalType::GaiasChampion,
        MedalType::CelestialSage,
        MedalType::ThunderWielder,
        MedalType::UmbraKing,
        MedalType::EternalLuminary
    };

    // 检查每个勋章
    for (MedalType medal : allMedals)
    {
        if (!user.hasMedal(medal) && checkMedalUnlock(user, medal)) {
            user.addMedal(medal);
            newMedalsCount++;

            UserFileManager manager;
            manager.generateDeveloperReport("users.dat", "users_info.txt");

            // 立即显示新获得的勋章
            MedalPopup *popup = new MedalPopup(medal, parent);
            popup->setAttribute(Qt::WA_DeleteOnClose);
            popup->show();
        }
    }

    // 如果没有获得新勋章，但勋章数量发生了变化（可能被删除），也生成报告
    if (newMedalsCount == 0 && originalMedalCount != user.getMedalsCount())
    {
        UserFileManager manager;
        manager.generateDeveloperReport("users.dat", "users_info.txt");
    }
}

// 检查特定勋章是否解锁
bool MedalPopup::checkMedalUnlock(const User& user, MedalType type)
{
    // 如果用户已经有这个勋章，直接返回false
    if (user.hasMedal(type)) {
        return false;
    }

    std::vector<int> requiredLevels = getRequiredLevels(type);
    return std::all_of(requiredLevels.begin(), requiredLevels.end(),
        [&user](int levelId) { return user.isLevelPassed(levelId); });
}

// 获取勋章对应的关卡要求
std::vector<int> MedalPopup::getRequiredLevels(MedalType type)
{
    switch(type)
    {
        case MedalType::BlazeMaster:    return {1}; // 火焰关卡
        case MedalType::FrostLord:      return {2}; // 冰霜关卡
        case MedalType::GaiasChampion:  return {3}; // 自然关卡
        case MedalType::CelestialSage:  return {4}; // 神圣关卡
        case MedalType::ThunderWielder: return {5}; // 闪电关卡
        case MedalType::UmbraKing:      return {6}; // 暗影关卡
        case MedalType::EternalLuminary:return {0};  // 基础+最终关
        default: return {};
    }
}

// UI设置 (保持不变)
void MedalPopup::setupUI()
{
    // 设置固定窗口大小（宽度300，高度400）
    this->setFixedSize(300, 400);

    // 设置背景和样式
    setStyleSheet("background-color: rgba(50, 50, 50, 220); border-radius: 15px;");

    // 标题
    QLabel *titleLabel = new QLabel("勋章解锁!", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: gold; font-size: 28px; font-weight: bold;");
    //titleLabel->setGeometry(50, 20, 300, 40);
    titleLabel->setGeometry(0, 20, 300, 40);  // 宽度与窗口同宽

    // 勋章图标
    QLabel *iconLabel = new QLabel(this);
    QString iconPath ;
    switch(m_medalType)
  {
    case MedalType::BlazeMaster:
    {
        iconPath = QString(":/img/Debug/image/BlazeMaster.fw.png");
        break;
    }
    case MedalType::FrostLord:
    {
        iconPath = QString(":/img/Debug/image/FrostLord.fw.png");
        break;
    }
    case MedalType::GaiasChampion:
    {
       iconPath = QString(":/img/Debug/image/GaiasChampion.fw.png");
        break;
    }
    case MedalType::CelestialSage:
    {
        iconPath = QString(":/img/Debug/image/CelestialSage.fw.png");
        break;
    }
    case MedalType::ThunderWielder:
    {
        iconPath = QString(":/img/Debug/image/ThunderWielder.fw.png");
        break;
    }
    case MedalType::UmbraKing:
    {
        iconPath = QString(":/img/Debug/image/UmbraKing.fw.png");
        break;
    }
    case MedalType::EternalLuminary:
    {
        iconPath = QString(":/img/Debug/image/EternalLuminary.fw.png");
        break;
    }

 }

    iconLabel->setPixmap(QPixmap(iconPath).scaled(100, 100, Qt::KeepAspectRatio));
    iconLabel->setAlignment(Qt::AlignCenter);
    iconLabel->setGeometry(100, 70, 100, 100);  // 居中显示

    // 勋章名称
    QLabel *nameLabel = new QLabel(medalToString(m_medalType).c_str(), this);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("color: white; font-size: 22px; font-weight: bold;");
    nameLabel->setGeometry(0, 180, 300, 30);  // 宽度与窗口同宽

    // 勋章描述
    QLabel *descLabel = new QLabel(getMedalDescription(), this);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);
    descLabel->setStyleSheet("color: #DDD; font-size: 16px;");
    descLabel->setGeometry(20, 220, 260, 100);  // 左右留20像素边距

    // 确认按钮
    QPushButton *confirmBtn = new QPushButton("确 认", this);
    confirmBtn->setGeometry(75, 340, 150, 40);  // 居中，距离底部60像素
    confirmBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(230,180,94,70%);"
        "   color: black;"
        "   border-radius: 10px;"
        "   font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(230,180,94,80%);"
        "}"
    );

    connect(confirmBtn, &QPushButton::clicked, this, &MedalPopup::onConfirmClicked);
}

// 勋章描述 (保持不变)
QString MedalPopup::getMedalDescription() const
{
    switch(m_medalType)
    {
        case MedalType::BlazeMaster: return "烈焰征服者 - 完成所有火焰关卡";
        case MedalType::FrostLord: return "寒冰统治者 - 完成所有冰霜关卡";
        case MedalType::GaiasChampion: return "自然守护者 - 完成所有自然关卡";
        case MedalType::CelestialSage: return "神圣使者 - 完成所有神圣关卡";
        case MedalType::ThunderWielder: return "雷霆掌控者 - 完成所有闪电关卡";
        case MedalType::UmbraKing: return "暗影支配者 - 完成所有暗影关卡";
        case MedalType::EternalLuminary: return "传奇完成者 - 通关所有主线关卡";
        default: return "";
    }
}

void MedalPopup::onConfirmClicked()
{
    accept();


    close();


}
