#pragma once

#ifndef STAR_H
#define STAR_H
 
#include <QObject>
#include <QGraphicsItem>
#include "figure.h"
 
class Star : public Figure
{
    Q_OBJECT
 
public:
    explicit Star(QPointF point, QObject *parent = 0);
    ~Star();
 
private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
 
#endif // STAR_H
