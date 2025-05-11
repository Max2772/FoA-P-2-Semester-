#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "deque.h"

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

    static const int MINIMUM_RANDOM_NUMBER = -99;
    static const int MAXIMUM_RANDOM_NUMBER = 99;

    static const int MINIMUM_RANDOM_SIZE = 1;
    static const int MAXIMUM_RANDOM_SIZE = 20;

private slots:
    void on_pushButtonGenerate_clicked();
    void on_pushButtonFront_clicked();
    void on_pushButtonBack_clicked();
    void on_pushButtonPopBack_clicked();
    void on_pushButtonSize_clicked();
    void on_pushButtonEmpty_clicked();
    void on_pushButtonPushFront_clicked();
    void on_pushButtonPushBack_clicked();
    void on_pushButtonPopFront_clicked();
private:
    void GenerateRandomDeque();
    void OutputDeque();
private:
    Deque d;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
