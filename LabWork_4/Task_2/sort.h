#ifndef SORT_H
#define SORT_H

#include <QVector>
#include <QPair>

class Sort
{
public:
    Sort();
    static void InterpolationSort(QVector<int>& arr, QVector<QPair<int, int>>& motionVector);
    static int BinaryPow(int digit, int power, int mod);
};

#endif // SORT_H
