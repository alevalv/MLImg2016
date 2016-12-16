#ifndef UTIL_H
#define UTIL_H

#include <random>

class Util
{
public:
    static const std::string WINDOW_NAME;

    static int countDigits(const int number);
    static double euclideanDistance(std::vector<double> &element1, std::vector<double> &element2);
    static double distance(std::vector<std::vector<double> > &element1,
                           std::vector<std::vector<double> > &element2,
                           std::function<double(std::vector<double> &, std::vector<double> &)> fun);
    static double manhattanDistance(std::vector<double> &element1, std::vector<double> &element2);
    static void showImage(const cv::Mat& image);
    static std::vector<cv::Point2d> getCircle(int x, int y, int radius);

};

#endif // UTIL_H
