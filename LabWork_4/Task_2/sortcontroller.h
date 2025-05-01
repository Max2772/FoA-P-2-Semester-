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

    void CreateNewArr(int size);
    void Sort();
    void BinarySearch(int value);

    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 4;
    static const int SORT_ANIMATION_SPEED = 30;
    static const int SERACH_ANIMATION_SPEED = 300;

signals:
    void sortingStateChanged(bool isSorting);
    void searchStateChanged(bool isSearching);

    void searchResult(int idx, int result);

private:
    void RandomNumberVectorGenerate(int size);
    bool IsSorted();
    void OutputArray();
    void onSortTimerTimeout();
    void ShowSort();;
    void onSearchTimerTimeout();

    QVector<int> arr_;
    QVector<QRectF> rectsVector_;
    QVector<QPair <int, int>> motionVector_;
    QVector<QPair<int, int>> searchVector_;

    bool isUpdating;
    bool isSearching;

    int MAX_HEIGHT;
    int idx1, idx2;
    int searchLeft, searchRight, searchMid;

    QTimer* sortTimer = nullptr;
    QTimer* searchTimer = nullptr;
    SortVisualizer *sortVisualizer = nullptr;
};

#endif // SORTCONTROLLER_H
