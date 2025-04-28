#ifndef ARRAYMANAGER_H
#define ARRAYMANAGER_H

#include <QVector>
#include <QRandomGenerator>
#include <QTime>

class ArrayManager
{
public:
    ArrayManager();

    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 101;

    void RandomNumberVectorGenerate(QVector<int>& arr, int size);
};

#endif // ARRAYMANAGER_H
