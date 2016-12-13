//
// Created by alevalv on 12/12/16.
//

#ifndef MACLEA_SVM_H
#define MACLEA_SVM_H

#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>

//STATEFUL CLASS
class svm
{
    cv::Ptr<cv::ml::SVM> mSvm;
    int windowSize;
public:
    void train(std::map<int, std::array<std::vector<cv::Mat>,2> > image, std::string savePath = "");
    cv::Mat predict(cv::Mat &image);
};


#endif //MACLEA_SVM_H
