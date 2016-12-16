#ifndef RETINALIMAGE_H
#define RETINALIMAGE_H

#include <opencv2/opencv.hpp>
#include <string>

class RetinalImage
{
    std::string code;
    cv::Mat original, groundTruth;
public:
    RetinalImage();
    void setCode(const std::string code);
    std::string getCode();
    void setOriginal(const cv::Mat& original);
    cv::Mat getOriginal();
    void setGroundTruth(const cv::Mat& groundTruth);
    cv::Mat getGroundTruth();
    void show(const std::string& windowName);
};

#endif // RETINALIMAGE_H
