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

private slots:
    void on_spinBoxAmount_valueChanged(int num);

    void on_pushButtonSort_clicked();

private:
    void RandomNumberVectorGenerate();
    QVector<int> arr;

    int MINIMUM_RANDOM_NUMBER = 1;
    int MAXIMUM_RANDOM_NUMBER = 101;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
