#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

void MainWindow::ShowErrorEvent(QString information) {
    QMessageBox box;
    box.setWindowTitle("Ошибка");
    box.setText(information);
    box.setIcon(QMessageBox::Critical);
    box.exec();
}

void MainWindow::ShowInformationEvent(QString information) {
    QMessageBox box;
    box.setWindowTitle("Информационная панель");
    box.setIcon(QMessageBox::Information);
    box.setText(information);
    box.exec();
}

void MainWindow::on_pushButtonImport_clicked()
{
    if(!fileManager.ImportFile()){
        ShowErrorEvent("Ошибка при импортировании!");
        return;
    }

    FillTable(fileManager.orders());
}

void MainWindow::FillTable(const QVector<Order> &orderVector)
{
    if(orderVector.size() == 0)
        ShowErrorEvent("Пустой список!");

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(orderVector.size());

    for(int i = 0; i < orderVector.size(); ++i){
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(orderVector[i].groupName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(orderVector[i].brand()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(orderVector[i].receiptDate().toString("dd.MM.yyyy")));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(orderVector[i].completionDate().toString("dd.MM.yyyy")));

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setCheckState(orderVector[i].isCompleted() ? Qt::Checked : Qt::Unchecked);
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        ui->tableWidget->setItem(i, 4, item);
    }

}
