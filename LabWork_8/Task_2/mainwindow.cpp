#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QVector>
#include <QRandomGenerator>
#include "heap.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    Heap heap;
    std::cout << "=== Тестируем insert (shiftUp) ===\n";
    QVector<int> values = CreateRandomArray();
    for (int val : values) {
        heap.insert(val);
        heap.printHeap();
    }

    std::cout << "\n=== Тестируем extractMin (shiftDown) ===\n";
    while (heap.getSize() > 0) {
        int min = heap.extractMin();
        std::cout << "После извлечения " << min << ": ";
        heap.printHeap();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector<int> MainWindow::CreateRandomArray()
{
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    QVector<int> arr;
    int size = rand.bounded(MIN_SIZE, MAX_SIZE);
    for(int i = 0; i < size; ++i){
        int num = rand.bounded(MIN_NUM, MAX_NUM);
        while(arr.contains(num)){
            num = rand.bounded(MIN_NUM, MAX_NUM);
        }
        arr.push_back(num);
    }
    return arr;
}
