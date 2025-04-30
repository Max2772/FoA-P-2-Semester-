#include "sortvisualizer.h"

#include <QPainter>

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent), idx1(-1), idx2(-1){}

void SortVisualizer::setRects(const QVector<QRectF> &rects, int idx1, int idx2){
    rectsVector_ = &rects;
    this->idx1 = idx1;
    this->idx2 = idx2;
    update();
}

void SortVisualizer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int maxHeight = height();

    QPen pen(Qt::gray, 2);
    painter.setPen(pen);

    for(int i = 0; i < rectsVector_->size(); ++i){
        QRectF rect = (*rectsVector_)[i];
        rect.moveBottom(maxHeight);

        painter.setBrush((i == idx1 || i == idx2) ? Qt::green : Qt::white);
        painter.drawRect(rect);
    }
}
