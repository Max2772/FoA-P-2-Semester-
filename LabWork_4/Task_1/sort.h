#ifndef SORT_H
#define SORT_H

#include <QVector>

class Sort
{
public:
    Sort();
    static void QuickSort(QVector<int>& arr, int low, int high);
    static void MergeSort(QVector<int>& arr, int left, int right);
    static void HeapSort(QVector<int>& arr);

private:
    static int Partition(QVector<int>& arr, int low, int high);
    static void Merge(QVector<int>& arr, int left, int mid, int right);
    static void Heapify(QVector<int>& arr, int n, int i);
};

#endif // SORT_H
