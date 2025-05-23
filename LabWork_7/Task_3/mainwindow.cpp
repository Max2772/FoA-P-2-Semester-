#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hashTable = new TaskHashTable;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonGenerate_clicked()
{
    ui->plainTextEdit->clear();

    QRandomGenerator rand(QRandomGenerator::system()->generate());
    for (int i = 0; i < 30; ++i) {
        int key = rand.bounded(MIN_RANDOM_KEY, MAX_RANDOM_KEY);
        int value = rand.bounded(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE);
        hashTable->insert(key, value);
    }

    QString output = "Исходная хэш-таблица:\n";
    output += hashTable->print();
    ui->plainTextEdit->setPlainText(output);
}


void MainWindow::on_pushButtonDoTask_clicked()
{
    QString output;
    hashTable->RemoveNegativeKeys();
    output += QString("\nХэш-таблица после удаления отрицательных ключей:\n");
    output += hashTable->print();
    ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText() + output);
}

