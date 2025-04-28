#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "arraymanager.h"

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

    static const int SPINBOX_MIN_VALUE = 1;
    static const int SPINBOX_MAX_VALUE = 100;

private slots:
    void on_spinBoxAmount_valueChanged(int num);

    void on_pushButtonSort_clicked();

private:
    void OutputArray();

    QVector<int> arr;

    Ui::MainWindow *ui;
    ArrayManager arrayManager;
};
#endif // MAINWINDOW_H
