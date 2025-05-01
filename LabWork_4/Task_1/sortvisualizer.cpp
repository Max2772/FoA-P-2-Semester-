#include "sortvisualizer.h"

#include <QPainter>

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent){}

void SortVisualizer::setRects(const QVector<QRectF> &rects, int idx1, int idx2){
    for(int i = 0; i < rects.size(); ++i){
        rectsVector_.append(rects[i]);
    }
    rectsVector_ = rects;
    this->idx1 = idx1;
    this->idx2 = idx2;
    update();
}

void SortVisualizer::setSearchIndices(int left, int right, int mid) {
    searchLeft = left;
    searchRight = right;
    searchMid = mid;
    update();
}

QVector<QRectF> SortVisualizer::createRects(const QVector<int> &values) const
{
    QVector<QRectF> rects;
    for(int i = 0; i < values.size(); ++i){
        QRectF rect(OFFSET_X + WIDTH * i,
                    height() - (MIN_HEIGHT + MULTIPILIER_HEIGHT * values[i]),
                    WIDTH,
                    MIN_HEIGHT + MULTIPILIER_HEIGHT * values[i]);

        rects.append(rect);
    }
    return rects;
}

void SortVisualizer::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int maxHeight = height();

    QPen pen(Qt::gray, 2);
    painter.setPen(pen);

    for(int i = 0; i < rectsVector_.size(); ++i){
        QRectF rect = rectsVector_[i];
        rect.moveBottom(maxHeight);

        if(i == searchMid){
            painter.setBrush(Qt::red);
        }else if(i == searchLeft || i == searchRight){
            painter.setBrush(Qt::yellow);
        }else if(i == idx1 || i == idx2){
            painter.setBrush(Qt::green);
        }else{
            painter.setBrush(Qt::white);
        }

        painter.drawRect(rect);
    }
}
