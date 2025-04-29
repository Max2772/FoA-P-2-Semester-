#include "sortvisualizer.h"

#include <QPainter>

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent), idx1(-1), idx2(-1){}

void SortVisualizer::setRects(const QVector<QRectF>& rects, int idx1, int idx2)
{
    rectsVector = rects;
    this->idx1 = idx1;
    this->idx2 = idx2;
    update();
}

void SortVisualizer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int maxHeight = height();

    QPen pen(Qt::gray, 2);
    painter.setPen(pen);

    for(int i = 0; i < rectsVector.size(); ++i){
        QRectF rect = rectsVector[i];
        rect.moveBottom(maxHeight);

        if (i == idx1 || i == idx2){
            painter.setBrush(Qt::green);
        }else{
            painter.setBrush(Qt::white);
        }

        painter.drawRect(rect);
    }
}
