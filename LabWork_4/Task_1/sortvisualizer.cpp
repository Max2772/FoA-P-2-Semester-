#include "sortvisualizer.h"

#include <QPainter>
#include <QDebug> // Delete after debug

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent), idx1(-1), idx2(-1){}

void SortVisualizer::setRects(const QVector<QRectF> &rects, int idx1, int idx2){
    qDebug() << "11";
    rectsVector_ = rects;
    qDebug() << "12";
    this->idx1 = idx1;
    this->idx2 = idx2;
    qDebug() << "13";
    update();
    qDebug() << "14";
}

void SortVisualizer::paintEvent(QPaintEvent *event){

    if(rectsVector_.isEmpty()){
        qDebug() << "rectVector_ пустой!";
        return;
    }

    QPainter painter(this);
    int maxHeight = height();

    qDebug() << "21";
    QPen pen(Qt::gray, 2);
    painter.setPen(pen);

    qDebug() << rectsVector_.size();
    qDebug() << "22";
    for(int i = 0; i < rectsVector_.size(); ++i){
        qDebug() << i << '\n';
        QRectF rect = rectsVector_[i];
        rect.moveBottom(maxHeight);

        painter.setBrush((i == idx1 || i == idx2) ? Qt::green : Qt::white);
        painter.drawRect(rect);
    }
}
