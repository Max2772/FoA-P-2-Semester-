#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    static const int MAX_RANDOM_KEY = 11;
    static const int MIN_RANDOM_KEY = -10;
    static const int MIN_RANDOM_VALUE = 0;
    static const int MAX_RANDOM_VALUE = 101;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
