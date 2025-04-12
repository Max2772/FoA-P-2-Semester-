#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <vector>
#include <ctime>
#include <chrono>

#include "date.h"

using std::vector;

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
    QStringList dates;
    vector<Date> dateVector;
    void ImportDatesInTable();
    void calculateAll();
    void SetTodaysDate();
private slots:
    void on_actionImport_triggered();
    void on_actionClean_triggered();
    void on_actionUpdate_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
