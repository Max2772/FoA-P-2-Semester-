#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    int m = ui->spinBoxFirstNumber->value();
    int n = ui->spinBoxSecondNumber->value();
    int result = solution.Ackermann(m, n);
    ui->labelResult->setText(QString(result));
}

