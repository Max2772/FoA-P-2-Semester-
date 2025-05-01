#ifndef SORT_H
#define SORT_H

#include <QVector>
#include <QPair>

class Sort
{
public:
    Sort();
    static void InterpolationSort(QVector<int>& arr, QVector<QPair<int, int>>& motionVector);
    static long long BinaryPow(int digit, int power, long long mod);
};

#endif // SORT_H
