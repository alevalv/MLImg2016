//
// Created by alevalv on 11/12/16.
//

#include "Feature.h"

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;

Feature::Feature(int minHessian)
{
    this->minHessian = minHessian;
}

Mat Feature::SURF(Mat &image)
{
    Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);

    std::vector<KeyPoint> keypoints1, keypoints2;

    detector->detect(image, keypoints1);

    Mat drawImage;
    drawKeypoints(image, keypoints1, drawImage, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

    return drawImage;
}