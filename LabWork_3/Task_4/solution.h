#ifndef SOLUTION_H
#define SOLUTION_H

#include <QString>

class Solution
{
public:
    Solution();

    QString Hanoi(int num, QString A, QString B, QString C);
    void ResetLine();
private:
    QString result;
};

#endif // SOLUTION_H
