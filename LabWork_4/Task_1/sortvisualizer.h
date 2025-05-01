#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <QWidget>
#include <QVector>
#include <QRectF>

class SortVisualizer: public QWidget{
    Q_OBJECT
public:
    SortVisualizer(QWidget *parent = nullptr);
    void setRects(const QVector<QRectF> &rects, int idx1, int idx2);
    void setSearchIndices(int left, int right, int mid);
    QVector<QRectF> createRects(const QVector<int> &values) const;

    static const int OFFSET_X = 30;
    static const int WIDTH = 10;
    static const int MIN_HEIGHT = 20;
    static const int MULTIPILIER_HEIGHT = 4;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVector<QRectF> rectsVector_;
    int idx1 = -1, idx2 = -1;
    int searchLeft = -1, searchRight = -1, searchMid = -1;
};

#endif // SORTVISUALIZER_H
