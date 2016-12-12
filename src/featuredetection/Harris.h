//
// Created by alevalv on 11/12/16.
//

#ifndef MACLEA_HARRIS_H
#define MACLEA_HARRIS_H

#include <opencv2/opencv.hpp>

class Harris
{
    int threshold;
public:
    Harris(int threshold);
    cv::Mat getHarrisCorners(const cv::Mat &image);

};


#endif //MACLEA_HARRIS_H
