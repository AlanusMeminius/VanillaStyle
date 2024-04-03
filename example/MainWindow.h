
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
class StyleAgent;
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
    void installWindowAgent();

private:
    Ui::MainWindow* ui;
    QTimer* m_timer;
    QWK::WidgetWindowAgent* windowAgent;
    QWK::StyleAgent* styleAgent;
};

#endif  // MAINWINDOW_H
