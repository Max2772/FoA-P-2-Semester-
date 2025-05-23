#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);

    tree = new AVLTree();
    root = tree;
    CreateRandomAVLTree();

    PrintTree(root);
    Update();
}

MainWindow::~MainWindow() {
    delete ui;
    delete tree;
}

void MainWindow::CreateRandomAVLTree()
{
    root->clear();
    QRandomGenerator rand(QRandomGenerator::system()->generate());
    int size = rand.bounded(MINIMUM_RANDOM_SIZE, MAXIMUM_RANDOM_SIZE);
    for(int i = 0; i < size; ++i){
        root->insert(rand.bounded(MINIMUM_RANDOM_NUMBER, MAXIMUM_RANDOM_NUMBER));
    }
}

void MainWindow::on_pushButtonInsert_clicked() {
    int value = ui->spinBox->value();
    root->insert(value);
    Update();
}


void MainWindow::on_pushButtonContains_clicked() {
    int value = ui->spinBox->value();
    if (root->contains(value)) {
        ui->pushButtonContains->setStyleSheet("QPushButton { color: green; }");
        QTimer::singleShot(600, [=]() {
            ui->pushButtonContains->setStyleSheet("");
        });
    } else {
        ui->pushButtonContains->setStyleSheet("QPushButton { color: red; }");
        QTimer::singleShot(600, [=]() {
            ui->pushButtonContains->setStyleSheet("");
        });
    }
}


void MainWindow::on_pushButtonRemove_clicked() {
    int value = ui->spinBox->value();
    root->remove(value);
    Update();
}


void MainWindow::on_pushButtonDoTask_clicked() {
    int value = ui->spinBox->value();
    root->remove(value);
    Update();

}

QTreeWidgetItem* MainWindow::UpdateTree(AVLTree *tree) {
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, QString::number(tree->get()));
    if (tree->Right() != nullptr) {
        item->addChild(UpdateTree(tree->Right()));
    }
    if (tree->Left() != nullptr) {
        item->addChild(UpdateTree(tree->Left()));
    }
    return item;
}

void MainWindow::Update() {
    ui->treeWidget->clear();
    if (root != nullptr) {
        QTreeWidgetItem *parent = UpdateTree(root);
        ui->treeWidget->addTopLevelItem(parent);
    }
}

void MainWindow::PrintTree(AVLTree *tree) {
    if(tree == nullptr) return;
    qDebug() << tree->get() << ' ';
    if (tree->Right() != nullptr)
        PrintTree(tree->Right());
    if (tree->Left() != nullptr)
        PrintTree(tree->Left());
}

void MainWindow::on_pushButtonGenerate_clicked()
{
    CreateRandomAVLTree();
    qDebug() << "Generated new ATL Tree:";
    PrintTree(root);
    Update();
}

