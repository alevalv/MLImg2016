//
// Created by alevalv on 12/12/16.
//

#include <opencv2/xfeatures2d.hpp>
#include <random>
#include "mSVM.h"


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

#define WINDOW_NAME "window"

void showImage2(const Mat& image)
{
    namedWindow(WINDOW_NAME, WINDOW_FREERATIO);
    imshow(WINDOW_NAME, image);
    waitKey(0);
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
            Mat image = createWindow(image, y, x, halfWS);
            float response = mSvm->predict(image);
            if (response == 1)
                outputImage.at<float>(y, x) = 255;
        }
        cout << "Finish row:" << y << "\n";
    }
    return outputImage;
}

mSVM::mSVM(int windowSize, int kernel)
{
    this->windowSize = windowSize;
    this->kernel = kernel;
}

