#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

#include "taskhashtable.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TaskHashTable hashTable;

    // QRandomGenerator rand(QRandomGenerator::system()->generate());
    // for (int i = 0; i < 30; ++i) {
    //     int key = rand.bounded(MIN_RANDOM_KEY, MAX_RANDOM_KEY);
    //     int value = rand.bounded(MIN_RANDOM_VALUE, MAX_RANDOM_VALUE);
    //     hashTable.insert(key, value);
    // }

    // std::cout << "Исходная хэш-таблица: " << std::endl;
    // hashTable.print();

    // hashTable.RemoveNegativeKeys();

    // std::cout << "\nHash table after removing negative keys:" << std::endl;
    // hashTable.print();
}


MainWindow::~MainWindow()
{
    delete ui;
}
