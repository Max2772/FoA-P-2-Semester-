#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    static const int SPINBOX_MAX_VALUE = 120;

private slots:
    void on_spinBoxAmount_valueChanged(int num);
    void on_pushButtonSort_clicked();
    void on_comboBoxSortType_currentTextChanged(const QString &text);
    void on_pushButtonShuffle_clicked();
    void on_pushButtonFindElement_clicked();

    void onSortingStateChanged(bool isSorting);
    void onSortTimeUpdated(qint64 timeResult);

    void onSearchStateChanged(bool isSearching);
    void onSearchResult(int idx);

private:
    Ui::MainWindow *ui;
    SortController* sortController;
    SortVisualizer* sortVisualizer;
};
#endif // MAINWINDOW_H
