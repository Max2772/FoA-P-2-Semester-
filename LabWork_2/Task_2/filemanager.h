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
    bool ImportFile(const QString &filePath);
    bool SaveFile(const QVector <Order> &orderVector);
    bool CloseFile();
    QVector <Order> ImportOrders(const QString &filePath);
private:
    bool isFileOpen_;
    QString filePath_;
};

#endif // FILEMANAGER_H
