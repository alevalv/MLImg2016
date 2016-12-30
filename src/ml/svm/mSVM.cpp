//
// Created by alevalv on 12/12/16.
//

#include <opencv2/xfeatures2d.hpp>
#include "mSVM.h"

using namespace std;
using namespace cv;

void mSVM::train(map<int, array<Mat, 2> > images)
{
    array<Mat, 2> inputData = dataMaker(images);
    mSvm = ml::SVM::create();
    mSvm->setType(ml::SVM::C_SVC);
    mSvm->setKernel(kernel);
    mSvm->setGamma(3);
    mSvm->setDegree(3);

    mSvm->train(inputData[0], ml::ROW_SAMPLE, inputData[1]);
}

Mat createWindow(Mat &image, int yy, int xx, int halfWS)
{
    Mat output(1, (halfWS*2) * (halfWS*2), CV_32F, 0.0);
    int currentColumn = 0;
    for (int y = yy-halfWS; y < yy + halfWS; y++)
        for (int x = xx - halfWS; x < xx + halfWS; x++)
            output.at<float>(0, currentColumn++) = image.at<float>(y, x);
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
                outputImage.at<float>(y, x) = 200;
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
            Mat currentpix(1, 3, CV_32FC1);
            currentpix.at<float>(0, 0) = channels[0].at<float>(y, x);
            currentpix.at<float>(0, 1) = channels[1].at<float>(y, x);
            currentpix.at<float>(0, 2) = channels[2].at<float>(y, x);

            float response = mSvm->predict(currentpix);
            if (response == 1)
                outputImage.at<float>(y, x) = 1;
        }
    }
    return outputImage;
}

mSVM::mSVM(const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> &dataMaker, int windowSize, int kernel)
{
    this->dataMaker = dataMaker;
    this->windowSize = windowSize;
    this->kernel = kernel;
}

void mSVM::setDataMaker(const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> &dataMaker)
{
    this->dataMaker = dataMaker;
}
