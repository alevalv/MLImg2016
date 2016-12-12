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
    static const std::function<Mat(Mat&)> EXTRACT_GREEN;
};

#endif //MACLEA_PREPROCESS_H
