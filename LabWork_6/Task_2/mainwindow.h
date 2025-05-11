#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "motorcycle.h"

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
    void on_comboBoxMode_activated(int mode);
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject* object, QEvent* event) override;
    void on_pushButtonAddElement_clicked();

private:
    void CheckElementsUI(bool on);
    void CheckIOUI(bool on);

    void Task1();
    void Task1Print();
    void Task2();
    void Task2Print();
    void Task3(const Motorcycle &motorcycle);
    void Task3Print();
    void Task4(const Motorcycle &motorcycle);
    void Task4Print();
    void Task5();
    void Task5Print();
private:
    const char SPLITTER = '!';
    const char SPLITTER_STRUCT = '|';
    int mode;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
