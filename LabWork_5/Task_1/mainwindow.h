#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>

#include "keyboardwidget.h"

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
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void on_pushButtonOpenFile_clicked();
    void on_comboBoxLanguage_currentIndexChanged(int index);

    void updateTimer();
    void updateAccuracy();
    void updateSpeed();

    void on_pushButtonPause_clicked(bool checked);

    void on_pushButtonRestart_clicked();

private:
    void ProgressReset();
    void CheckSymbol(QString symbol);
    void HighlightLetter(int position, const QColor &color);

    bool isFileOpened;
    bool isRunning;
    bool isStopped;
    QTimer *timer;
    QTime time;
    QString currentText;
    int currentIdx;
    int seconds;
    QString mask;
    KeyboardWidget *keyboardWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
