
#include "imgreader.h"
#include "preprocessor.h"
#include "featuredetection/Corner.h"
#include "featuredetection/Feature.h"

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
    vector<string> imageFilenames = reader.getAbsoluteUrls("test/images/");
    vector<Mat> images;
    for (string imageName : imageFilenames)
    {
        images.push_back(reader.readImage(imageName));
    }
    //Corner corner(200);
    //corner.runAll(reader, images[0], "corner");

    Feature feature;
    reader.saveImage(feature.SURF(images[0], 400), "sift.png");
    return 0;
}