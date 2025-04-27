#include "solution.h"

Solution::Solution() {}


int Solution::Reverse(int n)
{
    int digits = log10(n);
    if (n == 0) {
        return 0;
    }
    else {
        return (n % 10) * pow(10, digits) + Reverse(n / 10);
    }
}

int Solution::pow(int a, int b) {
    if(b == 0) return 1;

    return a * pow(a, b - 1);
}

int Solution::log10(int num, int res) {
    if(num < 10) {
        return res;
    }
    else {
        return log10(num / 10, res + 1);
    }
}
