#include <sstream>
#include <functional>
#include <cv.hpp>
#include "util.h"

using namespace std;
using namespace cv;

const string Util::WINDOW_NAME = "window";

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
    double totalDistance = 0;

    for (int i = 0; i < element1.size(); i++)
    {
        totalDistance += fun(element1[i], element2[i]);
    }

    return totalDistance;
}

void Util::showImage(const Mat& image)
{
    namedWindow(WINDOW_NAME, WINDOW_FREERATIO);
    imshow(WINDOW_NAME, image);
    waitKey(0);
}

//See https://en.wikipedia.org/wiki/Midpoint_circle_algorithm#C_EXAMPLE
vector<Point2d> Util::getCircle(int x0, int y0, int radius, int yy, int xx)
{
    vector<Point2d> points;
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        points.push_back(Point2d((x0 + x)%xx, (y0 + y)%yy));
        points.push_back(Point2d((x0 + y)%xx, (y0 + x)%yy));
        points.push_back(Point2d((x0 - y)%xx, (y0 + x)%yy));
        points.push_back(Point2d((x0 - x)%xx, (y0 + y)%yy));
        points.push_back(Point2d((x0 - x)%xx, (y0 - y)%yy));
        points.push_back(Point2d((x0 - y)%xx, (y0 - x)%yy));
        points.push_back(Point2d((x0 + y)%xx, (y0 - x)%yy));
        points.push_back(Point2d((x0 + x)%xx, (y0 - y)%yy));

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

    return points;
}
