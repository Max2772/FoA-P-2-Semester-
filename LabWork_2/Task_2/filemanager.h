#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QVector>

#include "order.h"

class FileManager
{
public:
    FileManager();
    QVector<Order> orders() const { return orderVector_; }

    bool ImportFile();
    QVector <Order> ImportOrders(const QString &filePath);
    void DeleteOrder(const int &idx);
    void AddOrder(const Order &order);
private:
    bool isFileOpen_;
    QString filePath_;
    QVector <Order> orderVector_;
};

#endif // FILEMANAGER_H
