#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <vector>
#include <ctime>

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
    static const int YEAR_CONST = 1900;
    Date bDate = Date(27, 05, 2006);

    QStringList dates;
    vector<Date> dateVector;
    void ImportDatesInTable();
    void calculateAll();
    void SetTodaysDate();
    void SetCurrentDate();
    void SetBirthDate(int day, int month, int year);

    static Date GetCurrentDate()
    {
        time_t currentTime = time(nullptr);
        struct tm *localTime = localtime(&currentTime);
        Date currentDate((localTime->tm_mday), (localTime->tm_mon + 1), (localTime->tm_year + YEAR_CONST));
        return currentDate;
    }

private slots:
    // Menu
    void on_actionImport_triggered();
    void on_actionClean_triggered();
    void on_actionUpdate_triggered();

    // Birthday
    void on_pushButton_clicked();
    void on_bDayMonthSpinBox_valueChanged(int month);
    void on_bDayYearSpinBox_valueChanged(int year);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
