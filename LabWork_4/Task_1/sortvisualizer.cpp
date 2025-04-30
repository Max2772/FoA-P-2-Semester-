#include "sortvisualizer.h"

#include <QPainter>
#include <QDebug> // Delete after debug

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent), idx1(-1), idx2(-1){}

void SortVisualizer::setRects(const QVector<QRectF> &rects, int idx1, int idx2){
    qDebug() << "11";
    for(int i = 0; i < rects.size(); ++i){
        rectsVector_.append(rects[i]);
        qDebug() << "Added rect" << i+1 << ":" << rects[i];
    }
    rectsVector_ = rects;
    qDebug() << "12";
    this->idx1 = idx1;
    this->idx2 = idx2;
    qDebug() << "13";
    update();
    qDebug() << "14";
}

void SortVisualizer::paintEvent(QPaintEvent *event){



    qDebug() << "21";
    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.drawRect(QRectF(10, 10, 50, 50));

    int maxHeight = height();

    qDebug() << "22";
    QPen pen(Qt::gray, 2);
    painter.setPen(pen);

    qDebug() << rectsVector_.size();
    qDebug() << "23";
    for(int i = 0; i < rectsVector_.size(); ++i){
        qDebug() << "Drawing rect:" << i << rectsVector_[i];
        QRectF rect = rectsVector_[i];
        rect.moveBottom(maxHeight);

        painter.setBrush((i == idx1 || i == idx2) ? Qt::green : Qt::white);
        painter.drawRect(rect);
    }
}
