#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    ui->setupUi(this);

    tree = new AVLTree();
    tree->insert(20);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(25);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(23);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(24);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(12);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(13);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(3);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(0);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(4);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(6);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(34);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(55);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(29);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(17);
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(18);
    while (tree->Parent() != nullptr) tree = tree->Parent();

    PrintTree(tree);
    Update(tree);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButtonInsert_clicked() {
    int value = ui->spinBox->value();
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->insert(value);
    Update(tree);
}


void MainWindow::on_pushButtonContains_clicked() {
    int value = ui->spinBox->value();
    while (tree->Parent() != nullptr) tree = tree->Parent();
        if (tree->contains(value)) {
            QTimer::singleShot(1000, [=]() {
                QPalette palette = ui->pushButtonContains->palette();
                palette.setColor(QPalette::ButtonText, Qt::red);
                ui->pushButtonContains->setPalette(palette);
            });
        } else {
            QTimer::singleShot(1000, [=]() {
                QPalette palette = ui->pushButtonContains->palette();
                palette.setColor(QPalette::ButtonText, Qt::green);
                ui->pushButtonContains->setPalette(palette);
            });
        }
}


void MainWindow::on_pushButtonRemove_clicked() {
    int value = ui->spinBox->value();
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->remove(value);
    Update(tree);
}


void MainWindow::on_pushButtonDoTask_clicked() {
    int value = ui->spinBox->value();
    while (tree->Parent() != nullptr) tree = tree->Parent();
    tree->remove(value);
    Update(tree);

}

QTreeWidgetItem* MainWindow::UpdateTree(AVLTree *tree) {
    QTreeWidgetItem *parent = new QTreeWidgetItem();
    parent->setText(0, QString::number(tree->get()));
    if (tree->Right() != nullptr) {
        parent->addChild(UpdateTree(tree->Right()));
    }
    if (tree->Left() != nullptr) {
        parent->addChild(UpdateTree(tree->Left()));
    }
    return parent;
}

void MainWindow::Update(AVLTree *tree) {
    while (tree->Parent() != nullptr) tree = tree->Parent();
    QTreeWidgetItem *parent = UpdateTree(tree);
    ui->treeWidget->setColumnCount(ui->treeWidget->columnCount() + 1);
    ui->treeWidget->addTopLevelItem(parent);
}

void MainWindow::PrintTree(AVLTree *tree) {
    qDebug() << tree->get() << ' ';
    if (tree->Right() != nullptr)
        PrintTree(tree->Right());
    if (tree->Left() != nullptr)
        PrintTree(tree->Left());
}
