//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_DATAMAKER_H
#define MACLEA_DATAMAKER_H


#include <opencv2/opencv.hpp>

class DataMaker
{
public:
    static int maxCount;
    static int windowSize;

    static std::map<int, std::array<std::vector<cv::Mat>, 2> > createData(
        std::map<int, std::array<cv::Mat, 2> > &inputImages,
        int threshold = 100);

    static const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> OPTICAL_DISK_CORNERS;

    static const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> OPTICAL_DISK_SURF;

    static const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> WINDOW;

    static const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> RANDOM_PIXELS;

};

#endif //MACLEA_DATAMAKER_H
