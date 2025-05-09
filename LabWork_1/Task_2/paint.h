#pragma once

#ifndef PAINT_H
#define PAINT_H

#include <QObject>
#include <QGraphicsItem>
#include "figure.h"

class Paint : public Figure
{
    Q_OBJECT

public:
    explicit Paint(QPointF point, QObject *parent = 0);
    ~Paint();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // PAINT_H
