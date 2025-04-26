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

