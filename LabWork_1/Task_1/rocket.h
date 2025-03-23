#ifndef ROCKET_H
#define ROCKET_H
#include <QTime>
#include <QTimer>
#include <QTimerEvent>
#include "line.h"

class Rocket : public Line
{
public:
    Rocket();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private slots:
    void updateFlame();
public slots:
    void startFlame();
    void stopFlame();
private:
    QTimer* flameTimer;
    int flameOffset;
};

#endif // ROCKET_H
