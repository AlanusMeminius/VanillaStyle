#include "MainWindow.h"
#include "ui_MainWindow.h"
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
{
    installWindowAgent();
    ui->setupUi(this);
    m_timer->setInterval(50);
    // ui->lineEdit->setDisabled(true);
    ui->horizontalLayout_7->insertWidget(0, new VanillaStyle::SwitchButton(this));

    QStringList list;
    list << ":grid.svg"
         << ":list.svg"
         << ":download.svg";

    const auto iconToggleButton = new VanillaStyle::ToggleButton(list, this);
    iconToggleButton->setUseIcon(true);
    iconToggleButton->setColumnWidth(50);
    ui->horizontalLayout_3->addWidget(iconToggleButton);

    QStringList textList;
    textList << "Default"
             << "Account"
             << "Advance";
    const auto textToggleButton = new VanillaStyle::ToggleButton(textList, this);
    textToggleButton->setUseIcon(false);
    textToggleButton->setColumnWidth(100);
    ui->horizontalLayout_3->addWidget(textToggleButton);

    ui->radioButton->setChecked(true);
    // setTheme(true);
    connect(ui->radioButton, &QRadioButton::clicked, this, [this]() {
        setTheme(true);
    });
    connect(ui->radioButton_2, &QRadioButton::clicked, this, [this]() {
        setTheme(false);
    });

    auto styleAgent = new QWK::StyleAgent(this);
    connect(styleAgent, &QWK::StyleAgent::systemThemeChanged, this, [this, styleAgent]() {
        if (const auto theme = styleAgent->systemTheme(); theme == QWK::StyleAgent::SystemTheme::Dark)
        {
            setTheme(false);
        }
        else if (theme == QWK::StyleAgent::SystemTheme::Light)
        {
            setTheme(true);
        }
    });

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::increaseProgress);

    auto* plusShortcut = new QShortcut(Qt::Key_J, this);
    connect(plusShortcut, &QShortcut::activated, this, &MainWindow::increaseProgress);
    auto* minusShortcut = new QShortcut(Qt::Key_K, this);
    connect(minusShortcut, &QShortcut::activated, this, &MainWindow::decreaseProgress);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setTheme(const bool theme)
{
    // CustomTheme::setDarkMode(!theme);
    windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), theme ? "light" : "dark");
    style()->polish(this);
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
// void MainWindow::paintEvent(QPaintEvent* event)
// {
//     QMainWindow::paintEvent(event);
//     // QPainter painter(this);
//     // painter.setCompositionMode(QPainter::CompositionMode_Clear);
//     // painter.fillRect(event->rect(), Qt::transparent);
// }
