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
    sortVisualizer->setGeometry(0, 0, width(), height() - ui->groupBox->height());

    sortController = new SortController(sortVisualizer, this);

    connect(sortController, &SortController::sortingStateChanged,
            this, &MainWindow::onSortingStateChanged);

    connect(sortController, &SortController::sortTimeUpdated,
            this, &MainWindow::onSortTimeUpdated);
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
    QString input = ui->comboBoxSortType->currentText();
    if(input == "Quick Sort"){
        sortController->Sort(SortController::SortType::QuickSort);
        return;
    }else if(input == "Heap Sort"){
        sortController->Sort(SortController::SortType::HeapSort);
        return;
    }else if(input == "Merge Sort"){
        sortController->Sort(SortController::SortType::MergeSort);
        return;
    }

    qDebug() << "Ошибка в comboBoxSortType!";
    return;
}


void MainWindow::on_comboBoxSortType_currentTextChanged(const QString &text)
{
    qDebug() << "Выбрана сортировка: " << text;
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

void MainWindow::onSortTimeUpdated(qint64 timeResult)
{
    ui->labelWastedTime->setText(QString("Затраченное время: %1 мс").arg(timeResult));
    qDebug() << "Затраченное время: " << timeResult;
}

