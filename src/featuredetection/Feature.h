//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_FEATURE_H
#define MACLEA_FEATURE_H

#include <opencv2/opencv.hpp>

class Feature
{
    int minHessian;
public:
    Feature(int minHessian = 400);
    cv::Mat SURFDrawImage(cv::Mat &image);
    std::vector<std::vector<double> > SURF(cv::Mat &image);
};


#endif //MACLEA_FEATURE_H
