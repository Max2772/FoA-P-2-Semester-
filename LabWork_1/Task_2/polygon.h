#pragma once

#ifndef POLYGONE_H
#define POLYGONE_H
 
#include <QObject>
#include <QGraphicsItem>
#include "figure.h"
 
class Polygone : public Figure
{
    Q_OBJECT
 
public:
    explicit Polygone(QPointF point, QObject *parent = 0);
    ~Polygone();
 
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
 
#endif // POLYGONE_H
