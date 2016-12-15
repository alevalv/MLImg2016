//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_DATAMAKER_H
#define MACLEA_DATAMAKER_H


#include <opencv2/opencv.hpp>
#include <array>
#include <map>

class DataMaker
{
    int maxCountImages, threshold, windowSize;
public:
    DataMaker(int maxCountImages, int threshold, int windowSize = 30);
    std::map<int, std::array<std::vector<cv::Mat>,2> > createData(std::map<int, std::array<cv::Mat, 2> > &inputImages);
    std::map<int, std::array<std::vector<cv::Mat>, 2>> createData2(std::map<int, std::array<cv::Mat, 2> > &inputImages);
};

#endif //MACLEA_DATAMAKER_H
