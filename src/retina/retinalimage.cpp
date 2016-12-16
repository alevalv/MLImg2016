#include "retinalimage.h"

RetinalImage::RetinalImage()
{

}

void RetinalImage::setCode(const std::string code)
{
    this->code = code;
}

std::string RetinalImage::getCode()
{
    return code;
}

void RetinalImage::setGroundTruth(const cv::Mat &groundTruth)
{
    this->groundTruth = groundTruth.clone();
}

cv::Mat RetinalImage::getGroundTruth()
{
    return groundTruth;
}

void RetinalImage::setOriginal(const cv::Mat &original)
{
    this->original = original.clone();
}

cv::Mat RetinalImage::getOriginal()
{
    return original;
}

void RetinalImage::show(const std::string &windowName)
{
    cv::imshow(windowName, original);
    cv::waitKey(0);
    cv::imshow(windowName, groundTruth);
    cv::waitKey(0);
}
