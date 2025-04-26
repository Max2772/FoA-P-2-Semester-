#ifndef SOLUTION_H
#define SOLUTION_H

#include <QString>

class Solution
{
public:
    Solution();

    QString IntegerToBinary(long long num);
    QString FractionalToBinary(double fraction, int numberOfPrecision);
    QString FormatNumber(const QString &integer, const QString &fractal);
private:
    int MAX_NUMBER_OF_FRACTAL_PRECISION = 64;
    double MAX_PRECISION = 0.0000001;
};
#endif // SOLUTION_H
