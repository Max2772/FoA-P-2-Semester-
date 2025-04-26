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

