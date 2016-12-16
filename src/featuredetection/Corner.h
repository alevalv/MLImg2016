//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_HARRIS_H
#define MACLEA_HARRIS_H

#include <opencv2/opencv.hpp>
#include "../image/imgreader.h"

class Corner
{
    int threshold;
public:
    Corner(int threshold);

    cv::Mat harrisDrawImage(const cv::Mat &image);

    std::vector<std::vector<double> > harrisGetCorners(const cv::Mat &image);

    cv::Mat shiTomasiDrawImage(const cv::Mat &image);

    std::vector<std::vector<double> > shiTomasiGetCorners(const cv::Mat &image);

    void runAll(ImgReader &reader, const cv::Mat &image, const std::string name);
};


#endif //MACLEA_HARRIS_H
