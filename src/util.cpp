#include <sstream>
#include <iterator>
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

double Util::distance(vector<vector<double> > &element1, vector<vector<double> > &element2)
{
    double distance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        distance += Util::distance(element1[i], element2[i]);
    }

    return distance;
}

double Util::distance(vector<double> &element1, vector<double> &element2)
{
    double distance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        double tmp = element1[i] - element2[i];
        distance += tmp * tmp;
    }

    return sqrt(distance);
}

string Util::vectorToString(vector<vector<double> > mVector)
{
    std::ostringstream oss;

    for (auto &cVector : mVector)
    {
        oss << "[";
        if (!cVector.empty())
        {
            std::copy(cVector.begin(), cVector.end() - 1,
                      std::ostream_iterator<double>(oss, ","));

            oss << cVector.back();
        }
        oss << "]";
    }

    return oss.str();
}