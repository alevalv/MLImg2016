//
// Created by alevalv on 06/12/16.
//

#ifndef MACLEA_KMEANS_H
#define MACLEA_KMEANS_H

#include <opencv2/core/mat.hpp>
#include <functional>
#include <cv.hpp>

class KMeans {
    std::vector<std::vector<double> > centroids;
public:
    double epsilon = 0.001;
    KMeans(int centroidCount, int elementSize, int maxValue);
    KMeans(std::vector<std::vector<double> > centroids);
    void execute(cv::Mat image);
    std::vector<int> execute(std::vector<std::vector<double> > elements);
    std::vector<std::vector<double> > getCentroids();
};
#endif //MACLEA_KMEANS_H
