#ifndef IMGREADER_H
#define IMGREADER_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <functional>
#include "preprocessor.h"

class ImgReader
{
    std::string baseurl;
    std::function<cv::Mat(cv::Mat&)> preprocessing = Preprocessor::NONE;
public:
    ImgReader(const std::string baseUrl);
    std::vector<std::string> getUrls(const std::string folder);
    std::vector<std::string> getAbsoluteUrls(const std::string folder);
    void saveImage(cv::Mat image, const std::string filename);
    void saveImages(std::string url, std::string name, std::vector<cv::Mat>& images, int initialNumber = 1);
    cv::Mat readImageAbsolute(const std::string url);
    cv::Mat readImage(const std::string url);
    cv::Mat readImageNoPreprocessing(const std::string url);
    cv::Mat readImageAbsoluteNoPreprocessing(const std::string url);
    void setPreprocessing(const std::function<cv::Mat(cv::Mat&)> &function);
    std::map<int, std::array<cv::Mat, 2> > readWithGroundTruth(
        std::string originalImagePath, std::string groundTruthPath, std::string numberDelim);
};

#endif // IMGREADER_H
