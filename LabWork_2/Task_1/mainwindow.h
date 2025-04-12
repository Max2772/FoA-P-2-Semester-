#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QStringList>
#include <QMessageBox>

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
    void ImportDatesInTable();
private slots:
    void on_actionImport_triggered();
    void on_actionClean_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
