//
// Created by alevalv on 12/12/16.
//

#ifndef MACLEA_SVM_H
#define MACLEA_SVM_H

#include <functional>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>
#include "../../Benchmark.h"

//STATEFUL CLASS
class mSVM
{
    int windowSize;
    int kernel;
    cv::Ptr<cv::ml::SVM> mSvm;
    std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> dataMaker;
public:
    mSVM(const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> &dataMaker, int windowSize = 20, int kernel = cv::ml::SVM::LINEAR);

    void train(std::map<int, std::array<cv::Mat, 2> > image);

    void setDataMaker(const std::function<std::array<cv::Mat, 2>(std::map<int, std::array<cv::Mat, 2> > &)> &dataMaker);

    cv::Mat predict(cv::Mat &image);

    cv::Mat predict2(cv::Mat &image);
};


#endif //MACLEA_SVM_H
