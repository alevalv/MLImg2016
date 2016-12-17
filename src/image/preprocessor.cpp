//
// Created by alevalv on 11/12/16.
//

#include <cmath>
#include "preprocessor.h"

const function<Mat(Mat &)> Preprocessor::NONE = [] (cv::Mat &image) -> cv::Mat
{
    return image;
};

const function<Mat(Mat &)> Preprocessor::EXTRACT_GREEN = [](Mat &image) -> Mat
{
    Mat channels[3];
    split(image.clone(), channels);
    return channels[1];
};

const function<Mat(Mat &)> Preprocessor::GRADIENT = [](Mat &image) -> Mat
{
    Mat outputX, outputY, abX, abY;
    Mat output(image.rows, image.cols, CV_8UC1, 0.0);

    Sobel(image, outputX, CV_32FC1, 1, 0);
    Sobel(image, outputY, CV_32FC1, 0, 1);
    convertScaleAbs(outputX, abX);
    convertScaleAbs(outputY, abY);
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            uchar xx = abX.at<uchar>(y,x);
            uchar yy = abY.at<uchar>(y,x);
            output.at<uchar>(y,x) = sqrt(xx*xx+yy*yy);
        }
    }
    return output;
};

const function<Mat(Mat &)> Preprocessor::GRADIENT2 = [](Mat &image) -> Mat
{
    Mat output;
    Laplacian(image, output, CV_8UC1);

    return output;
};

const function<Mat(Mat &)> Preprocessor::GREEN_DUAL_GRADIENT = [](Mat &image) -> Mat
{
    Mat output, green;

    GaussianBlur(EXTRACT_GREEN(image), green, Size(3, 3), 0, 0);

    merge(vector<Mat>{green, GRADIENT(green), GRADIENT2(green)}, output);

    return output;
};