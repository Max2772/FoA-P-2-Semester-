#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "filemanager.h"
#include <QDate>

class OrderManager
{
public:
    OrderManager();
    QVector<Order> orders() const { return orderVector_; }

    void LoadOrders(const QString &filePath);
    bool SaveOrders();
    void ClearOrders();

    QVector<Order> ShowReadyTodayOrders(const QString &groupName);
    QVector<Order> ShowUnfinishedOrders();

    QVector<Order> SortOrdersDescending();
    QVector<Order> SortOrdersAscending();

    // Methods for SearchWindow
    QVector<Order> SearchWindowFinishedOrders();
    QVector<Order> SearchWindowUnfinishedOrders();

    void DeleteOrder(const int &idx);
    void AddOrder(const Order &order);
    void EditOrder(const Order &order, const int &idx);
private:
    QVector <Order> orderVector_;
};

#endif // ORDERMANAGER_H
