#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace cv::ml;

int ML(int argc, char** argv)
{
    Ptr<ml::SVM> svm = ml::SVM::create();
    svm->setType(ml::SVM::C_SVC);
    svm->setKernel(ml::SVM::POLY);
    svm->setGamma(3);

    Mat trainingData; //one row per feature
    Mat labels;
    svm->train(trainingData, ml::ROW_SAMPLE, labels);

    return 0;
}
