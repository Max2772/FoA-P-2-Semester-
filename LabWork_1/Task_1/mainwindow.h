#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rocket.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int width_scene = 1000;
    int heigth_scene = 500;
    Rocket rock;

private slots:
    void moveObj();
    void turn_onObj();
    void restartObj();
};
#endif // MAINWINDOW_H
