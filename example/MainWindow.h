
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VanillaStyle/Style/VanillaStyle.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace QWK
{
class WidgetWindowAgent;
}  // namespace QWK


class MainWindow : public QMainWindow {
Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTheme(bool theme);

    void start();
    void stop();

    void increaseProgress();
    void decreaseProgress();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    void installWindowAgent();
    QWK::WidgetWindowAgent* windowAgent;


// protected:
    // void paintEvent(QPaintEvent* event) override;
};


#endif //MAINWINDOW_H
