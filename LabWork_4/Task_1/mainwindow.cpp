#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QPainter>

#include "sort.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);

    sortVisualizer = new SortVisualizer(this);
    sortVisualizer->setGeometry(0, 0, width(), height() - ui->groupBox->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    //sortController.RandomNumberVectorGenerate(num);
    sortController.OutputArray();
}


void MainWindow::on_pushButtonSort_clicked(){
    motionVector.clear();
    Sort::QuickSort(arr, 0, arr.size() - 1, motionVector);
    ShowSort();
    OutputArray();
}
