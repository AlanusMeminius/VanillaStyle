#include <QTimer>
#include <QButtonGroup>
#include <QMenu>
#include <QShortcut>

#include <QWKCore/styleagent.h>
#include <QWKWidgets/widgetwindowagent.h>

#include <VanillaStyle/Style.h>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VanillaStyle/Style/Global.h"
#include "VanillaStyle/Widgets/Spinner.h"

#include "VanillaStyle/Widgets/ToggleButton.h"

#include <QFile>
#include <QPushButton>
#include <QRadioButton>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(new QTimer(this))
    , windowAgent(new QWK::WidgetWindowAgent(this))
    , styleAgent(new QWK::StyleAgent(this))
{
    installWindowAgent();
    ui->setupUi(this);
    m_timer->setInterval(100);

    ui->progressBar->setValue(0);
    ui->toggleBtnfirst->setIconList(QStringList{":grid.svg", ":list.svg", ":download.svg"});
    ui->toggleBtnfirst->setToolTips(QStringList{"Default", "Account", "Advance"});
    ui->toggleBtnfirst->setColumnWidth(50);

    ui->toggleBtnSecond->setItemList(QStringList{"Default", "Account", "Advance"});
    ui->toggleBtnSecond->setColumnWidth(100);

    ui->iconWithText->setIconList(QStringList{":grid.svg", ":list.svg", ":download.svg"});
    ui->iconWithText->setItemList(QStringList{"Default", "Account", "Advance"});
    ui->iconWithText->setColumnWidth(120);
    ui->iconWithText->setVertical();
    ui->iconWithText->setRowHeight(40);

    ui->radioButton->setChecked(true);

    ui->pushButton->setCheckable(true);

    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::setLightTheme);
    connect(ui->radioButton_2, &QRadioButton::toggled, this, &MainWindow::setDarkTheme);
    connect(ui->radioButton_3, &QRadioButton::clicked, this, [this](const bool checked) {
        if (checked)
        {
            connect(styleAgent, &QWK::StyleAgent::systemThemeChanged, this, &MainWindow::setAutoTheme);
        }
        else
        {
            disconnect(styleAgent, &QWK::StyleAgent::systemThemeChanged, this, &MainWindow::setAutoTheme);
        }
    });

    ui->startButton->setProperty(VANILLA_PATCH_PROPERTY, QVariant("CleanButtonPatch"));
    ui->startButton->setText("");
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::increaseProgress);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::setAutoTheme);

    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->tableWidget->setRowCount(5);     // 设置行数
    ui->tableWidget->setColumnCount(3);  // 设置列数

    const QStringList headers = {"Item", "Select", "Description"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setProperty(Vanilla::s_CustomItemViewBackground.c_str(), true);
    for (int row = 0; row < 5; ++row)
    {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString("Item %1").arg(row + 1)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem("Description here"));

        auto* checkBoxItem = new QTableWidgetItem();
        checkBoxItem->setBackground(Qt::darkCyan);
        checkBoxItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkBoxItem->setCheckState(Qt::Checked);  // 初始状态为未选中
        ui->tableWidget->setItem(row, 1, checkBoxItem);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTheme(const bool theme)
{
    windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), theme ? "light" : "dark");
}

void MainWindow::setLightTheme()
{
    // Vanilla::Style::setStyleFromAppDir(QStringLiteral("LightVanillaStyle"));
    const auto filePath = QCoreApplication::applicationDirPath() + "/LightVanillaStyle.json";
    if (QFile(filePath).exists())
    {
        Vanilla::Style::setStyleFromPath(filePath);
    }
    else
    {
        Vanilla::Style::setDefaultTheme(Vanilla::Light);
    }
    setTheme(true);
}

void MainWindow::setDarkTheme()
{
    // Vanilla::Style::setStyleFromName(QStringLiteral("DarkVanillaStyle"));
    const auto filePath = QCoreApplication::applicationDirPath() + "/DarkVanillaStyle.json";
    if (QFile(filePath).exists())
    {
        Vanilla::Style::setStyleFromPath(filePath);
    }
    else
    {
        Vanilla::Style::setDefaultTheme(Vanilla::Dark);
    }
    setTheme(false);
}

void MainWindow::setAutoTheme()
{
    const auto theme = styleAgent->systemTheme();
    theme == QWK::StyleAgent::SystemTheme::Dark ? setDarkTheme() : setLightTheme();
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    if (m_menu == nullptr)
    {
        m_menu = new QMenu(this);
        // createContextMenu();
        m_menu->setProperty("_vanillaStyle_Patch","CheckBoxWithNoBorder");
        auto* downloadAction = new QAction(QIcon(":/download.svg"), "Download\tCTRL ALT D", this);
        downloadAction->setCheckable(true);
        connect(downloadAction, &QAction::triggered, this, [downloadAction](bool checked) {
            downloadAction->setChecked(checked);
        });
        m_menu->addAction(downloadAction);
        auto* secondAction = new QAction("placeHolder PlaceHolder\t⌘ D");
        m_menu->addAction(secondAction);
    }
    m_menu->popup(event->globalPos());
}

void MainWindow::start()
{
    m_timer->start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainWindow::stop()
{
    m_timer->stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}

void MainWindow::increaseProgress()
{
    const int value = (ui->progressBar->value() + 1) % 101;
    ui->progressBar->setValue(value);
}

void MainWindow::decreaseProgress()
{
    const int value = (ui->progressBar->value() + 100) % 101;
    ui->progressBar->setValue(value);
}

void MainWindow::installWindowAgent()
{
    windowAgent->setup(this);
    const auto bar = new QWidget(this);
    bar->setMinimumHeight(30);
    windowAgent->setTitleBar(bar);
    setMenuWidget(bar);
}