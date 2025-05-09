#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <cstring>
#include "utils.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Motorcycle motorcycle1 = {15000, 299.0, 'R', false, "Yamaha YZF-R1"};

    Motorcycle motorcycle2;
    motorcycle2.mileage = 77000;
    motorcycle2.maxSpeed = 246.6;
    motorcycle2.type = 'S';
    motorcycle2.damaged = false;
    strncpy(motorcycle2.modelName, "Yamaha FJR 1300", MAX_MODEL_NAME_CHARACTES);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonAddElement_clicked()
{
    int mileage = ui->spinBoxMileageInfo->value();
    motorcycle5.mileage = mileage;

    double maxSpeed = ui->doubleSpinBoxMaxSpeed->value();
    motorcycle5.maxSpeed = maxSpeed;

    QString selectedType = ui->buttonGroupType->checkedButton()->text();
    if (selectedType == "S - Sport") {
        motorcycle5.type = 'S';
    } else if (selectedType == "C - Cruiser") {
        motorcycle5.type = 'C';
    } else if (selectedType == "T - Touring") {
        motorcycle5.type = 'T';
    } else if (selectedType == "A - Adventure") {
        motorcycle5.type = 'A';
    } else if (selectedType == "D - Dirt") {
        motorcycle5.type = 'D';
    }

    if(ui->radioButtonDamage_Yes->isChecked()){
        motorcycle5.damaged = true;
    }else{
        motorcycle5.damaged = false;
    }

    QString input = ui->plainTextEditModel->toPlainText();
    strncpy(motorcycle5.modelName, input.toUtf8().constData(), MAX_MODEL_NAME_CHARACTES);
    motorcycle5.modelName[MAX_MODEL_NAME_CHARACTES - 1] = '\0';
}

