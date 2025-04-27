#ifndef SOLUTION_H
#define SOLUTION_H
#include <QString>
#include <QFileInfo>
#include <QDir>

class Solution {
public:
    Solution();
    int GetNumberOfFoldersAndFiles(const QString &path);
    int GetNumberOfFolders(const QString &path);

private:
    QStringList nameFilter;
    int CountFilteredFiles(const QString &path);
    QFileInfoList GetSubfolders(const QString &path);
};

#endif // SOLUTION_H
