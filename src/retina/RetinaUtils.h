//
// Created by alevalv on 16/12/16.
//

#ifndef MACLEA_RETINAUTILS_H
#define MACLEA_RETINAUTILS_H

#include <opencv2/opencv.hpp>

class RetinaUtils
{
public:
    static std::vector<double> findOpticalDisk(cv::Mat& image);
};


#endif //MACLEA_RETINAUTILS_H
