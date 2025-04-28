#ifndef SOLUTION_H
#define SOLUTION_H
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class Solution {
public:
    Solution();
    int GetNumberOfFoldersAndFiles(const QString &path);
    int GetNumberOfFolders(const QString &path);

    bool IsValidFilter(QString filter);
    void SetNameFilters(const QStringList &nameFilters);

    QStringList getNameFilters(){
        return nameFilters_;
    }

private:
    QStringList nameFilters_;
    int CountFilteredFiles(const QString &path);
    QFileInfoList GetSubfolders(const QString &path);
};

#endif // SOLUTION_H
