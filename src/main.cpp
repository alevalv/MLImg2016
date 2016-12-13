
#include "imgreader.h"
#include "preprocessor.h"
#include "featuredetection/Corner.h"
#include "featuredetection/Feature.h"
#include "ml/datamaker/DataMaker.h"
#include "ml/svm/svm.h"

using namespace std;
using namespace cv;

#define IMAGE_DIR "../../DRIVE/"
#define WINDOW_NAME "window"

void showImage(const Mat& image)
{
    namedWindow(WINDOW_NAME, WINDOW_FREERATIO);
    imshow(WINDOW_NAME, image);
    waitKey(0);
}

int main(int argc, char* argv[])
{

    ImgReader reader = ImgReader(IMAGE_DIR);
    reader.setPreprocessing(Preprocessor::EXTRACT_GREEN);
//    vector<string> imageFilenames = reader.getAbsoluteUrls("test/images/");
//    vector<Mat> images;
//    for (string imageName : imageFilenames)
//    {
//        images.push_back(reader.readImageAbsolute(imageName));
//    }
    //Corner corner(200);
    //corner.runAll(reader, images[0], "corner");

    //Feature feature(400);
    //feature.SURF(images[0]), "sift.png"

    DataMaker maker(5000, 100);
    map<int, std::array<Mat, 2> > images = reader.readWithGroundTruth("test/images/", "test/1st_manual/", "_");

    svm mSvm;
    mSvm.train(maker.createData(images));
    Mat image = reader.readImageAbsolute("/home/alevalv/Maestria/MacLea/SourceCode/DRIVE/training/images/21_training.tif");
    Mat seg = mSvm.predict(image);

    showImage(seg);
    return 0;
}