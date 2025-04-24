#include "filemanager.h"

FileManager::FileManager() {}

bool FileManager::ImportFile()
{
    isFileOpen_ = false;
    filePath_ = QFileDialog::getOpenFileName();

    QFile file(filePath_);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Ошибка при открытии файла для чтения!";
        return false;
    }

    QFileInfo check_file(filePath_);
    if (check_file.suffix() == "txt") {
        isFileOpen_ = true;
        orderVector_ = ImportOrders(filePath_);
        return true;
    }

    qDebug() << "Неверный формат файла!";
    return false;
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
            orderVector.append(order);
        }
    }

    file.close();
    return orderVector;
}
