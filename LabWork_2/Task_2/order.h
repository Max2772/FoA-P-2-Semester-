#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDate>

class Order
{
public:
    Order(QString groupName, QString brand, QDate receiptDate, QDate completionDate, bool isCompleted);

    QString groupName() const { return groupName_;}
    QString brand() const { return brand_; }
    QDate receiptDate() const { return receiptDate_; }
    QDate completionDate() const { return completionDate_; }
    bool isCompleted() const { return isCompleted_; }

private:
    QString groupName_;
    QString brand_;
    QDate receiptDate_;
    QDate completionDate_;
    bool isCompleted_;
};

#endif // ORDER_H
