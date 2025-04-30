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
void Sort::Merge(QVector<int>& arr, int left, int mid, int right, QVector<QPair<int, int>>& motionVector) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Временный массив для хранения промежуточного результата
    QVector<int> temp(right - left + 1);
    int tempIndex = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            temp[tempIndex] = L[i];
            // Записываем "перемещение" элемента из позиции left+i в k
            motionVector.append({k, left + i});
            i++;
        } else {
            temp[tempIndex] = R[j];
            // Записываем "перемещение" элемента из позиции mid+1+j в k
            motionVector.append({k, mid + 1 + j});
            j++;
        }
        k++;
        tempIndex++;
    }

    while (i < n1) {
        temp[tempIndex] = L[i];
        motionVector.append({k, left + i});
        i++;
        k++;
        tempIndex++;
    }

    while (j < n2) {
        temp[tempIndex] = R[j];
        motionVector.append({k, mid + 1 + j});
        j++;
        k++;
        tempIndex++;
    }

    // Копируем временный массив обратно в arr
    for (int t = 0; t < temp.size(); t++) {
        arr[left + t] = temp[t];
    }
}

void Sort::MergeSort(QVector<int>& arr, int left, int right, QVector<QPair<int, int>>& motionVector){
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid, motionVector);
    MergeSort(arr, mid + 1, right, motionVector);
    Merge(arr, left, mid, right, motionVector);
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
