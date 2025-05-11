#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QWidget>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include<QDebug>

namespace Ui {
class Leaderboard;
}

// 添加排行榜模式枚举
enum DisplayMode {
    PassedLevels,
    BestTimes,
    Medals,
    workshop // 新增
};

struct PlayerData
{
    QString username;
    int passedLevels = 0;  // 初始化默认值
    QMap<int, float> levelTimes; // levelId -> bestTime
    int medalsCount = 0;   // 初始化默认值
    QStringList medalsList;  // 改为存储多个勋章的列表
    int createdMaps = 0;
    int workshopPoints = 0;

    // 新增人机对战属性
    int battleWins = 0;
    int battleTotal = 0;
    int battlePoints = 0;

    // 添加调试方法
    void debugPrint() const
    {
        qDebug() << "Player:" << username
                 << "| Levels:" << passedLevels
                 << "| Medals:" << medalsCount
                 << "| Medal List:" << medalsList.join(", ")
                 << "| Battle Wins:" << battleWins
                 << "| Battle Total:" << battleTotal
                 << "| Battle Points:" << battlePoints;


        for (auto it = levelTimes.begin(); it != levelTimes.end(); ++it)
        {
            qDebug() << "  Level" << it.key() << ":" << it.value() << "sec";
        }
    }
};

class Leaderboard : public QWidget
{
    Q_OBJECT

public:
    explicit Leaderboard(const QString& reportFile, QWidget *parent = nullptr);
    ~Leaderboard();

signals:
    void returnToMain();  // 添加返回信号

private slots:
    void onPassedLevelsClicked();
    void onBestTimesClicked();
    void onMedalsClicked();
    void onWorkshopClicked();
    void on_btnWorkshop_clicked();
    void on_btnBattle_clicked();

private:
    void parseReportFile();
    void clearTable();
    void initTable();
    void adjustTableColumns();
    void setTableHeaders(DisplayMode mode);  // 新增方法

    Ui::Leaderboard *ui;
    QString m_reportFile;
    QVector<PlayerData> m_players;
    QMap<int, QPair<float, QString>> m_bestTimes; // levelId -> (time, player)
    DisplayMode m_currentDisplayMode;  // 当前显示模式
};

#endif // LEADERBOARD_H
