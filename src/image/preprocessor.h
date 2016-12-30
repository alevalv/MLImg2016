//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_PREPROCESS_H
#define MACLEA_PREPROCESS_H

#include <opencv2/opencv.hpp>
#include <functional>

using namespace std;
using namespace cv;

class Preprocessor
{
public:
    static const function<Mat(Mat &)> NONE;
    static const function<Mat(Mat &)> EXTRACT_GREEN;
    static const function<Mat(Mat &)> GRADIENT;
    static const function<Mat(Mat &)> GRADIENT2;
    static const function<Mat(Mat &, int)> GRADIENT_SCALE;
    static const function<Mat(Mat &, int)> GRADIENT2_SCALE;
    static const function<Mat(Mat &)> GREEN_DUAL_GRADIENT;
};

#endif //MACLEA_PREPROCESS_H
