//
// Created by alevalv on 15/12/16.
//

#ifndef MACLEA_KNEAREST_H
#define MACLEA_KNEAREST_H

#include <opencv2/opencv.hpp>

class KNearest
{
    cv::Ptr<cv::ml::KNearest> knearest;
public:
    void train(std::map<int, std::array<std::vector<cv::Mat>, 2> > image);

    cv::Mat predict();
};


#endif //MACLEA_KNEAREST_H
