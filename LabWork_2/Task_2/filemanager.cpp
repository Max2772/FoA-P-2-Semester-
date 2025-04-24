#include "filemanager.h"

FileManager::FileManager() {}

bool FileManager::ImportFile(const QString &filePath)
{
    isFileOpen_ = false;
    filePath_ = filePath;

    QFile file(filePath_);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Ошибка при открытии файла для чтения!";
        return false;
    }

    QFileInfo checkFile(filePath_);
    if (checkFile.suffix() == "txt") {
        isFileOpen_ = true;
        orderVector_ = ImportOrders(filePath_);
        return true;
    }

    qDebug() << "Неверный формат файла!";
    return false;
}

bool FileManager::SaveFile()
{
    if(!isFileOpen_){
        qDebug("Ни один файл не открыт");
        return false;
    }

    QFile file(filePath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Ошибки при открытии файла для записи";
        return false;
    }

    QTextStream out(&file);
    for(const Order &order : orderVector_){
        out << order.groupName() << ';'
            << order.brand() << ';'
            << order.receiptDate().toString("dd.MM.yyyy") << ';'
            << order.completionDate().toString("dd.MM.yyyy") << ';'
            << (order.isCompleted() ? QStringLiteral("Готово") : QStringLiteral("Не готово")) << "\n";
    }

    qDebug() << "Сохранение в " << filePath_ << " успешно!";

    file.close();
    return true;
}

bool FileManager::CloseFile()
{
    if(!isFileOpen_){
        qDebug() << "Нету открытого файла!";
        return false;
    }

    isFileOpen_ = false;
    filePath_ = nullptr;
    orderVector_.clear();
    qDebug() << "Файл закрыт!";
    return true;
}

QVector<Order> FileManager::ImportOrders(const QString &filePath)
{
    QVector<Order> orderVector;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return orderVector;
    }

    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(';');
        if(parts.size() == 5){
            Order order(parts[0],
                        parts[1],
                        QDate::fromString(parts[2], "dd.MM.yyyy"),
                        QDate::fromString(parts[3], "dd.MM.yyyy"),
                        parts[4].trimmed() == "Готово");
            qDebug() << order.groupName() << order.isCompleted();
            orderVector.append(order);
        }
    }

    file.close();
    return orderVector;
}

void FileManager::DeleteOrder(const int &idx)
{
    orderVector_.remove(idx);
}

void FileManager::AddOrder(const Order &order)
{
    orderVector_.append(order);
}

void FileManager::EditOrder(const Order &order, const int &idx)
{
    orderVector_[idx] = order;
}
