#ifndef FIGURE_H
#define FIGURE_H
 
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
 
class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint
               READ startPoint WRITE setStartPoint
               NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint
               READ endPoint WRITE setEndPoint
               NOTIFY pointChanged)
public:
    explicit Figure(QPointF point, QObject *parent = 0);
    ~Figure();
 
    QPointF startPoint() const;
    QPointF endPoint() const;
 
    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    void setNumber(int value);
    void setScale(double value);
    void setRotation(int value);
    void setRotationX(int value);
    void setRotationY(int value);
    void setOuterRadius(int value);
    void setInnerRadius(int value);
    void setSideA(int value);
    void setSideB(int value);
    void setAngel(int value);
    // Треугольникz
    void setPointA_x(int value);
    void setPointA_y(int value);
    void setPointB_x(int value);
    void setPointB_y(int value);
    void setPointC_x(int value);
    void setPointC_y(int value);
    int returnPointA_x();
    int returnPointA_y();
    int returnPointB_x();
    int returnPointB_y();
    int returnPointC_x();
    int returnPointC_y();

    void setIsDrawingFirstTime(bool value);
    double returnArea();
    double returnPerimeter();
    double returnCenterX();
    double returnCenterY();
    double returnOuterRadius();
    double returnInnerRadius();
    double returnSideA();
    double returnSideB();
    double returnAngel();
    int returnNumber();
    int N;
    double scale;
    int rotation;
    int rotationX;
    int rotationY;
    double sideA;
    double sideB;
    double sideC;
    double area;
    double perimeter;
    double angel;
    double outerRadius;
    double innerRadius;
    QPointF center;
    QPointF pointA;
    QPointF pointB;
    QPointF pointC;
    int A_x;
    int A_y;
    int B_x;
    int B_y;
    int C_x;
    int C_y;

    bool is_drawing_first_time;

signals:
    void pointChanged();
 
private:
    QPointF m_startPoint;
    QPointF m_endPoint;
 
    QRectF boundingRect() const;
 
public slots:
    void updateRomb();

protected:
    QVector<QPointF> points;

};
 
#endif // FIGURE_H
