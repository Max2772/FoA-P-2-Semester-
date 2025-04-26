#ifndef UTILS_H
#define UTILS_H

#include <QTableWidget>
#include <QMessageBox>
#include "order.h"

namespace Utils{

    static void ShowErrorEvent(QString information) {
        QMessageBox box;
        box.setWindowTitle("Ошибка");
        box.setText(information);
        box.setIcon(QMessageBox::Critical);
        box.exec();
    }

    static void ShowInformationEvent(QString information) {
        QMessageBox box;
        box.setWindowTitle("Информационная панель");
        box.setIcon(QMessageBox::Information);
        box.setText(information);
        box.exec();
    }

    static void AddElementToTable(QTableWidget *tableWidget, const Order &order, const int &idx)
    {
        tableWidget->setItem(idx, 0, new QTableWidgetItem(order.groupName()));
        tableWidget->setItem(idx, 1, new QTableWidgetItem(order.brand()));
        tableWidget->setItem(idx, 2, new QTableWidgetItem(order.receiptDate().toString("dd.MM.yyyy")));
        tableWidget->setItem(idx, 3, new QTableWidgetItem(order.completionDate().toString("dd.MM.yyyy")));

        QTableWidgetItem* item = new QTableWidgetItem;
        item->setCheckState(order.isCompleted() ? Qt::Checked : Qt::Unchecked);
        item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
        tableWidget->setItem(idx, 4, item);
    }

    static void FillTable(QTableWidget *tableWidget, const QVector<Order> &orderVector)
    {
        if(orderVector.size() == 0){
            ShowErrorEvent("Пустой список!");
            return;
        }

        tableWidget->clearContents();
        tableWidget->setRowCount(orderVector.size());

        for(int i = 0; i < orderVector.size(); ++i){
            AddElementToTable(tableWidget, orderVector[i], i);
        }
    }


}

#endif // UTILS_H
