#include "rocket.h"
#include "line.h"
#include <QPolygon>


void Rocket::updateFlame()
{
    flameOffset = (flameOffset + 1) % 15;
    update();
}

Rocket::Rocket() : Line()
{
    rect_ = QRectF(0, -230, 90, 280);
    flameTimer = new QTimer;
    flameOffset = 0;
    connect(flameTimer, &QTimer::timeout, this, &Rocket::updateFlame);
}

void Rocket::stopFlame(){
    flameTimer->stop();
}

void Rocket::startFlame(){
    flameTimer->start(10);
}

void Rocket::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget * widget)
{
    // Корпус
    QPolygon rocketBody;
    rocketBody << QPoint(0, 0) << QPoint(25, -25) << QPoint(25, -200) << QPoint(37, -225) << QPoint(49, -200)
        << QPoint(49, -25) << QPoint(74, 0) << QPoint(0, 0);
    painter->drawPolygon(rocketBody);

    // Окно
    painter->setBrush(Qt::blue);
    painter->drawEllipse(30, -175, 15, 15);

    // Пламя
    painter->setBrush(QColor(255,128,0));
    QPolygon flameShape;
    int flameHeight = 30 + flameOffset;
    flameShape << QPoint(22, 0) << QPoint(37, flameHeight) << QPoint(52, 0);
    painter->drawPolygon(flameShape);
}
