#include "ordermanager.h"

OrderManager::OrderManager() {}

void OrderManager::LoadOrders(const QString &filePath)
{
    FileManager fileManager;
    orderVector_ = fileManager.ImportOrders(filePath);

    qDebug() << "Данные загружены в OrderManager!";
}

bool OrderManager::SaveOrders()
{
    FileManager fileManager;
    if(!fileManager.SaveFile(orderVector_)){
        qDebug() << "Ошибка при сохранении в FileManager";
        return false;
    }

    return true;
}

void OrderManager::ClearOrders()
{
    orderVector_.clear();
}

QVector<Order> OrderManager::ShowReadyTodayOrders(const QString &groupName)
{
    QDate currentDate = QDate::currentDate();
    QVector<Order> readyOrdersVector;

    for(int i = 0; i < orderVector_.size(); ++i){
        if(orderVector_[i].groupName() == groupName &&
            orderVector_[i].completionDate() <= currentDate)
            readyOrdersVector.append(orderVector_[i]);
    }

    return readyOrdersVector;
}

QVector<Order> OrderManager::ShowUnfinishedOrders()
{
    QDate currentDate = QDate::currentDate();
    QVector<Order> unfinishedOrdersVector;

    for(int i = 0; i < orderVector_.size(); ++i){
        if(orderVector_[i].completionDate() <= currentDate
            && !(orderVector_[i].isCompleted()))
            unfinishedOrdersVector.append(orderVector_[i]);
    }

    return unfinishedOrdersVector;
}

void OrderManager::DeleteOrder(const int &idx)
{
    orderVector_.remove(idx);
}

void OrderManager::AddOrder(const Order &order)
{
    orderVector_.append(order);
}

void OrderManager::EditOrder(const Order &order, const int &idx)
{
    orderVector_[idx] = order;
}
