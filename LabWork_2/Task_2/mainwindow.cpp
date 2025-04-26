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

void MainWindow::on_pushButtonImport_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)", nullptr, QFileDialog::DontUseNativeDialog);

    if(!fileManager.ImportFile(filePath)){
        Utils::ShowErrorEvent("Ошибка при импортировании!");
        return;
    }

    orderManager.LoadOrders(filePath);

    Utils::FillTable(ui->tableWidget, orderManager.orders());
    SetSpinBoxesLimits();
}

void MainWindow::SetSpinBoxesLimits()
{
    ui->spinBoxDeleteOrder->setMaximum(ui->tableWidget->rowCount());
    ui->spinBoxEditOrder->setMaximum(ui->tableWidget->rowCount());

    ui->spinBoxEditOrder->setMinimum(1);
    ui->spinBoxDeleteOrder->setMinimum(1);
}

void MainWindow::on_pushButtonDeleteOrder_clicked()
{
    if(ui->tableWidget->rowCount() == 0){
        Utils::ShowErrorEvent("Таблица пуста, удаление невозможно!");
        return;
    }
    int idx = ui->spinBoxDeleteOrder->value();
    ui->tableWidget->removeRow(idx - 1);
    orderManager.DeleteOrder(idx - 1);
    qDebug() << idx << " deleted from table";

    SetSpinBoxesLimits();
}


void MainWindow::on_pushButtonAdd_clicked()
{
    if(ui->lineEditBrand->text().isEmpty()){
        Utils::ShowInformationEvent("Заполните модель!");
        return;
    }

    Order newOrder(
        ui->comboBoxGroupName->currentText(),
        ui->lineEditBrand->text(),
        ui->dateEditReceiptDate->date(),
        ui->dateEditCompletionDate->date(),
        ui->checkBoxIsCompleted->isChecked()
        );

    orderManager.AddOrder(newOrder);

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    Utils::AddElementToTable(ui->tableWidget, newOrder, row);


    qDebug() << "Новый элемент " << newOrder.brand() << " добавлен в таблицу";

    SetSpinBoxesLimits();
}


void MainWindow::on_pushButtonSave_clicked()
{
    if(!orderManager.SaveOrders()){
        Utils::ShowErrorEvent("Ошибка при сохранении файла!");
        return;
    }

    Utils::ShowInformationEvent("Файл сохранен!");
}


void MainWindow::on_pushButtonClose_clicked()
{
    if(!fileManager.CloseFile()){
        Utils::ShowErrorEvent("Ошибка при закрытии файла!");
        return;
    }

    orderManager.ClearOrders();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    Utils::ShowInformationEvent("Файл закрыт!");

    SetSpinBoxesLimits();
}


void MainWindow::on_pushButtonEdit_clicked()
{
    if(ui->lineEditBrand->text().isEmpty()){
        Utils::ShowInformationEvent("Заполните модель!");
        return;
    }

    Order editedOrder(
        ui->comboBoxGroupName->currentText(),
        ui->lineEditBrand->text(),
        ui->dateEditReceiptDate->date(),
        ui->dateEditCompletionDate->date(),
        ui->checkBoxIsCompleted->isChecked()
        );

    int row = ui->spinBoxEditOrder->value();
    orderManager.EditOrder(editedOrder, row - 1);
    Utils::AddElementToTable(ui->tableWidget, editedOrder, row - 1);

    qDebug() << "Элемент " << editedOrder.brand() << " заменил " << row << " строку" ;

}

void MainWindow::on_radioButtonReadyOrders_toggled(bool checked)
{
    if(checked){
        ui->radioButtonUnfinishedOrders->setChecked(false);

        QString groupName = ui->comboBoxGroupNameReadyOrders->currentText();
        QVector<Order> readyOrders = orderManager.ShowReadyTodayOrders(groupName);

        Utils::FillTable(ui->tableWidget, readyOrders);
        qDebug() << "Выполненные заказы из группы " << groupName;
    }else{
        Utils::FillTable(ui->tableWidget, orderManager.orders());
        qDebug() << "Весь список!";
    }
}


void MainWindow::on_radioButtonUnfinishedOrders_toggled(bool checked)
{
    if(checked){
        ui->radioButtonReadyOrders->setChecked(false);

        QVector<Order> unfinishedOrders = orderManager.ShowUnfinishedOrders();
        Utils::FillTable(ui->tableWidget, unfinishedOrders);

        qDebug() << "Заказы невыполненные в срок!";
    }else{
        Utils::FillTable(ui->tableWidget, orderManager.orders());
        qDebug() << "Весь список!";
    }
}


void MainWindow::on_comboBoxGroupNameReadyOrders_currentIndexChanged(int index)
{
    if(ui->radioButtonReadyOrders->isChecked()){
        QString groupName = ui->comboBoxGroupNameReadyOrders->currentText();
        QVector<Order> readyOrders = orderManager.ShowReadyTodayOrders(groupName);

        Utils::FillTable(ui->tableWidget, readyOrders);
        qDebug() << "Выполненные заказы из группы " << groupName;
    }
}



void MainWindow::on_comboBoxGroupNameSort_currentTextChanged(const QString &choice)
{
    if(choice == "По дате добавления"){
        Utils::FillTable(ui->tableWidget, orderManager.orders());
        qDebug() << "Список по дате добавления!";
    }else if(choice == "По убыванию даты исполнения"){
        QVector<Order> descendingOrders = orderManager.SortOrdersDescending();

        Utils::FillTable(ui->tableWidget, descendingOrders);
        qDebug() << "Заказы по убыванию даты исполнения";
    }else{
        QVector<Order> ascendingOrders = orderManager.SortOrdersAscending();

        Utils::FillTable(ui->tableWidget, ascendingOrders);
        qDebug() << "Заказы по возврастанию даты исполнения";
    }
}


void MainWindow::on_pushButtonSearch_clicked()
{
    SearchWindow *searchWindow = new SearchWindow(this);
    searchWindow->exec();
}

