#ifndef SORTVISUALIZER_H
#define SORTVISUALIZER_H

#include <QWidget>
#include <QVector>
#include <QRectF>

class SortVisualizer: public QWidget
{
    Q_OBJECT
public:
    SortVisualizer(QWidget *parent = nullptr);
    void setRects(const QVector<QRectF*>& rects, int ind1, int ind2);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QVector<QRectF*> rectsVector;
    int ind1, ind2;

};

#endif // SORTVISUALIZER_H
