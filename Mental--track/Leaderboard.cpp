#include "Leaderboard.h"
#include "ui_Leaderboard.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QTimer>
#include <QDebug>
#include<QLabel>

Leaderboard::Leaderboard(const QString& reportFile, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Leaderboard),
    m_reportFile(reportFile),
    m_currentDisplayMode(PassedLevels)  // 默认显示通关数排行榜
{
    ui->setupUi(this);

    //设置背景图片
    QLabel *label_Background=new QLabel(this);
    label_Background->setGeometry(0,0,1200,1200);
    label_Background->setPixmap(QPixmap(":/img/Debug/image/Listbg.fw.png"));
    label_Background->setScaledContents(true);
    label_Background->lower(); // 关键：将背景置于底层

    // 添加返回按钮
    QPushButton* backButton = new QPushButton("返回", this);
    backButton->setFixedSize(300, 100);
    backButton->move(450, 1100); // 右上角位置
    QFont font1("华文行楷", 30, QFont::Bold);
    backButton->setFont(font1);

    backButton->setStyleSheet(
        "QPushButton {"
        "     background-color: rgba(230,180, 94, 60%);"
        "   color: Black;"               // 文字颜色
        "   border-radius: 10px;"        // 圆角
        "   padding: 5px;"               // 内边距
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(230,180, 94, 70%);"  // 悬浮状态背景色
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(230,180, 94, 80%);"  // 点击状态背景色
        "}"
    );

    connect(backButton, &QPushButton::clicked, [=](){
        emit returnToMain();  // 发射返回信号
        this->close();        // 关闭排行榜
    });

    setFixedSize(1200, 1200);
    setWindowTitle("排行榜");

    qDebug() << "正在初始化排行榜，报告文件:" << reportFile;

    // 1. 初始化表格基础设置
    initTable();

    // 2. 应用样式表
   { setStyleSheet(R"(
                  /* 表格整体样式 */
                     QTableWidget {
                         border: 1px solid #e0e0e0;
                         border-radius: 8px;
                         background-color: rgba(255, 255, 255, 0.5); /* 半透明背景 */
                         gridline-color: #f0f0f0;
                         outline: 0; /* 去除选中虚线框 */
                     }

                     /* 表头样式 */
                     QHeaderView::section {
                         background-color: #5F9EA0; /* 表头背景色 */
                         color: black;
                         padding: 10px;
                         border: none;
                         font-family: "华文行楷";
                         font-size: 39px;
                         font-weight: bold;
                         border-radius: 5px;
                     }

                     /* 单元格样式 */
                     QTableWidget::item {
                         padding: 8px;
                         border-bottom: 1px solid #f0f0f0;
                         text-align: center;

                     }

                     /* 鼠标悬停效果 */
                     QTableWidget::item:hover {
                         background-color: rgba(255, 255, 255, 0.6);
                     }



    )");

    }
    // 3. 高级表格设置
    //ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(108);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    // 4. 设置字体
    QFont font("Azeri France Lat", 15,QFont::Bold,0);
    ui->tableWidget->setFont(font);





    //解析用户文件
    parseReportFile();

    connect(ui->btnPassedLevels, &QPushButton::clicked, this, &Leaderboard::onPassedLevelsClicked);
    connect(ui->btnBestTimes, &QPushButton::clicked, this, &Leaderboard::onBestTimesClicked);
    connect(ui->btnMedals, &QPushButton::clicked, this, &Leaderboard::onMedalsClicked);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::geometriesChanged,
            this, &Leaderboard::adjustTableColumns);

    onPassedLevelsClicked();
}

// 新增方法：设置表头
void Leaderboard::setTableHeaders(DisplayMode mode)
{
    m_currentDisplayMode = mode;

    switch(mode) {
    case PassedLevels:
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels({"排名", "玩家名称", "通关关卡数"});
        break;
    case BestTimes:
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels({"关卡ID", "最短时间", "最佳玩家", "所有记录"});
        break;
    case Medals:
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels({"排名", "玩家名称", "勋章数量", "勋章详情"});
        break;
    }
}

