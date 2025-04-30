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
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    const QVector<QRectF>* rectsVector_ = nullptr;
    int idx1, idx2;
};

#endif // SORTVISUALIZER_H
