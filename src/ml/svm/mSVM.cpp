//
// Created by alevalv on 12/12/16.
//

#include <opencv2/xfeatures2d.hpp>
#include <random>
#include "mSVM.h"
#include "../../retina/RetinaUtils.h"
#include "../../util.h"
#include "../../../lib/prettyprint.hpp"

using namespace std;
using namespace cv;

void mSVM::train(map<int, array<vector<Mat>, 2> > images, string savePath)
{
    int imageCount = 0;
    int imageSize = images[1][0][0].cols * images[1][0][0].rows;
    windowSize = images[1][0][0].cols;
    for (auto const &item : images)
    {
        imageCount += 60;
        //imageCount+=item.second[0].size() + item.second[1].size();
    }
    //cout<<imageCount<<":"<<imageSize<<endl;

    Mat trainingData(imageCount, imageSize, CV_32F);

    mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> random;

    int currentImage = 0;
    for (auto const &item: images)
    {
        for (int cmi = 0; cmi < 30; cmi++)
        {
            long randomImage = random() % item.second[0].size();
            int currentColumn = 0;
            for (int y = 0; y < item.second[0][randomImage].rows; y++)
            {
                for (int x = 0; x < item.second[0][randomImage].cols; x++)
                {
                    trainingData.at<int>(currentImage, currentColumn) = item.second[0][randomImage].at<int>(y, x);
                    trainingData.at<int>(currentImage + 1, currentColumn) = item.second[1][randomImage].at<int>(y, x);
                    currentColumn++;
                }
            }
            currentImage += 2;
        }
    }

    Mat labels(imageCount, 1, CV_32SC1);

    for (int i = 1; i <= imageCount; i++)
        labels.at<int>(i - 1, 0) = (i % 2);

    mSvm = ml::SVM::create();
    mSvm->setType(ml::SVM::C_SVC);
    mSvm->setKernel(kernel);
    mSvm->setGamma(3);
    mSvm->setDegree(3);

    mSvm->train(trainingData, ml::ROW_SAMPLE, labels);

    if (savePath != "")
    {
        mSvm->save(savePath);
    }
}

//original image should have three channels, 1st with original green, 2nd with first gradient and 3rd with second gradient
void mSVM::train2(map<int, array<Mat, 2> > images, bool useCorners, string savePath)
{

    vector<Mat> trainingDataVector;
    vector<Mat> labelsVector;
    Mat trainingData;
    Mat labels;
    for (auto& item : images)
    {
        Mat channels[3];
        split(item.second[0], channels);

        vector<double> opticalDisk = RetinaUtils::findOpticalDisk(channels[0], useCorners);

        //Util::showImage(RetinaUtils::drawOpticalDiskLocation(opticalDisk, channels[0]));
        //cout<<item.first<<" "<<opticalDisk<<endl;

        vector<Point2d> points;
        for (int i=12; i <=15; i+=1)
        {
            vector<Point2d> tmpPoints = Util::getCircle((int)opticalDisk[0], (int)opticalDisk[1], i, channels[0].rows, channels[0].cols);
            points.insert(std::end(points), std::begin(tmpPoints), std::end(tmpPoints));
        }

        Mat tmpTrainingData(points.size(), 5, CV_32F, 0.0);
        Mat tmpLabels(points.size(), 1, CV_32SC1, 0.0);
        int currentTD = 0;

        for (auto& point : points)
        {
            tmpTrainingData.at<float>(currentTD, 0) = channels[0].at<float>(point.x, point.y);
            tmpTrainingData.at<float>(currentTD, 1) = channels[1].at<float>(point.x, point.y);
            tmpTrainingData.at<float>(currentTD, 2) = channels[2].at<float>(point.x, point.y);
            tmpTrainingData.at<float>(currentTD, 3) = point.x;
            tmpTrainingData.at<float>(currentTD, 4) = point.y;

            if (images[1][1].at<int>(point.x, point.y) > 50)
            {
                tmpLabels.at<int>(currentTD, 0) = 1;
            }
            else
            {
                tmpLabels.at<int>(currentTD, 0) = 0;
            }
            currentTD++;
        }
        vconcat(tmpTrainingData, trainingData);
        vconcat(tmpLabels, labels);
    }

    mSvm = ml::SVM::create();
    mSvm->setType(ml::SVM::C_SVC);
    mSvm->setKernel(kernel);
    mSvm->setGamma(3);
    mSvm->setDegree(3);

    mSvm->train(trainingData, ml::ROW_SAMPLE, labels);
}
Mat createWindow(Mat &image, int yy, int xx, int halfWS)
{
    Mat output(1, (halfWS*2) * (halfWS*2), CV_32F);
    int currentColumn = 0;
    for (int y = yy-halfWS; y < yy + halfWS; y++)
        for (int x = xx - halfWS; x < xx + halfWS; x++)
            output.at<int>(0, currentColumn++) = image.at<int>(y, x);
    return output;
}

Mat mSVM::predict(cv::Mat &image)
{
    int halfWS = windowSize/2;
    Mat outputImage(image.rows, image.cols, CV_8U, 0.0);
    cout<<"Evaluating "<<image.rows*image.cols<<" pixels\n";
    for (int y = windowSize; y < (image.rows - windowSize); y++)
    {
        for (int x = windowSize; x < (image.cols - windowSize); x++)
        {
            Mat image2 = createWindow(image, y, x, halfWS);
            float response = mSvm->predict(image2);
            if (response == 1)
                outputImage.at<float>(y, x) = 255;
        }
    }
    return outputImage;
}

Mat mSVM::predict2(cv::Mat &image)
{
    Mat channels[3];
    split(image, channels);

    Mat outputImage(image.rows, image.cols, CV_32SC1, 0.0);
    cout<<"2Evaluating "<<image.rows*image.cols<<" pixels\n";
    for (int y = 0; y < outputImage.rows; y++)
    {
        for (int x = 0; x < outputImage.cols ; x++)
        {
            Mat currentpix(1, 5, CV_32FC1);
            currentpix.at<float>(0, 0) = channels[0].at<float>(y, x);
            currentpix.at<float>(0, 1) = channels[1].at<float>(y, x);
            currentpix.at<float>(0, 2) = channels[2].at<float>(y, x);
            currentpix.at<float>(0, 3) = x;
            currentpix.at<float>(0, 4) = y;

            float response = mSvm->predict(currentpix);
            if (response == 1)
                outputImage.at<float>(y, x) = 1;
        }
    }
    return outputImage;
}

mSVM::mSVM(int windowSize, int kernel)
{
    this->windowSize = windowSize;
    this->kernel = kernel;
}