void Leaderboard::parseReportFile()
{
    QFile file(m_reportFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "无法打开报告文件:" << m_reportFile;
            return;
        }


        // 强制使用UTF-8编码读取
        QTextStream in(&file);
        in.setCodec("UTF-8");

        PlayerData currentPlayer;
        bool readingLevels = false;
        bool readingMedals = false;
        bool gotMedalTitle = false; // 新增标志，表示是否已读取"勋章详情:"行

        while (!in.atEnd())
        {
            QString line = in.readLine();
            line = line.trimmed(); // 去除前后空白

            // 调试输出当前解析的行
            qDebug() << "正在解析行:" << line;

            // 跳过分隔线和报告头
            if (line.startsWith("===") || line.startsWith("生成时间") ||
                line.startsWith("用户总数") || line.trimmed().isEmpty()) {
                continue;
            }

            // 处理用户数据开始
            if (line.startsWith("用户名:")) {
                // 保存上一个玩家的数据
                if (!currentPlayer.username.isEmpty()) {
                    m_players.append(currentPlayer);
                    currentPlayer = PlayerData();
                }
                currentPlayer.username = line.section(':', 1).trimmed();
                qDebug() << "找到用户:" << currentPlayer.username;
                continue;
            }

            // 处理通过关卡数
            if (line.startsWith("通过关卡数:")) {
                QString levelStr = line.section(':', 1).section('/', 0, 0).trimmed();
                bool ok;
                int levels = levelStr.toInt(&ok);
                if (ok) {
                    currentPlayer.passedLevels = levels;
                    qDebug() << currentPlayer.username << "通过关卡数:" << levels;
                }
                readingLevels = false;
                continue;
            }

            // 处理关卡详情
            if (line.trimmed().startsWith("通过的关卡详情")) {
                readingLevels = true;
                readingMedals = false;
                continue;
            }

            // 处理关卡记录行
            if (readingLevels && line.trimmed().startsWith("关卡")) {
                QString trimmedLine = line.trimmed();
                QStringList parts = trimmedLine.split('-');
                if (parts.size() >= 2) {
                    QString levelPart = parts[0].trimmed();
                    int levelId = levelPart.mid(2).toInt(); // 去掉"关卡"两字

                    QString timePart = parts[1].section(':', 1).trimmed();
                    timePart.remove("秒");
                    bool ok;
                    float time = timePart.toFloat(&ok);

                    if (ok) {
                        currentPlayer.levelTimes[levelId] = time;
                        qDebug() << currentPlayer.username << "关卡" << levelId << "时间:" << time;

                        // 更新全局最佳时间
                        if (!m_bestTimes.contains(levelId) || time < m_bestTimes[levelId].first) {
                            m_bestTimes[levelId] = qMakePair(time, currentPlayer.username);
                        }
                    }
                }
                continue;
            }

            // 处理勋章数
            if (line.startsWith("获得勋章数:")) {
                QString medalStr = line.section(':', 1).trimmed();
                bool ok;
                int medals = medalStr.toInt(&ok);
                if (ok) {
                    currentPlayer.medalsCount = medals;
                    qDebug() << currentPlayer.username << "勋章数:" << medals;
                }
                readingMedals = false;
                continue;
            }

            // 处理勋章详情标题行
                    if (line.startsWith("勋章详情:"))
                    {
                        readingMedals = true;
                        gotMedalTitle = true;
                        currentPlayer.medalsList.clear();
                        continue;
                    }

                    // 处理勋章详情内容行（在标题行之后且不为空的行）
                    if (readingMedals && gotMedalTitle && !line.trimmed().isEmpty())
                    {
                        // 跳过可能的分隔线
                        if (line.startsWith("---") || line.startsWith("===")) {
                            continue;
                        }

                        // 添加勋章到列表中（每行一个勋章）
                        QString medal = line.trimmed();
                        if (!medal.isEmpty()) {
                            currentPlayer.medalsList.append(medal);  // 使用QStringList存储多个勋章
                            qDebug() << currentPlayer.username << "获得勋章:" << medal;
                        }
                        continue;
                    }


            // 处理用户数据结束
            if (line.startsWith("---") || line.startsWith("===")) {
                readingLevels = false;
                readingMedals = false;
                gotMedalTitle = false;
                continue;
            }
        }

        // 添加最后一个玩家
        if (!currentPlayer.username.isEmpty())
        {
            m_players.append(currentPlayer);
        }

        file.close();

        // 调试输出解析结果
        qDebug() << "解析完成，共加载" << m_players.size() << "个玩家";
        for (const auto& player : m_players)
        {
            player.debugPrint();
        }
}

