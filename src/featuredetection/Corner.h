//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_HARRIS_H
#define MACLEA_HARRIS_H

#include <opencv2/opencv.hpp>
#include "../imgreader.h"

class Corner
{
    int threshold;
public:
    Corner(int threshold);
    cv::Mat getHarrisCorners(const cv::Mat &image);
    cv::Mat getShiTomasiCorners(const cv::Mat &image);
    void runAll(ImgReader &reader, const cv::Mat &image, const std::string name);
};


#endif //MACLEA_HARRIS_H
