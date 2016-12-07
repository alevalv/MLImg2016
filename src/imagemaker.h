#ifndef IMAGEMAKER_H
#define IMAGEMAKER_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "retinalimage.h"

class ImageMaker
{
    std::string fileName;
    int startingNumber, windowSize;
public:
    ImageMaker(const std::string filename, const int startingNumber, const int windowSize);
    std::vector<cv::Mat> createFrom(RetinalImage& image);
};

#endif // IMAGEMAKER_H
