//
// Created by alevalv on 06/12/16.
//

#include "KMeans.h"

using namespace std;
using namespace cv;

KMeans::KMeans(int centroids)
{
    this->centroids = vector<Element>(centroids);
}

KMeans::KMeans(std::vector<Element> centroids)
{
    this->centroids = centroids;
}

void KMeans::execute(Mat image)
{
    Mat input = preprocess(image);

}

void KMeans::setPreprocessing(std::function<cv::Mat(cv::Mat)> &function)
{
    this->preprocess = function;
}
