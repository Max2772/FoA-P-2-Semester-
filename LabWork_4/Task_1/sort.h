#ifndef SORT_H
#define SORT_H

#include <QVector>

class Sort
{
public:
    Sort();
    static void QuickSort(QVector<int>& arr, int low, int high, QVector<QPair<int, int>>& motionVector);
    static void MergeSort(QVector<int>& arr, int left, int right, QVector<QPair<int, int>>& motionVector);
    static void HeapSort(QVector<int>& arr, QVector<QPair<int, int>>& motionVector);

private:
    static int Partition(QVector<int>& arr, int low, int high, QVector<QPair<int, int>>& motionVector);
    static void Merge(QVector<int>& arr, int left, int mid, int right, QVector<QPair<int, int>>& motionVector);
    static void Heapify(QVector<int>& arr, int n, int i, QVector<QPair<int, int>>& motionVector);
};

#endif // SORT_H
