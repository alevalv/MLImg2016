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
    static std::vector<double> findBiggestCentroid(std::vector<int> labels, std::vector<std::vector<double> > centroids);

    double epsilon = 0.001;
    double maxIterations = 1000;


    KMeans(int centroidCount, int elementSize, int maxValue);
    KMeans(std::vector<std::vector<double> > centroids);
    void execute(cv::Mat image);
    std::vector<int> execute(std::vector<std::vector<double> > elements);
    std::vector<std::vector<double> > getCentroids();
};
#endif //MACLEA_KMEANS_H
