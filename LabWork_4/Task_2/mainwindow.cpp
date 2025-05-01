#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxAmount->blockSignals(true);
    ui->spinBoxSearchElement->blockSignals(true);
    ui->spinBoxAmount->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxAmount->setMaximum(SPINBOX_MAX_VALUE);
    ui->spinBoxSearchElement->setMinimum(SPINBOX_MIN_VALUE);
    ui->spinBoxSearchElement->setMaximum(SPINBOX_MAX_VALUE);
    ui->spinBoxAmount->blockSignals(false);
    ui->spinBoxSearchElement->blockSignals(true);

    sortVisualizer = new SortVisualizer(this);
    sortVisualizer->setGeometry(0, 0, width(), height() - ui->groupBox->height());

    sortController = new SortController(sortVisualizer, this);

    connect(sortController, &SortController::sortingStateChanged,
            this, &MainWindow::onSortingStateChanged);

    connect(sortController, &SortController::searchStateChanged,
            this, &MainWindow::onSearchStateChanged);

    connect(sortController, &SortController::searchResult,
            this, &MainWindow::onSearchResult);
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
    sortController->Sort();
}

void MainWindow::on_pushButtonShuffle_clicked()
{
    int size = ui->spinBoxAmount->value();
    sortController->CreateNewArr(size);
    qDebug() << "Массив перемешан";
}

void MainWindow::onSortingStateChanged(bool isSorting)
{
    ui->groupBox->setEnabled(!isSorting);
    qDebug() << "UI " << (isSorting ? "заблокирован" : "разблокирован");
}

void MainWindow::onSearchStateChanged(bool isSearching)
{
    ui->groupBox->setEnabled(!isSearching);
    qDebug() << "UI " << (isSearching ? "заблокирован" : "разблокирован");
}

void MainWindow::onSearchResult(int idx, long long result)
{
    if(idx == -1){
        ui->labelIndexOfElement->setText(QString("Индекс элемента: NaN"));
        qDebug() << "Элемент не найден в массиве";
        return;
    }

    ui->labelIndexPowLength->setText(QString("Индекс ^ Длина: %1").arg(result));
    ui->labelIndexOfElement->setText(QString("Индекс элемента: %1").arg(idx));
    qDebug() << "Элемент найден под индексом " << idx;
}

void MainWindow::on_pushButtonFindElement_clicked()
{
    int element = ui->spinBoxSearchElement->value();
    qDebug() << "Бинарынй поиск элемента " << element;
    sortController->BinarySearch(element);
}

