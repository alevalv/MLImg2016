//
// Created by alevalv on 15/12/16.
//

#include <opencv2/opencv.hpp>
#include <chrono>
#include <unordered_set>
#include "KNearest.h"
#include "../../util.h"
#include "../../log/Logger.h"

using namespace std;
using namespace cv;

KNearest::KNearest(const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> &dataMaker)
{
    this->dataMaker = dataMaker;
}

void KNearest::train(map<int, array<Mat, 2> > images)
{
    array<Mat, 2> data = dataMaker(images);
    Logger::getLogger()->info("Input vectors: "+to_string(data[0].rows)+" features: "+to_string(data[0].cols)+"\n");
    knearest = ml::KNearest::create();
    knearest->setAlgorithmType(ml::KNearest::BRUTE_FORCE);
    knearest->setIsClassifier(true);
    knearest->train(data[0], ml::ROW_SAMPLE, data[1]);
}

cv::Mat KNearest::predict(cv::Mat &image)
{
    ILogger* logger = Logger::getLogger();
    Mat channels[3];
    split(image, channels);
    Mat outputImage(image.rows, image.cols, CV_32SC1, 0.0);
    logger->info("KNearest-Evaluating:"+to_string(image.rows*image.cols)+" pixels\n");
    std::unordered_set<float> responses;
    for (int y = 0; y < outputImage.rows; y++)
    {
        logger->info("crow:"+std::to_string(y)+"t:"+Benchmark::getCurrentTimeAndDate());
        for (int x = 0; x < outputImage.cols; x++)
        {
            Mat currentpix(1, 3, CV_32FC1);
            currentpix.at<float>(0, 0) = channels[0].at<float>(y, x);
            currentpix.at<float>(0, 1) = channels[1].at<float>(y, x);
            currentpix.at<float>(0, 2) = channels[2].at<float>(y, x);

            float response = knearest->predict(currentpix);
            auto search = responses.find(response);
            if (search == responses.end())
            {
                logger->info(to_string(response));
                responses.insert(response);
            }
            if (response == 0.0)
                outputImage.at<float>(y, x) = 255;
        }
    }
    return outputImage;
}
