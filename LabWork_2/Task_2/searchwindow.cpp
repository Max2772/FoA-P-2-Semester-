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

    connect(ui->lineEditBrand, &QLineEdit::textChanged, this, [this](const QString &text) {
        currentName = text;
        UpdateSearch();
    });
    connect(ui->dateEditReceiptDate, &QDateEdit::dateChanged, this, [this](const QDate &date) {
        currentReceiptDate = date;
        UpdateSearch();
    });
    connect(ui->dateEditCompletionDate, &QDateEdit::dateChanged, this, [this](const QDate &date) {
        currentCompletionDate = date;
        UpdateSearch();
    });
    connect(ui->radioButtonAny, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            currentStatus = "Любое";
            UpdateSearch();
        }
    });
    connect(ui->radioButtonFinished, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            currentStatus = "Готово";
            UpdateSearch();
        }
    });
    connect(ui->radioButtonUnfinished, &QRadioButton::toggled, this, [this](bool checked) {
        if (checked) {
            currentStatus = "Не готово";
            UpdateSearch();
        }
    });
}

SearchWindow::~SearchWindow()
{
    delete ui;
}

void SearchWindow::UpdateSearch()
{
    QVector<Order> filteredOrders;
    for(const Order &order : orderManager->orders()){
        bool match = true;

        if(!order.brand().contains(currentName, Qt::CaseInsensitive) && !currentName.isEmpty())
        {
            match = false;
        }

        if(currentReceiptDate.isValid() && order.receiptDate() != currentReceiptDate){
            match = false;
        }

        if(currentCompletionDate.isValid() && order.completionDate() != currentCompletionDate){
            match = false;
        }

        if(order.isCompleted() && currentStatus == "Не готово"){
            match = false;
        }

        if(!order.isCompleted() && currentStatus == "Готово"){
            match = false;
        }

        if(match){
            filteredOrders.append(order);
        }
    }

    if(filteredOrders.isEmpty()){
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(0);
        Utils::ShowInformationEvent("Заказов не найдено!");
        qDebug() << "Не найдено элементов по параметрам:\n"
                 << "Наименование: " << currentName << '\n'
                 << "Дата поступления: " << currentReceiptDate.toString("dd.MM.yyyy") << '\n'
                 << "Дата исполнения: " << currentCompletionDate.toString("dd.MM.yyyy") << '\n'
                 << "Состояние готовности: " << currentStatus;
        return;
    }

    Utils::FillTable(ui->tableWidget, filteredOrders);
    qDebug() << "Найдено " << filteredOrders.size() << " элементов по параметрам:\n"
             << "Наименование: " << currentName << '\n'
             << "Дата поступления: " << currentReceiptDate.toString("dd.MM.yyyy") << '\n'
             << "Дата исполнения: " << currentCompletionDate.toString("dd.MM.yyyy") << '\n'
             << "Состояние готовности: " << currentStatus;
}
