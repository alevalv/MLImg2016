#include "imagemaker.h"
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;

ImageMaker::ImageMaker(const std::string filename, const int startingNumber, const int windowSize)
{
    this->fileName = filename;
    this->startingNumber = startingNumber;
    this->windowSize = windowSize;
}


std::vector<Mat> ImageMaker::createFrom(RetinalImage& image)
{
    std::cout<<"creating from"<<image.getCode()<<std::endl;
    std::cout<<"creating from"<<image.getGroundTruth().rows<<":"<<image.getGroundTruth().rows<<std::endl;
    std::cout<<"creating from"<<image.getOriginal().rows<<":"<<image.getOriginal().rows<<std::endl;
    Mat groundTruth = image.getGroundTruth();
    std::vector<Mat> outputImages;

    int w = windowSize/2;
    for (int i=windowSize; i<(groundTruth.rows-windowSize); i++)
    {
        for (int j=windowSize; j<(groundTruth.cols-windowSize); j++)
        {
            if (groundTruth.at<int>(i,j) != 0)
            {
                Rect region(i-w, j-w, w, w);
                outputImages.push_back(image.getOriginal()(region));
            }
        }
    }

    return outputImages;
}
