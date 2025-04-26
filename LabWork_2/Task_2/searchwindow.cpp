#include "searchwindow.h"
#include "ui_searchwindow.h"
#include "utils.h"

SearchWindow::SearchWindow(OrderManager *manager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow),
    orderManager(manager)
{
    ui->setupUi(this);
    Utils::FillTable(ui->tableWidget, orderManager->orders());
}

SearchWindow::~SearchWindow()
{
    delete ui;
}


void SearchWindow::on_radioButtonAny_clicked()
{
    if(ui->radioButtonAny->isChecked()){
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        qDebug() << "Любые заказы по готовности (SearchWindow)";
    }
}


void SearchWindow::on_radioButtonFinished_clicked()
{
    if(ui->radioButtonFinished->isChecked()){
        QVector<Order> finishedOrders = orderManager->SearchWindowFinishedOrders();

        Utils::FillTable(ui->tableWidget, finishedOrders);
        qDebug() << "Выполненные заказы (SearchWindow)";
    }
}


void SearchWindow::on_radioButtonUnfinished_clicked()
{
    if(ui->radioButtonUnfinished->isChecked()){
        QVector<Order> unfinishedOrders = orderManager->SearchWindowUnfinishedOrders();

        Utils::FillTable(ui->tableWidget, unfinishedOrders);
        qDebug() << "Невыполненные заказы (SearchWindow)";
    }
}


void SearchWindow::on_lineEditBrand_textEdited(const QString &text)
{
    if(text.isEmpty()){
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        return;
    }

    QVector<Order> filteredOrders;
    for(const Order &order : orderManager->orders()){
        if(order.brand().contains(text, Qt::CaseInsensitive)){
            filteredOrders.append(order);
        }
    }

    if(filteredOrders.isEmpty()){
        qDebug() <<  "Элементов не найдено по наименованию: " << text;
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        return;
    }

    Utils::FillTable(ui->tableWidget, filteredOrders);
    qDebug() << "Поиск по наименованию: " << text
             << '\n' << "Найдено " << filteredOrders.size() << " элементов";
}


void SearchWindow::on_dateEditReceiptDate_dateChanged(const QDate &date)
{
    if(!date.isValid()){
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        return;
    }

    QVector<Order> filteredOrders;
    for(const Order &order : orderManager->orders()){
        if(order.receiptDate() == date){
            filteredOrders.append(order);
        }
    }

    if(filteredOrders.isEmpty()){
        qDebug() <<  "Элементов не найдено по дате поступления: " << date.toString("dd.MM.yyyy");
        Utils::ShowInformationEvent("Не найдено заказов по дате поступления:\n" + date.toString("dd.MM.yyyy"));
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        return;
    }

    Utils::FillTable(ui->tableWidget, filteredOrders);
    qDebug() << "Поиск по дате поступления: " << date.toString("dd.MM.yyyy")
             << '\n' << "Найдено " << filteredOrders.size() << " элементов";
}


void SearchWindow::on_dateEditCompletionDate_dateChanged(const QDate &date)
{
    if(!date.isValid()){
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        return;
    }

    QVector<Order> filteredOrders;
    for(const Order &order : orderManager->orders()){
        if(order.completionDate() == date){
            filteredOrders.append(order);
        }
    }

    if(filteredOrders.isEmpty()){
        qDebug() <<  "Элементов не найдено по дате исполнения: " << date.toString("dd.MM.yyyy");
        Utils::ShowInformationEvent("Не найдено заказов по дате исполнения:\n" + date.toString("dd.MM.yyyy"));
        Utils::FillTable(ui->tableWidget, orderManager->orders());
        return;
    }

    Utils::FillTable(ui->tableWidget, filteredOrders);
    qDebug() << "Поиск по дате исполнения: " << date.toString("dd.MM.yyyy")
             << '\n' << "Найдено " << filteredOrders.size() << " элементов";
}
