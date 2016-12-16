#ifndef UTIL_H
#define UTIL_H

#include <random>

class Util
{
public:
    static int countDigits(const int number);
    static double euclideanDistance(std::vector<double> &element1, std::vector<double> &element2);
    static double distance(std::vector<std::vector<double> > &element1,
                           std::vector<std::vector<double> > &element2,
                           std::function<double(std::vector<double> &, std::vector<double> &)> fun);
    static double manhattanDistance(std::vector<double> &element1, std::vector<double> &element2);
};

#endif // UTIL_H
