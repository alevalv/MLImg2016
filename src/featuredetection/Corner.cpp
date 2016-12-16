//
// Created by alevalv on 11/12/16.
//

#include "Corner.h"
#include "../image/imgreader.h"

using namespace std;
using namespace cv;

Corner::Corner(int threshold)
{
    this->threshold = threshold;
}

Mat Corner::harrisDrawImage(const Mat &image)
{
    Mat dest, dest_normalized, dest_norm_scaled;
    Mat result = image.clone();

    cornerHarris(image, dest, 2, 3, 0.04, BORDER_DEFAULT);
    normalize(dest, dest_normalized, 0, 255, NORM_MINMAX, CV_8U, Mat());
    convertScaleAbs(dest_normalized, dest_norm_scaled);

    for (int j = 0; j < dest_norm_scaled.rows; j++)
    {
        for (int i = 0; i < dest_norm_scaled.cols; i++)
        {
            if ((int) dest_norm_scaled.at<float>(j, i) > threshold)
            {
                circle(result, Point(i, j), 5, Scalar(255), 2, 8, 0);
            }
        }
    }

    return result;
}

vector<vector<double> > Corner::harrisGetCorners(const Mat& image)
{
    Mat dest, dest_normalized, dest_norm_scaled;
    Mat result = image.clone();

    cornerHarris(image, dest, 2, 3, 0.04, BORDER_DEFAULT);
    normalize(dest, dest_normalized, 0, 255, NORM_MINMAX, CV_8U, Mat());
    convertScaleAbs(dest_normalized, dest_norm_scaled);

    vector<vector<double> > output;

    for (int j = 0; j < dest_normalized.rows; j++)
    {
        for (int i = 0; i < dest_normalized.cols; i++)
        {
            if ((int) dest_normalized.at<float>(j, i) > threshold)
            {
                vector<double> point(2,0);
                point[0] = j;
                point[1] = i;
                output.push_back(point);
            }
        }
    }
    return output;
}

cv::Mat Corner::shiTomasiDrawImage(const cv::Mat &image)
{
    int maxCorners = 23;
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    Mat copy;
    copy = image.clone();
    goodFeaturesToTrack(image,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k);
    int r = 4;
    for (size_t i = 0; i < corners.size(); i++)
    {
        circle(copy, corners[i], r, Scalar(255), -1, 8, 0);
    }

    return copy;
}

std::vector<std::vector<double> > Corner::shiTomasiGetCorners(const cv::Mat &image)
{

    int maxCorners = 23;
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    Mat copy;
    copy = image.clone();
    goodFeaturesToTrack(image,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k);
    int r = 4;

    vector<vector<double> > output;
    for (size_t i = 0; i < corners.size(); i++)
    {
        vector<double> point(2, 0);
        point[0] = corners[i].x;
        point[1] = corners[i].y;
        output.push_back(point);
    }

    return output;
}

void Corner::runAll(ImgReader &reader, const cv::Mat &image, const string name)
{
    reader.saveImage(harrisDrawImage(image), name+ "harris.png");
    reader.saveImage(shiTomasiDrawImage(image), name + "shiTomasi.png");
}


