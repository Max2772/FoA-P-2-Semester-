#ifndef SORTCONTROLLER_H
#define SORTCONTROLLER_H

#include <QVector>
#include <QRandomGenerator>
#include <QTime>
#include <QRectF>

#include "sortvisualizer.h"

class SortController
{
public:
    SortController();

    void OutputArray();

    const QVector<QRectF>& getRects() const { return rectsVector_; }

    static const int MINIMUM_RANDOM_NUMBER = 1;
    static const int MAXIMUM_RANDOM_NUMBER = 101;
private:
    void RandomNumberVectorGenerate(const int &size);
    bool IsSorted();
    void CreateNewArr(const int &size, const int& sortWidgetHeight);
    void onSortTimerTimeout();
    void ShowSort();

    QVector<int> arr_;
    QVector<QRectF> rectsVector_;
    QVector <QPair <int, int>> motionVector_;

    bool isUpdating;

    int idx1, idx2;

    SortVisualizer sortVisualizer;
};

#endif // SORTCONTROLLER_H
