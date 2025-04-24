#include "order.h"

Order::Order(QString groupName, QString brand, QDate receiptDate,
             QDate completionDate, bool isCompleted){
    groupName_ = groupName;
    brand_ = brand;
    receiptDate_ = receiptDate;
    completionDate_ = completionDate;
    isCompleted_ = isCompleted;
}
