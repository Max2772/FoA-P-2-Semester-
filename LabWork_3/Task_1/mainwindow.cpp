#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

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

void MainWindow::on_doubleSpinBoxInput_valueChanged(double inputNum)
{
    if(inputNum == 0){
        ui->labelOutput->setText("0");
        return;
    }

    bool negative = inputNum < 0 ? true : false;
    inputNum = inputNum < 0 ? -inputNum : inputNum;

    long long integerNum = static_cast<long long>(inputNum);
    double fractionNum = inputNum - integerNum;

    QString integerBinaryString = solution.IntegerToBinary(integerNum);
    QString fractalBinaryString = solution.FractionalToBinary(fractionNum, 64);

    ui->labelOutput->setText((negative ? "-" : "") + solution.FormatNumber(integerBinaryString, fractalBinaryString));
}

