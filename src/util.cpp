#include <sstream>
#include <iterator>
#include <functional>
#include "util.h"

using namespace std;

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

double Util::euclideanDistance(vector<double> &element1, vector<double> &element2)
{
    double distance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        double tmp = element1[i] - element2[i];
        distance += tmp * tmp;
    }

    return sqrt(distance);
}

double Util::manhattanDistance(vector<double> &element1, vector<double> &element2)
{

    double distance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        double tmp = element1[i] - element2[i];
        distance += abs(tmp);
    }

    return sqrt(distance);
}

double Util::distance(vector<vector<double> > &element1,
                      vector<vector<double> > &element2,
                      function<double(vector<double> &, vector<double> &)> fun)
{
    double distance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        distance += fun(element1[i], element2[i]);
    }

    return distance;
}
