#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <QString>

constexpr int MAX_MODEL_NAME_CHARACTES = 50;

struct Motorcycle{
    int mileage;
    double maxSpeed;
    char type;
    bool damaged;
    char modelName[MAX_MODEL_NAME_CHARACTES];
    static int series;

    QString Print();
};

#endif // MOTORCYCLE_H