void Leaderboard::onPassedLevelsClicked()
{
    clearTable();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels({"排名", "玩家名称", "通关关卡数"});

    // 按通关数排序
    std::sort(m_players.begin(), m_players.end(),
        [](const PlayerData& a, const PlayerData& b) {
            return a.passedLevels > b.passedLevels;
        });

    if (m_players.isEmpty())
    {
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("暂无通关记录"));
        ui->tableWidget->setSpan(0, 0, 1, 3);
        return;
    }

    // 填充表格
    for (int i = 0; i < m_players.size() && i < 100; ++i) {
        const PlayerData& player = m_players[i];
        // 排名列
         QTableWidgetItem* rankItem = new QTableWidgetItem(QString::number(i + 1));
         rankItem->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 0, rankItem);

        // 玩家名列
         QTableWidgetItem* nameItem = new QTableWidgetItem(player.username);
         nameItem->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 1, nameItem);

         // 通关数列
         QTableWidgetItem* levelItem = new QTableWidgetItem(QString::number(player.passedLevels));
         levelItem->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 2, levelItem);
    }

    adjustTableColumns();
}

void Leaderboard::onBestTimesClicked()
{
    clearTable();
       ui->tableWidget->setColumnCount(4);
       ui->tableWidget->setHorizontalHeaderLabels({"关卡ID", "最短时间", "最佳玩家", "所有记录"});

       if (m_bestTimes.isEmpty()) {
           ui->tableWidget->setItem(0, 0, new QTableWidgetItem("暂无通关记录"));
           ui->tableWidget->setSpan(0, 0, 1, 4);
           return;
       }

       // 获取排序后的关卡ID
       QList<int> sortedLevels = m_bestTimes.keys();
       std::sort(sortedLevels.begin(), sortedLevels.end());

       // 填充表格
          int row = 0;
          for (int levelId : sortedLevels) {
              if (row >= 100) break;

              // 收集所有玩家的该关卡记录
              QString allRecords;
              for (const PlayerData& player : m_players) {
                  if (player.levelTimes.contains(levelId)) {
                      allRecords += QString("%1: %2秒\n")
                          .arg(player.username)
                          .arg(player.levelTimes[levelId], 0, 'f', 2);
                  }
              }

              // 确保表格有足够的行
              if (row >= ui->tableWidget->rowCount()) {
                  ui->tableWidget->insertRow(row);
              }

              // 关卡ID列
              QTableWidgetItem* levelItem = new QTableWidgetItem(QString::number(levelId));
              levelItem->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget->setItem(row, 0, levelItem);

              // 最短时间列
              QTableWidgetItem* timeItem = new QTableWidgetItem(QString::number(m_bestTimes[levelId].first, 'f', 2) + "秒");
              timeItem->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget->setItem(row, 1, timeItem);

              // 最佳玩家列
              QTableWidgetItem* playerItem = new QTableWidgetItem(m_bestTimes[levelId].second);
              playerItem->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget->setItem(row, 2, playerItem);

              // 所有记录列
              QTableWidgetItem* recordsItem = new QTableWidgetItem(allRecords);
              recordsItem->setTextAlignment(Qt::AlignCenter);
              ui->tableWidget->setItem(row, 3, recordsItem);

              row++;
          }

          // 移除多余的行
          while (ui->tableWidget->rowCount() > row) {
              ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1);
          }

          adjustTableColumns();
}

