#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <cstring>
#include <QDebug>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(5);

    motorcycles[0] = {15000, 299.0, 'R', true, "Yamaha YZF-R1"};

    motorcycles[1].mileage = 77000;
    motorcycles[1].maxSpeed = 246.6;
    motorcycles[1].type = 'S';
    motorcycles[1].damaged = false;
    strncpy(motorcycles[1].modelName, "Yamaha FJR 1300", MAX_MODEL_NAME_CHARACTES);

    motorcycles[2].mileage = 100000;
    motorcycles[2].maxSpeed = 180.0;
    motorcycles[2].type = 'T';
    motorcycles[2].damaged = true;
    strncpy(motorcycles[2].modelName, "Honda Gold Wing", MAX_MODEL_NAME_CHARACTES);

    motorcycles[3].mileage = 25000;
    motorcycles[3].maxSpeed = 200.0;
    motorcycles[3].type = 'A';
    motorcycles[3].damaged = false;
    strncpy(motorcycles[3].modelName, "BMW R 1250 GS", MAX_MODEL_NAME_CHARACTES);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAddElement_clicked()
{
    int mileage = ui->spinBoxMileageInfo->value();
    if(mileage == 0){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }
    motorcycles[4].mileage = mileage;

    double maxSpeed = ui->doubleSpinBoxMaxSpeed->value();
    if(maxSpeed == 0){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }
    motorcycles[4].maxSpeed = maxSpeed;

    QString selectedType = ui->buttonGroupType->checkedButton()->text();
    if (selectedType == "S - Sport") {
        motorcycles[4].type = 'S';
    } else if (selectedType == "C - Cruiser") {
        motorcycles[4].type = 'C';
    } else if (selectedType == "T - Touring") {
        motorcycles[4].type = 'T';
    } else if (selectedType == "A - Adventure") {
        motorcycles[4].type = 'A';
    } else if (selectedType == "D - Dirt") {
        motorcycles[4].type = 'D';
    }else{
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    if(ui->radioButtonDamage_Yes->isChecked()){
        motorcycles[4].damaged = true;
    }else if(ui->radioButtonDamage_No->isChecked()){
        motorcycles[4].damaged = false;
    }else{
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }

    QString input = ui->plainTextEditModel->toPlainText();
    if(input.isEmpty()){
        Utils::ShowInformationEvent("Заполните все данные!");
        return;
    }
    strncpy(motorcycles[4].modelName, input.toUtf8().constData(), MAX_MODEL_NAME_CHARACTES);
    motorcycles[4].modelName[MAX_MODEL_NAME_CHARACTES - 1] = '\0';

    FillTable();
}

void MainWindow::FillTable()
{
    for(int i = 0; i < 5; ++i){
        qDebug() << motorcycles[i].Print();
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(motorcycles[i].modelName));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(motorcycles[i].mileage)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(motorcycles[i].maxSpeed)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString(motorcycles[i].type)));

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setCheckState((motorcycles[i].damaged ? Qt::Checked : Qt::Unchecked));
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        ui->tableWidget->setItem(i, 4, item);
    }
}

