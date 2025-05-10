#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "motorcycle.h"
#include <QTimer>

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
    void on_pushButtonAddElement_clicked();
private:
    void InitializeInfo();
    void FillTable();
    void FillElement(const Motorcycle& moto, int row);
private:
    Motorcycle motorcycles[5];
    Motorcycle motorcyclePointer;
    Motorcycle* ptr = &motorcyclePointer;
    Motorcycle motorcycleRef;
    Motorcycle &motoRef = motorcycleRef;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
