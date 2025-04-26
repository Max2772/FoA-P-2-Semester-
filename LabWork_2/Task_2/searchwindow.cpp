#include "searchwindow.h"
#include "ui_searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchWindow)
{
    ui->setupUi(this);

    Utils::FillTable(ui->tableWidget, orderManager.orders());
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

