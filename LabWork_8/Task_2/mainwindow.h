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

    static const int MIN_SIZE = 1;
    static const int MAX_SIZE = 10;
    static const int MIN_NUM = 1;
    static const int MAX_NUM = 10;
private:
    QVector<int> CreateRandomArray();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
