#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

#include "sort.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    arrayManager.RandomNumberVectorGenerate(arr, num);
    OutputArray();
}


void MainWindow::on_pushButtonSort_clicked()
{
    Sort::QuickSort(arr, 0, arr.size() - 1);
    qDebug() << "Array:" << arr;
    OutputArray();
}

void MainWindow::OutputArray()
{
    QStringList numbers;
    for(const int num: arr){
        numbers.append(QString::number(num));
    }
    ui->plainTextEdit->setPlainText(numbers.join(','));
}

