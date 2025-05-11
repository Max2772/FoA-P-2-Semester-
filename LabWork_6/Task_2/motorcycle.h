#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include <QString>

constexpr int MAX_MODEL_NAME_CHARACTERS = 50;

struct Motorcycle{
    int mileage;
    double maxSpeed;
    char type;
    bool damaged;
    char modelName[MAX_MODEL_NAME_CHARACTERS];
};

#endif // MOTORCYCLE_H
