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
    void on_pushButtonAddSize_clicked();
    void on_pushButtonAddElement_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonAutoFill_clicked();

private:
    void DisableUI(bool sizeUI, bool elementUI);
    void EnableUI(bool sizeUI, bool elementUI);

    QString FormatArray(const QVector<long long>& arr);
    void CalculateMedians();

    static const int MAX_ELEMENT_NUMBER = 1000;
    static const int MIN_ELEMENT_NUMBER = -1000;

    static const int MAX_SIZE_NUMBER = 21;
    static const int MIN_SIZE_NUMBER = 1;

    long long size;
    QVector<long long> arr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
