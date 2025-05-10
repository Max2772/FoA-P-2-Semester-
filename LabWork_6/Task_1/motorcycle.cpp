#include "motorcycle.h"

int Motorcycle::series = 2025;

QString Motorcycle::Print() const
{
    return QString("Model: %1 | Type: %2 | Mileage: %3 | MaxSpeed: %4 | Damaged: %5 | Series: %6")
        .arg(modelName).arg(type).arg(mileage).arg(maxSpeed).arg(damaged ? "Yes" : "No").arg(series);
}
