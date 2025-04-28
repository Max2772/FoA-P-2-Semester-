#include "solution.h"

#include <QDebug>
#include <QRegularExpression>

Solution::Solution() {}

void Solution::setNameFilters(const QStringList &nameFilters) {
    nameFilters_ = nameFilters;
}

bool Solution::IsValidFilter(QString filter){
    QRegularExpression re("^\\*\\.[a-zA-Z0-9]+$");
    return !filter.isEmpty() && re.match(filter).hasMatch();
}


int Solution::GetNumberOfFoldersAndFiles(const QString &path) {
    QDir dir(path);
    if (!dir.exists()){
        qDebug() << "Папки  по пути " << path << " не существует!";
        return 0;
    }

    int result = CountFilteredFiles(path);
    for (const QFileInfo &info : GetSubfolders(path)) {
        result += GetNumberOfFoldersAndFiles(info.absoluteFilePath());
    }
    return result;
}

int Solution::GetNumberOfFolders(const QString &path) {
    QDir dir(path);
    if (!dir.exists()){
        qDebug() << "Папки  по пути " << path << " не существует!";
        return 0;
    }

    int result = 0;
    QFileInfoList subfolders = GetSubfolders(path);
    for (const QFileInfo &info : subfolders) {
        result++;
        result += GetNumberOfFolders(info.absoluteFilePath());
    }
    return result;
}

int Solution::CountFilteredFiles(const QString &path) {
    return QDir(path).entryList(nameFilters_, QDir::Files).size();
}

QFileInfoList Solution::GetSubfolders(const QString &path) {
    return QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
}
