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
    void QuickSort();

    const QVector<QRectF>& getRects() const { return rectsVector_; }

    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 101;
private:
    void RandomNumberVectorGenerate(int size);
    bool IsSorted();
    void onSortTimerTimeout();
    void ShowSort();
    void OutputArray();

    QVector<int> arr_;
    QVector<QRectF> rectsVector_;
    QVector <QPair <int, int>> motionVector_;

    bool isUpdating;

    int idx1, idx2;

    QTimer* sortTimer = nullptr;
    SortVisualizer *sortVisualizer = nullptr;
};

#endif // SORTCONTROLLER_H
