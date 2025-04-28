#include "sortvisualizer.h"

#include <QPainter>

SortVisualizer::SortVisualizer(QWidget *parent) : QWidget(parent), ind1(-1), ind2(-1)
{
    setStyleSheet("background-color: #444444;"); // Контрастный фон
}

#include <QPainter>

void SortVisualizer::setRects(const QVector<QRectF*>& rects, int ind1, int ind2)
{
    rectsVector = rects;
    this->ind1 = ind1;
    this->ind2 = ind2;
    update();
}

void SortVisualizer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int maxHeight = height();

    QPen pen(Qt::white, 1); // Белая обводка
    painter.setPen(pen);

    for (int i = 0; i < rectsVector.size(); ++i) {
        QRectF rect = *rectsVector[i];
        rect.moveBottom(maxHeight);
        if (i == ind1 || i == ind2) {
            painter.setBrush(Qt::green); // Активные
        } else {
            painter.setBrush(Qt::white); // Неактивные
        }
        painter.drawRect(rect);
    }
}
