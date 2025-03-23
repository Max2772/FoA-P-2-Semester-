#ifndef LINE_H
#define LINE_H
#include <QPainter>
#include <QPaintEvent>
#include <QGraphicsItem>
#include <QGraphicsObject>

class Line : public QGraphicsObject{
    Q_OBJECT
public:
    explicit Line();
    void turn_on();
    void restart();
    void move();
    QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    bool on_off;
    QRectF rect_;
};

#endif // LINE_H
