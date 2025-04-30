#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);

    sortVisualizer = new SortVisualizer(this);
    sortVisualizer->setGeometry(0, 0, width() / 2, height() - ui->groupBox->height());
    sortVisualizer->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    sortController.CreateNewArr(num);
}


void MainWindow::on_pushButtonSort_clicked(){
    sortController.QuickSort();
    qDebug() << "Quick Sort in action";
}
