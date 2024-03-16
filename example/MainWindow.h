
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VanillaStyle/Style/VanillaStyle.h"
#include "extern/qwindowkit/src/core/style/styleagent.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

namespace QWK
{
class WidgetWindowAgent;
}  // namespace QWK

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void setTheme(bool theme);
    void setLightTheme();
    void setDarkTheme();
    void start();
    void stop();

    void increaseProgress();
    void decreaseProgress();

    Q_SLOT void setAutoTheme();

private:
    Ui::MainWindow* ui;
    QTimer* m_timer;
    void installWindowAgent();
    QWK::WidgetWindowAgent* windowAgent;
    QWK::StyleAgent* styleAgent;

    // protected:
    // void paintEvent(QPaintEvent* event) override;
};

#endif  // MAINWINDOW_H
