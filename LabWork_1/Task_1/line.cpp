#include "line.h"
#include "QPainter"

void Line::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->drawLine(1, 0, 1, 260);
}

void Line::turn_on()
{
    on_off = true;
}

void Line::restart()
{
    this->setPos(this->x(), 500);
    on_off = false;
}

void Line::move()
{
    if(on_off == true) {
        this->setPos(this->x(), this->y() - 1);
    }
}

QRectF Line::boundingRect() const
{
    return rect_;
}

Line::Line() : QGraphicsObject()
{
    rect_ = QRectF(0, 0, 1, 260);
    on_off = false;
}
