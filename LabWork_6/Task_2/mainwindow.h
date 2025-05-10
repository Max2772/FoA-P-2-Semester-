#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
private:
    void Task1();
    void Task2();
    void Task3();
    void Task4();
    void Task5();
private:
    int mode;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
