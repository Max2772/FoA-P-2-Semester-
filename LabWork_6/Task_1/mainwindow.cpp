#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "motorcycle.h"
#include <cstring>

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
