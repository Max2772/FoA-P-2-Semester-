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
    ui->plainTextEditOutput->setPlainText(nullptr);
    solution.ResetLine();

    int input = ui->spinBoxInput->value();
    QString output = solution.Hanoi(input, "A", "B", "C");
    ui->plainTextEditOutput->setPlainText(output);
}