void Leaderboard::onMedalsClicked() {
    clearTable();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels({"排名", "玩家名称", "勋章数量", "勋章详情"});

    // 按勋章数排序
    std::sort(m_players.begin(), m_players.end(),
        [](const PlayerData& a, const PlayerData& b) {
            return a.medalsCount > b.medalsCount;
        });

    // 填充表格
    for (int i = 0; i < m_players.size() && i < 100; ++i) {
        const PlayerData& player = m_players[i];

        // 排名列
        QTableWidgetItem* rankItem = new QTableWidgetItem(QString::number(i + 1));
        rankItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 0, rankItem);

        // 玩家名称列
        QTableWidgetItem* nameItem = new QTableWidgetItem(player.username);
        nameItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 1, nameItem);

        // 勋章数量列
        QTableWidgetItem* medalCountItem = new QTableWidgetItem(QString::number(player.medalsCount));
        medalCountItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 2, medalCountItem);

        // 勋章详情列 - 显示最多3个勋章
        QString medalText;
        if (player.medalsCount > 0) {
            // 取前3个勋章
            int showCount = qMin(3, player.medalsList.size());
            QStringList shownMedals;
            for (int j = 0; j < showCount; ++j) {
                shownMedals.append(player.medalsList[j]);
            }
            medalText = shownMedals.join("\n");

            // 如果有更多勋章，添加提示
            if (player.medalsCount > 3) {
                medalText += QString("\n(还有%1个勋章...)").arg(player.medalsCount - 3);
            }
        } else {
            medalText = "无";
        }

        QTableWidgetItem* medalDetailItem = new QTableWidgetItem(medalText);
        medalDetailItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 3, medalDetailItem);
    }
    adjustTableColumns();
}

void Leaderboard::initTable()
{
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->setColumnCount(4);



    for(int i = 0; i < 100; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(!ui->tableWidget->item(i, j))
            {
                 ui->tableWidget->setItem(i, j, new QTableWidgetItem(""));
            }
        }
    }

    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionsMovable(false);
}

void Leaderboard::clearTable()
{
    ui->tableWidget->clearContents();
       setTableHeaders(m_currentDisplayMode);

       int rowCount = std::min(100, m_players.size());
       ui->tableWidget->setRowCount(rowCount);

       for(int i = 0; i < rowCount; ++i) {
           for(int j = 0; j < ui->tableWidget->columnCount(); ++j) {
               if(!ui->tableWidget->item(i, j)) {
                   QTableWidgetItem* item = new QTableWidgetItem("");
                   item->setTextAlignment(Qt::AlignCenter);  // 关键修改：设置默认居中
                   ui->tableWidget->setItem(i, j, item);
               }
           }
       }
}

void Leaderboard::adjustTableColumns()
{
    QTimer::singleShot(100, this, [this](){
        ui->tableWidget->resizeColumnsToContents();

        int totalWidth = ui->tableWidget->viewport()->width();
        int contentWidth = 0;

        for(int i = 0; i < ui->tableWidget->columnCount(); ++i)
        {
            contentWidth += ui->tableWidget->columnWidth(i);
        }

        if(contentWidth < totalWidth)
        {
            int extraWidth = (totalWidth - contentWidth) / ui->tableWidget->columnCount();
            for(int i = 0; i < ui->tableWidget->columnCount(); ++i) {
                ui->tableWidget->setColumnWidth(i, ui->tableWidget->columnWidth(i) + extraWidth);
            }
        }
    });
}

Leaderboard::~Leaderboard()
{
    delete ui;
}
