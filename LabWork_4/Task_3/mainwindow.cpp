#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRandomGenerator>
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
void MainWindow::on_pushButtonAddSize_clicked()
{
    size = ui->spinBoxSize->value();
    qDebug() << "Размер массива = " << size;
    arr.resize(size);
    step = 0;
    DisableUI(true, false);
}

void MainWindow::on_pushButtonAddElement_clicked()
{
    if(step < size){
        arr[step] = ui->spinBoxElement->value();
        ui->plainTextEdit->setPlainText("Массив: " + FormatArray(arr));
        qDebug() << "Элемент " << step+1 << " = " << arr[step];
        step++;

        ui->labelElement->setText(QString("Введите %1 элемент:").arg(step+1));
    }

    if(step == size){
        qDebug() << "Массив на " << size << " элементов инициализирован!";
        step = 0;
        CalculateMedians();
        DisableUI(false, true);
    }

    ui->spinBoxElement->clear();
}


void MainWindow::on_pushButtonDelete_clicked()
{
    arr.clear();
    size = 0, step = 0;
    qDebug() << "Массив удален!";

    EnableUI(true, true);
    ui->labelElement->setText("Введите 1 элемент:");
}


void MainWindow::on_pushButtonAutoFill_clicked()
{
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    if(size == 0 && arr.isEmpty()){
        size = rand.bounded(MIN_SIZE_NUMBER, MAX_SIZE_NUMBER + 1);
        arr.resize(size);
        qDebug() << "Сгенерирован размер массива: " << size;
    }

    for(int i = 0; i < size; ++i){
        arr[i] = rand.bounded(MIN_ELEMENT_NUMBER, MAX_ELEMENT_NUMBER);
        qDebug() << "Элемент " << i+1 << " = " << arr[i];
    }
}

void MainWindow::DisableUI(bool sizeUI, bool elementUI)
{
    if(sizeUI){
        ui->spinBoxSize->setEnabled(false);
        ui->pushButtonAddSize->setEnabled(false);
    }

    if(elementUI){
        ui->pushButtonAutoFill->setEnabled(false);
        ui->pushButtonAddElement->setEnabled(false);
        ui->spinBoxElement->setEnabled(false);
    }
}

void MainWindow::EnableUI(bool sizeUI, bool elementUI)
{
    if(sizeUI){
        ui->spinBoxSize->setEnabled(true);
        ui->pushButtonAddSize->setEnabled(true);
    }

    if(elementUI){
        ui->pushButtonAutoFill->setEnabled(true);
        ui->pushButtonAddElement->setEnabled(true);
        ui->spinBoxElement->setEnabled(true);
    }
}

QString MainWindow::FormatArray(const QVector<long long>& arr)
{
    QStringList arrayString;
    for(long long number : arr){
        arrayString.append(QString::number(number));
    }
    return arrayString.join(',');
}

void MainWindow::CalculateMedians() {
    QVector<long long> result;
    for (int i = 0; i < size; i += 3) {
        if (i + 2 < size) {
            long long a = arr[i], b = arr[i + 1], c = arr[i + 2];
            QVector<long long> triplet = {a, b, c};
            std::sort(triplet.begin(), triplet.end());
            result.push_back(triplet[1]);
        } else if(i + 1 == size){
            result.push_back(arr[i]);
        }else{
            long long average = (arr[i] + arr[i+1]) / 2;
            result.push_back(average);
        }
    }
    ui->plainTextEdit->setPlainText("Массив: " + FormatArray(arr) + "\n\nРезультат: " + FormatArray(result));
}

