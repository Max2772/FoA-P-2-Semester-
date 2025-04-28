#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "sort.h"

#include <QRandomGenerator>
#include <QTime>

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

void MainWindow::RandomNumberVectorGenerate()
{
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    QVector<int> randomNumbers;
    int size = ui->spinBoxAmount->value();

    for(int i = 0; i < size; ++i){
        int randomNum = rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER);
        while(randomNumbers.contains(randomNum)){
            randomNum = rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER);
        }
        randomNumbers.append(randomNum);
    }
    arr = randomNumbers;
}

void MainWindow::on_spinBoxAmount_valueChanged(int num)
{
    RandomNumberVectorGenerate();
    QString res;
    for(int i = 0; i < arr.size(); ++i){
        res += QString::number(arr[i]) + ", ";
    }
    ui->plainTextEdit->setPlainText(res);
}


void MainWindow::on_pushButtonSort_clicked()
{
    RandomNumberVectorGenerate();
    Sort::HeapSort(arr);
    QString res;
    for(int i = 0; i < arr.size(); ++i){
        res += QString::number(arr[i]) + ", ";
    }
    ui->plainTextEdit->setPlainText(res);
}

