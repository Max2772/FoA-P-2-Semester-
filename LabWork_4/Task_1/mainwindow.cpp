#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->blockSignals(true);
    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);
    ui->spinBoxAmount->blockSignals(false);

    sortVisualizer = new SortVisualizer(this);
    sortVisualizer->setGeometry(0, 0, width() / 2, height() - ui->groupBox->height());
    qDebug() << sortVisualizer->height() << " height px";
    qDebug() << sortVisualizer->width() << " width px";
    sortVisualizer->setStyleSheet("background-color: red;");
    sortVisualizer->raise();
    sortVisualizer->show();

    sortController = new SortController(sortVisualizer, this);

    qDebug() << "SortVisualizer visible:" << sortVisualizer->isVisible();
    qDebug() << "SortVisualizer geometry:" << sortVisualizer->geometry();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    sortController->CreateNewArr(num);
}


void MainWindow::on_pushButtonSort_clicked(){
    sortController->QuickSort();
    qDebug() << "Quick Sort in action";
}
