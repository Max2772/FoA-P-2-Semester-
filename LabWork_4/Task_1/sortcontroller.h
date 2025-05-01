#ifndef SORTCONTROLLER_H
#define SORTCONTROLLER_H

#include <QVector>
#include <QRandomGenerator>
#include <QTimer>
#include <QRectF>

#include "sortvisualizer.h"

class SortController : public QObject
{
    Q_OBJECT
public:
    SortController(SortVisualizer *visualizer, QObject* parent = nullptr);
    ~SortController();

    enum class SortType {
        QuickSort,
        HeapSort,
        MergeSort
    };

    void CreateNewArr(int size);
    void Sort(SortType type);

    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 101;
    static const int ANIMATION_SPEED = 30;

signals:
    void sortingStateChanged(bool isSorting);

private:
    void RandomNumberVectorGenerate(int size);
    bool IsSorted();
    void OutputArray();
    void onSortTimerTimeout();
    void ShowSort();;

    QVector<int> arr_;
    QVector<QRectF> rectsVector_;
    QVector <QPair <int, int>> motionVector_;

    bool isUpdating;

    int MAX_HEIGHT;
    int idx1, idx2;

    QTimer* sortTimer = nullptr;
    SortVisualizer *sortVisualizer = nullptr;
};

#endif // SORTCONTROLLER_H
