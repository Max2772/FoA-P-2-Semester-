#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>
#include <vector>
#include <ctime>
#include <QSpinBox>
#include <QTemporaryFile>

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
    void setErase(const vector<Date> &newErase);

private:
    static const int YEAR_CONST = 1900;
    QString filePath;
    Date bDate = Date(27, 05, 2006);
    bool rewriteMode = false;

    QStringList dates;
    vector<Date> dateVector;
    vector<Date> erase(vector<Date> dateVector, int idx);

    void ImportDatesInTable();
    void calculateAll();
    void SetTodaysDate();
    void SetCurrentDate();
    void SetBirthDate(int day, int month, int year);
    bool addDateToFile(const QString &filePath, Date &date);
    bool deleteDateFromFile(const QString &filePath, int lineNumber);

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
    void on_bDayPushButton_clicked();
    void MonthSpinBox_valueChanged(QSpinBox* spinBoxDay, QSpinBox* spinBoxMonth, QSpinBox* spinBoxYear);
    void YearSpinBox_valueChanged(QSpinBox* spinBoxDay, QSpinBox* spinBoxMonth, QSpinBox* spinBoxYear);

    // Delete Element
    void on_actionDeleteElement_triggered();

    // Add date
    void on_addDatePushButton_clicked();

    // Save file
    void on_actionSave_triggered();

    // Get bool for Rewrite Mode
    void on_actionRewriteFile_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
