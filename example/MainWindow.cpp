#include "MainWindow.h"
#include "Theme.h"
#include "ui_MainWindow.h"
#include "Widgets/ToggleButton.h"
#include "Widgets/SwitchButton.h"
#include <QWKCore/styleagent.h>
#include <QWKWidgets/widgetwindowagent.h>
#include <QTimer>
#include <QColorDialog>
#include <QShortcut>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timer(new QTimer(this))
    , windowAgent(new QWK::WidgetWindowAgent(this))
{
    // this->setAttribute(Qt::WA_TranslucentBackground, true);
    installWindowAgent();
    ui->setupUi(this);
    m_timer->setInterval(50);

    // ui->lineEdit->setDisabled(true);

    ui->horizontalLayout_3->insertWidget(0, new SwitchButton(this));

    QStringList list;
    list << ":grid.svg"
         << ":list.svg"
         << ":download.svg";

    const auto iconToggleButton = new ToggleButton(list, this);
    iconToggleButton->setUseIcon(true);
    iconToggleButton->setColumnWidth(100);
    ui->horizontalLayout_3->addWidget(iconToggleButton);

    QStringList textList;
    textList << "Default"
             << "Account"
             << "Advance";
    const auto textToggleButton = new ToggleButton(textList, this);
    textToggleButton->setUseIcon(false);
    textToggleButton->setColumnWidth(100);
    ui->horizontalLayout_3->addWidget(textToggleButton);

    ui->darkModeCheckBox->setChecked(false);
    connect(ui->darkModeCheckBox, &QCheckBox::clicked, this, [](const bool checked) {
        CustomTheme::setDarkMode(checked);
    });
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stop);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::increaseProgress);

    auto* plusShortcut = new QShortcut(Qt::Key_J, this);
    connect(plusShortcut, &QShortcut::activated, this, &MainWindow::increaseProgress);
    auto* minusShortcut = new QShortcut(Qt::Key_K, this);
    connect(minusShortcut, &QShortcut::activated, this, &MainWindow::decreaseProgress);

    connect(ui->changeBg, &QPushButton::clicked, this, [this]() {
        windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "light");
    });
    // windowAgent->setWindowAttribute(QStringLiteral("blur-effect"), "light");

}

MainWindow::~MainWindow()
{
    delete ui;
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
