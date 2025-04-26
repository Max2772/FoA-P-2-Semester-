#include "solution.h"
#include <QDebug>

Solution::Solution() {}

QString Solution::IntegerToBinary(long long num)
{
    if(num == 0){
        return "";
    }else if(num % 2 == 0){
        return IntegerToBinary(num / 2) + QString("0");
    }else{
        return IntegerToBinary(num / 2) + QString("1");
    }
}

QString Solution::FractionalToBinary(double fraction, int numberOfPrecision){
    qDebug() << "Fraction: " << fraction << "\nNumber Of Precision: " << numberOfPrecision;
    if(numberOfPrecision <= 0 || fraction == 0){
        return "";
    }

    if(fraction * 2 - 1 >= 0){
        return QString("1") + FractionalToBinary(fraction * 2 - 1, numberOfPrecision - 1);
    }

    return QString("0") + FractionalToBinary(fraction * 2, numberOfPrecision - 1);
}

QString Solution::FormatNumber(const QString &integer, const QString &fractal)
{
    QString formattedInteger;
    for(int i = 0; i < integer.size(); ++i){
        formattedInteger += integer[i];
        if(i % 4 == 3 && i < integer.size() - 1){
            formattedInteger += ' ';
        }
    }

    QString formattedFractal;
    for(int i = 0; i < fractal.size(); ++i){
        formattedFractal += fractal[i];
        if(i % 4 == 3 && i < fractal.size() - 1){
            formattedFractal += ' ';
        }
    }

    if(formattedFractal.isEmpty())
        return formattedInteger;

    return formattedInteger + '.' + formattedFractal;

}
