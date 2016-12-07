#include "util.h"

int Util::countDigits(const int number)
{
    int digits = 0;
    int tmpNumber = number;
    while (tmpNumber)
    {
        tmpNumber /= 10;
        digits++;
    }

    return digits;
}
