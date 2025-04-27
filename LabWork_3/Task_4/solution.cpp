#include "solution.h"

Solution::Solution() {}

QString Solution::Hanoi(int num, QString A,
                        QString B, QString C) {
    if (num == 1) {
        result += "Переместить диск номер " + QString::number(num) + " из  " +
                  A + " на " + C + '.' + '\n';
        return result;
    }
    Hanoi(num - 1, A, C, B);
    result += "Переместить диск номер " + QString::number(num) + " из  " +
              A + " на " + C + '.' + '\n';
    Hanoi(num - 1, B, C, A);
    return result;
}

void Solution::ResetLine() {
    result = "Поочередные шаги по перестановке колец:\n";
}
