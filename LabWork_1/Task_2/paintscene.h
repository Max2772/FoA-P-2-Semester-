#pragma once

#ifndef PAINTSCENE_H
#define PAINTSCENE_H
 
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "figure.h"
 
class PaintScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(int typeFigure
               READ typeFigure WRITE setTypeFigure
               NOTIFY typeFigureChanged)
 
public:
    explicit PaintScene(QObject *parent = 0);
    ~PaintScene();

    void spaceFigure();
 
    int typeFigure() const;
    void setTypeFigure(const int type);
    void setMouseMode(const int type);

    void setScale(double value);
    void setRotationX(int value);
    void setRotationY(int value);
    void setRotation(int value);
    void setOuterRadius(int value);
    void setInnerRadius(int value);
    void setSideA(int value);
    void setSideB(int value);
    void setNumber(int value);
    void setAngel(int value);
    int N;
    int rotationX;
    int rotationY;
    int rotation;
    double outerRadius;
    double innerRadius;

    bool isNoFigure;

    bool isNew = true;

    double returnArea();
    double returnPerimeter();
    int returnCenterX();
    int returnCenterY();
    double returnOuterRadius();
    double returnInnerRadius();
    double returnSideA();
    double returnSideB();
    double returnAngel();
    int returnNumber();

    bool returnIsNew();
    void setIsNew();

    bool is_No_Figure();

    // Треугольник
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

    enum FigureTypes {
        RectangleType,
        RombType,
        TriangleType,
        EllipseType,
        StarType,
        PolygonType,
        ParallelogramType,
        PaintType
    };

    enum MouseMode {
        drawing,
        editing
    };
 
signals:
    void typeFigureChanged();
 
private:
    Figure *tempFigure;
    int m_typeFigure;
    int m_mousemode;


    QGraphicsPolygonItem* selectedPolygon = nullptr;

 
private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};
 
#endif // PAINTSCENE_H
