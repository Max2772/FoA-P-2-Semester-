#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>

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
private:
    void ProgressReset();
    void CheckSymbol(QString symbol);
    void HighlightLetter(int position, const QColor &color);

    bool isRunning;
    QTimer timer;
    QString currentText;
    int currentIdx;
    QString mask;
    KeyboardWidget *keyboardWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
