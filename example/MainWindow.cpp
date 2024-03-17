#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VanillaStyle/Style.h"
#include "VanillaStyle/Helper/ItemViewStyle.h"
#include "VanillaStyle/Style/VanillaStyle.h"
#include "VanillaStyle/Widgets/IconLabel.h"

#include <QWKCore/styleagent.h>
#include <QWKWidgets/widgetwindowagent.h>
#include <QTimer>
#include <QButtonGroup>
#include <QColorDialog>
#include <QShortcut>
#include <QtGui/QPainter>
#include "VanillaStyle/Widgets/SwitchButton.h"
#include "VanillaStyle/Widgets/ToggleButton.h"
// #include <Theme.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(new QTimer(this))
    , windowAgent(new QWK::WidgetWindowAgent(this))
    , styleAgent(new QWK::StyleAgent(this))
{
    installWindowAgent();
    ui->setupUi(this);
    m_timer->setInterval(50);
    // ui->lineEdit->setDisabled(true);

    ui->toggleBtnfirst->setItemList(QStringList{":grid.svg", ":list.svg", ":download.svg"});
    ui->toggleBtnfirst->setColumnWidth(50);

    ui->toggleBtnSecond->setUseIcon(false);
    ui->toggleBtnSecond->setItemList(QStringList{"Default", "Account", "Advance"});
    ui->toggleBtnSecond->setColumnWidth(100);

    ui->iconLabelFirst->setIcon(QIcon(":download.svg"));
    ui->iconLabelFirst->setLabel("Download");

    ui->iconLabelSecond->setIcon(QIcon(":download.svg"));
    ui->iconLabelSecond->setLabel("Download");
    ui->iconLabelSecond->setIconFirst(false);

    ui->iconBtn->setIcon(QIcon(":download.svg"));

    ui->radioButton->setChecked(true);

    setAutoTheme();

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

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::increaseProgress);

    auto* plusShortcut = new QShortcut(Qt::Key_J, this);
    connect(plusShortcut, &QShortcut::activated, this, &MainWindow::increaseProgress);
    auto* minusShortcut = new QShortcut(Qt::Key_K, this);
    connect(minusShortcut, &QShortcut::activated, this, &MainWindow::decreaseProgress);

    // auto *view = new VanillaStyle::RoundRectListView;
    // ui->comboBox->setView(view);
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
    VanillaStyle::Style::setStyleFromName(QStringLiteral("LightVanillaStyle"));
    setTheme(true);
}
void MainWindow::setDarkTheme()
{
    VanillaStyle::Style::setStyleFromName(QStringLiteral("DarkVanillaStyle"));
    setTheme(false);
}
void MainWindow::setAutoTheme()
{
    const auto theme = styleAgent->systemTheme();
    theme == QWK::StyleAgent::SystemTheme::Dark ? setDarkTheme() : setLightTheme();
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