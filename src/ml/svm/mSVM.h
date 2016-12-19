//
// Created by alevalv on 12/12/16.
//

#ifndef MACLEA_SVM_H
#define MACLEA_SVM_H

#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>

//STATEFUL CLASS
class mSVM
{
    int windowSize;
    int kernel;
    cv::Ptr<cv::ml::SVM> mSvm;
public:
    mSVM(int windowSize = 20, int kernel = cv::ml::SVM::LINEAR);

    void train(std::map<int, std::array<std::vector<cv::Mat>, 2> > image, std::string savePath = "");

    void train2(std::map<int, std::array<cv::Mat, 2> > image, bool useCorners = true, std::string savePath = "");

    cv::Mat predict(cv::Mat &image);

    cv::Mat predict2(cv::Mat &image);
};


#endif //MACLEA_SVM_H
