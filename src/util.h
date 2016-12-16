#ifndef UTIL_H
#define UTIL_H

#include <random>

class Util
{
public:
    static int countDigits(const int number);
    static double distance(std::vector<double> &element1, std::vector<double> &element2);
    static double distance(std::vector<std::vector<double> > &element1, std::vector<std::vector<double> > &element2);
    static std::string vectorToString(std::vector<std::vector<double> > mVector);
};

#endif // UTIL_H
