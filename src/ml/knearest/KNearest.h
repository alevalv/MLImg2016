//
// Created by alevalv on 15/12/16.
//

#ifndef MACLEA_KNEAREST_H
#define MACLEA_KNEAREST_H

#include <opencv2/opencv.hpp>
#include <functional>

class KNearest
{
    cv::Ptr<cv::ml::KNearest> knearest;
    std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> dataMaker;
public:
    KNearest(const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> &dataMaker);
    void train(std::map<int, std::array<cv::Mat, 2> > images);

    cv::Mat predict(cv::Mat &image);
};


#endif //MACLEA_KNEAREST_H
