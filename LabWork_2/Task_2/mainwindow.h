#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QDate>

#include "filemanager.h"
#include "order.h"

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
    void on_pushButtonImport_clicked();
    void FillTable(const QVector<Order> &orderVector);

    void ShowErrorEvent(QString information);
    void ShowInformationEvent(QString information);
    void on_spinBoxDeleteOrder_valueChanged(int arg1);

    void on_pushButtonDeleteOrder_clicked();

    void on_pushButtonAdd_clicked();

private:
    Ui::MainWindow *ui;
    FileManager fileManager;
};
#endif // MAINWINDOW_H
