//
// Created by alevalv on 11/12/16.
//

#include "Feature.h"

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace cv;
using namespace std;

Feature::Feature(int minHessian)
{
    this->minHessian = minHessian;
}

Mat Feature::SURFDrawImage(Mat &image)
{
    Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);

    vector<KeyPoint> keypoints;

    detector->detect(image, keypoints);

    Mat drawImage;
    drawKeypoints(image, keypoints, drawImage, Scalar(0), DrawMatchesFlags::DEFAULT);

    return drawImage;
}

vector<vector<double> > Feature::SURF(Mat &image)
{
    Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create(minHessian);

    vector<KeyPoint> keypoints;

    detector->detect(image, keypoints);

    vector<vector<double> > output;

    for (auto& keypoint : keypoints)
    {
        vector<double> point(2, 0.0);
        point[0] = keypoint.pt.x;
        point[1] = keypoint.pt.y;
        output.push_back(point);
    }

    return output;
}