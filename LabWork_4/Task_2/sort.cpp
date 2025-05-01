#include "sort.h"
#include <QDebug>
#include <cmath>

Sort::Sort() {}

void Sort::InterpolationSort(QVector<int>& arr, QVector<QPair<int, int>>& motionVector) {
    if (arr.isEmpty()) return;

    int size = arr.size();
    QVector<int> process = {size};
    int rangeStart = 0, rangeEnd = size;

    while (!process.isEmpty()) {
        int bucketSize = process.takeLast();
        rangeStart = rangeEnd - bucketSize;

        int min = arr[rangeStart], max = arr[rangeStart];
        for (int i = rangeStart + 1; i < rangeEnd; ++i) {
            if (arr[i] > max) max = arr[i];
            else if (arr[i] < min) min = arr[i];
        }

        if (min == max) {
            rangeEnd -= bucketSize;
            continue;
        }

        QVector<QVector<int>> buckets(bucketSize);
        for (int i = rangeStart; i < rangeEnd; ++i) {
            double ratio = (arr[i] - min) / static_cast<double>(max - min);
            int bucketIndex = static_cast<int>(std::floor(ratio * (bucketSize - 1)));
            buckets[bucketIndex].append(arr[i]);
        }

        int currentPos = rangeStart;
        for (int i = 0; i < bucketSize; ++i) {
            if (buckets[i].isEmpty()) continue;
            for (int value : buckets[i]) {
                if (arr[currentPos] != value) {
                    for (int j = currentPos + 1; j < rangeEnd; ++j) {
                        if (arr[j] == value) {
                            std::swap(arr[currentPos], arr[j]);
                            motionVector.append({currentPos, j});
                            break;
                        }
                    }
                }
                currentPos++;
            }
            process.append(buckets[i].size());
        }
    }
}

long long Sort::BinaryPow(int digit, int power, long long mod) {
    long long result = 1;
    long long base = digit % mod;
    while (power > 0) {
        if (power & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        power >>= 1;
    }
    return result;
}
