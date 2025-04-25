#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QDate>

#include "filemanager.h"
#include "ordermanager.h"
#include "searchwindow.h"
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
    void SetSpinBoxesMaximum();

    void ShowErrorEvent(QString information);
    void ShowInformationEvent(QString information);
    void AddElementToTable(const Order &order, const int &idx);

    void on_pushButtonDeleteOrder_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonEdit_clicked();

    void on_radioButtonReadyOrders_toggled(bool checked);
    void on_radioButtonUnfinishedOrders_toggled(bool checked);

    void on_comboBoxGroupNameReadyOrders_currentIndexChanged(int index);
    void on_comboBoxGroupNameSort_currentTextChanged(const QString &choice);

    void on_pushButtonSearch_clicked();

private:
    Ui::MainWindow *ui;
    FileManager fileManager;
    OrderManager orderManager;
};
#endif // MAINWINDOW_H
