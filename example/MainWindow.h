
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    enum Theme
    {
        Dark,
        Light,
    };
    Q_ENUM(Theme)

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void start();
    void stop();

    void increaseProgress();
    void decreaseProgress();

private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    void installWindowAgent();
    QWK::WidgetWindowAgent* windowAgent;
};


#endif //MAINWINDOW_H
