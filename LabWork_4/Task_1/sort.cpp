#include "sort.h"

Sort::Sort() {}

// Quick Sort
int Sort::Partition(QVector<int>& arr, int low, int high, QVector<QPair<int, int>>& motionVector){
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            motionVector.append({i, j});
        }
    }
    std::swap(arr[i + 1], arr[high]);
    motionVector.append({i + 1, high});
    return i + 1;
}

void Sort::QuickSort(QVector<int>& arr, int low, int high, QVector<QPair<int, int>>& motionVector){
    if (low < high) {
        int pi = Partition(arr, low, high, motionVector);
        QuickSort(arr, low, pi - 1, motionVector);
        QuickSort(arr, pi + 1, high, motionVector);
    }
}

// Merge Sort
void Sort::Merge(QVector<int>& arr, int begin, int end, QVector <QPair <int, int>>& motionVector){
    int i = begin;
    int mid = begin + (end - begin) / 2;
    int j = mid + 1;
    int k = 0;
    int d[1000];

    while (i <= mid && j <= end){
        if ((arr)[i] <= (arr)[j]){
            d[k] = arr[i];
            i++;
        }
        else{
            d[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid){
        d[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end){
        d[k] = arr[j];
        j++;
        k++;
    }

    for(i = 0; i < k; ++i){
        int p;
        for (int z = 0; z < k ; ++z){
            if (arr[z + begin] == d[i]){
                p = z;
                motionVector.append(QPair<int, int>(begin + i, z + begin));
                std::swap(arr[i+ begin], arr[z + begin]);
                break;
            }
        }
    }
}

void Sort::MergeSort(QVector<int>& arr, int left, int right, QVector <QPair <int, int>>& motionVector){
    if (left < right){
        if (right - left == 1){
            if ((arr)[left] > (arr)[right]){
                motionVector.append(QPair<int, int>(left, right));
                std::swap(arr[left], arr[right]);
            }
        }
        else{
            MergeSort(arr, left, left + (right - left) / 2, motionVector);
            MergeSort(arr, left + (right - left) / 2 + 1, right, motionVector);
            Merge(arr, left, right, motionVector);

        }
    }
}

// Heap Sort
void Sort::Heapify(QVector<int>& arr, int n, int i, QVector<QPair<int, int>>& motionVector){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        motionVector.append({i, largest});
        Heapify(arr, n, largest, motionVector);
    }
}

void Sort::HeapSort(QVector<int>& arr, QVector<QPair<int, int>>& motionVector){
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i, motionVector);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        motionVector.append({0, i});
        Heapify(arr, i, 0, motionVector);
    }
}
