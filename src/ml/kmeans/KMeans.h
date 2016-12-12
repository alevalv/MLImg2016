//
// Created by alevalv on 06/12/16.
//

#ifndef MACLEA_KMEANS_H
#define MACLEA_KMEANS_H

#include <vector>
#include <opencv2/core/mat.hpp>
#include <functional>
#include <cv.hpp>
#include "element/Element.h"

class KMeans {
    std::function<cv::Mat(cv::Mat)> preprocess = [] (cv::Mat image) -> cv::Mat
    {
        cv::Mat sobel;
        cv::Sobel(image, sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);


        return sobel;
    };
    std::vector<Element> centroids;
    cv::Mat elementMatrix;
public:
    KMeans(int centroids);
    KMeans(std::vector<Element> centroids);
    void execute(cv::Mat image);
    void setPreprocessing(std::function<cv::Mat(cv::Mat)> &function);
};
#endif //MACLEA_KMEANS_H
