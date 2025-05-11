#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRandomGenerator>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxElement->setMinimum(MINIMUM_RANDOM_NUMBER);
    ui->spinBoxElement->setMaximum(MAXIMUM_RANDOM_NUMBER);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGenerate_clicked()
{
    GenerateRandomDeque();
    OutputDeque();
}

void MainWindow::GenerateRandomDeque()
{
    d.clear();
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    int size = rand.bounded(MINIMUM_RANDOM_SIZE, MAXIMUM_RANDOM_SIZE);
    for(int i = 0; i < size; ++i){
        d.push_back(rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER));
    }
}

void MainWindow::OutputDeque()
{
    QString result;
    for(int i = 0; i < d.size(); ++i){
        result += QString::number(d.at(i)) + " ";
    }

    ui->plainTextEditDeque->clear();
    ui->plainTextEditDeque->setPlainText(result);
}

void MainWindow::on_pushButtonFront_clicked()
{
    if(d.empty()){
        Utils::ShowInformationEvent("Deque пустой!");
        return;
    }

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(d.front()));
}


void MainWindow::on_pushButtonBack_clicked()
{
    if(d.empty()){
        Utils::ShowInformationEvent("Deque пустой!");
        return;
    }

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(d.back()));
}


void MainWindow::on_pushButtonSize_clicked()
{
    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(d.size()));
}


void MainWindow::on_pushButtonEmpty_clicked()
{
    ui->plainTextEditOutput->clear();
    QString result = d.empty() ? "True" : "False";
    ui->plainTextEditOutput->setPlainText(result);
}


void MainWindow::on_pushButtonPushFront_clicked()
{
    int num = ui->spinBoxElement->value();
    d.push_front(num);

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(num));

    OutputDeque();
}

void MainWindow::on_pushButtonPushBack_clicked()
{
    int num = ui->spinBoxElement->value();
    d.push_back(num);

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(num));

    OutputDeque();
}

void MainWindow::on_pushButtonPopFront_clicked()
{
    int num = ui->spinBoxElement->value();
    d.pop_front();

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(num));

    OutputDeque();
}

void MainWindow::on_pushButtonPopBack_clicked()
{
    int num = ui->spinBoxElement->value();
    d.pop_back();

    ui->plainTextEditOutput->clear();
    ui->plainTextEditOutput->setPlainText(QString::number(num));

    OutputDeque();
}

