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

void MainWindow::on_spinBoxDeleteOrder_valueChanged(int arg1)
{
    ui->spinBoxDeleteOrder->setMaximum(ui->tableWidget->rowCount());
}


void MainWindow::on_pushButtonDeleteOrder_clicked()
{
    if(ui->tableWidget->rowCount() == 0){
        ShowErrorEvent("Таблица пуста, удаление невозможно!");
        return;
    }
    int idx = ui->spinBoxDeleteOrder->value();
    ui->tableWidget->removeRow(idx - 1);
    fileManager.DeleteOrder(idx - 1);
    qDebug() << idx << " deleted from table";

    ui->spinBoxDeleteOrder->setMaximum(ui->tableWidget->rowCount());

}


void MainWindow::on_pushButtonAdd_clicked()
{
    if(ui->lineEditBrand->text().isEmpty()){
        ShowInformationEvent("Заполните модель!");
        return;
    }

    Order newOrder(
        ui->comboBoxGroupName->currentText(),
        ui->lineEditBrand->text(),
        ui->dateEditReceiptDate->date(),
        ui->dateEditCompletionDate->date(),
        ui->checkBoxIsCompleted->isChecked()
        );

    fileManager.AddOrder(newOrder);

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(newOrder.groupName()));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(newOrder.brand()));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(newOrder.receiptDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(newOrder.completionDate().toString("dd.MM.yyyy")));

    QTableWidgetItem* item = new QTableWidgetItem;
    item->setCheckState(newOrder.isCompleted() ? Qt::Checked : Qt::Unchecked);
    item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
    ui->tableWidget->setItem(row, 4, item);


    qDebug() << "Новый элемент " << newOrder.brand() << " добавлен в таблицу";

    ui->spinBoxDeleteOrder->setMaximum(ui->tableWidget->rowCount());
}

