#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "sortcontroller.h"
#include "sortvisualizer.h"

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
    static const int SPINBOX_MAX_VALUE = 3;

private slots:
    void on_spinBoxAmount_valueChanged(int num);
    void on_pushButtonSort_clicked();
    void on_pushButtonShuffle_clicked();
    void on_pushButtonFindElement_clicked();

    void onSortingStateChanged(bool isSorting);
    void onSearchStateChanged(bool isSearching);
    void onSearchResult(int idx, int result);

private:
    Ui::MainWindow *ui;
    SortController* sortController;
    SortVisualizer* sortVisualizer;
};
#endif // MAINWINDOW_H
