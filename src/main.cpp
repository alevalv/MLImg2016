
#include "imgreader.h"
#include "preprocessor.h"
#include "featuredetection/Harris.h"

using namespace std;
using namespace cv;

#define IMAGE_DIR "../../DRIVE/"
#define WINDOW_NAME "window"

int main(int argc, char* argv[])
{
    namedWindow(WINDOW_NAME, WINDOW_FREERATIO);

    ImgReader reader = ImgReader(IMAGE_DIR);
    reader.setPreprocessing(Preprocessor::EXTRACT_GREEN);
    vector<string> imageFilenames = reader.getAbsoluteUrls("test/images/");
    vector<Mat> images;
    for (string imageName : imageFilenames)
    {
        images.push_back(reader.readImage(imageName));
    }
    Harris harris(240);
    imshow(WINDOW_NAME, harris.getHarrisCorners(images[0]));
    waitKey(0);

    return 0;
}