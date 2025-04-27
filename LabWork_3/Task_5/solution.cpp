#include "solution.h"
#include <QDebug>

Solution::Solution() {
    nameFilter << "*.cpp    ";
}

int Solution::GetNumberOfFoldersAndFiles(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) return 0;

    int result = CountFilteredFiles(path); // Считаем .txt файлы в текущей папке
    for (const QFileInfo &info : GetSubfolders(path)) {
        result += GetNumberOfFoldersAndFiles(info.absoluteFilePath());
    }
    return result;
}

int Solution::GetNumberOfFolders(const QString &path) {
    QDir dir(path);
    if (!dir.exists()) return 0;

    int result = 0;
    QFileInfoList subfolders = GetSubfolders(path);
    for (const QFileInfo &info : subfolders) {
        result++; // Учитываем текущую подпапку
        result += GetNumberOfFolders(info.absoluteFilePath());
    }
    return result;
}

int Solution::CountFilteredFiles(const QString &path) {
    return QDir(path).entryList(nameFilter, QDir::Files).size();
}

QFileInfoList Solution::GetSubfolders(const QString &path) {
    return QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
}
