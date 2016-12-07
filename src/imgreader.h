#ifndef IMGREADER_H
#define IMGREADER_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class ImgReader
{
    std::string baseurl;
public:
    ImgReader(const std::string baseUrl);
    std::vector<std::string> getUrls(const std::string folder);
    std::vector<std::string> getAbsoluteUrls(const std::string folder);
    void saveImage(cv::Mat image, const std::string filename);
    void saveImages(std::string url, std::string name, std::vector<cv::Mat>& images, int initialNumber = 1);
    cv::Mat readImage(const std::string url);
protected:
    cv::Mat preprocessing(const cv::Mat& image);

};

#endif // IMGREADER_H
