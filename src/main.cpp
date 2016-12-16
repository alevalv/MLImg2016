
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <libltdl/lt_system.h>
#include "imgreader.h"
#include "preprocessor.h"
#include "featuredetection/Corner.h"
#include "featuredetection/Feature.h"
#include "ml/datamaker/DataMaker.h"
#include "ml/svm/mSVM.h"
#include "ml/kmeans/KMeans.h"
#include "util.h"

using namespace std;
using namespace cv;

#define IMAGE_DIR "../../DRIVE/"
#define WINDOW_NAME "window"
#define USAGE "maclea -c -f -s -k kernel_type -w window_size -i image_count -d image_dir -o source_dir(relpath) -g groundt_dir(relpath) -t target_image_path \n"

void showImage(const Mat& image)
{
    namedWindow(WINDOW_NAME, WINDOW_FREERATIO);
    imshow(WINDOW_NAME, image);
    waitKey(0);
}

static const char *optString = "cfsk:w:i:d:o:g:t:!:h?";

static const struct option longOpts[] =
    {
        {"corner", no_argument, NULL, 'c'},
        {"feature", no_argument, NULL, 'f'},
        {"mSVM", no_argument, NULL, 's'},
        {"kernel-type", required_argument, NULL, 'k'},
        {"window-size", required_argument, NULL, 'w'},
        {"image-count", required_argument, NULL, 'i'},
        {"help", no_argument, NULL, '?'},
        {"image-directory", required_argument, NULL, 'd'},
        {"sourcei-directory", required_argument, NULL, 'o'},
        {"groundt-directory", required_argument, NULL, 'g'},
        {"target-image", required_argument, NULL, 't'}
    };

int main(int argc, char* argv[])
{
    bool testing = false;
    int option = 0;
    int corner = 0, feature = 0, use_svm = 0, kernel = -1, window_size = 30, image_count = 5000;
    int long_index;
    string image_dir, source_images_dir, ground_truth_dir, target_image_path;
    if (argc < 2)
    {
        cout<<USAGE;
        exit(EXIT_FAILURE);
    }
    while ((option = getopt_long(argc, argv, optString, longOpts, &long_index)) != -1)
    {
        switch (option)
        {
            case 'c':
                corner = 1;
                break;
            case 'f':
                feature = 1;
                break;
            case 's':
                use_svm = 1;
                break;
            case 'k':
                kernel = atoi(optarg);
                break;
            case 'w':
                window_size = atoi(optarg);
                break;
            case 'i':
                image_count = atoi(optarg);
                break;
            case 'd':
                image_dir = string(optarg);
                break;
            case 'o':
                source_images_dir = string(optarg);
                break;
            case 'g':
                ground_truth_dir = string(optarg);
                break;
            case '!':
                testing = true;
            case 't':
                target_image_path = string(optarg);
                break;
            case 'h':
            case '?':
            default:
                cout<<USAGE;
                exit(EXIT_FAILURE);
                break;
        }
    }

    //sets the image reader with the given folder path
    ImgReader reader = ImgReader(image_dir);
    reader.setPreprocessing(Preprocessor::EXTRACT_GREEN);

    if (testing)
    {
        KMeans kmeans(4, 2, 500);
        vector<int> tags = kmeans.execute(vector<vector<double> >{vector<double>{20,20}});
        cout<<Util::vectorToString(kmeans.getCentroids());
        cout<<tags[0]<<endl;
    }
    else if (corner || feature)
    {
        vector<string> imageFilenames = reader.getAbsoluteUrls(source_images_dir);
        vector<Mat> images;
        for (string imageName : imageFilenames)
        {
            images.push_back(reader.readImageAbsolute(imageName));
        }
        if (corner)
        {
            Corner corner(200);
            corner.runAll(reader, images[0], "corner");
        }
        else
        {
            Feature feature(400);
            Mat image = feature.SURF(images[0]);
            reader.saveImage(image, "surf.png");
        }
    }
    else if (use_svm)
    {
        if (source_images_dir.empty() || ground_truth_dir.empty())
        {
            cout<<"-o and -g are mandatory for -s\n";
            exit(EXIT_FAILURE);
        }
        reader.setPreprocessing(Preprocessor::GREEN_DUAL_GRADIENT);
        DataMaker maker(image_count, 100);
        map<int, std::array<Mat, 2> > images = reader.readWithGroundTruth(source_images_dir, ground_truth_dir, "_");
        mSVM mSvm(window_size, kernel);
        mSvm.train(maker.createData(images));
        Mat image = reader.readImageAbsolute(target_image_path); // /home/alevalv/Maestria/MacLea/SourceCode/DRIVE/training/images/21_training.tif
        Mat seg = mSvm.predict(image);
        string outputfile = "svm";
        outputfile.append(""+kernel);
        outputfile.append("-");
        outputfile.append(""+window_size);
        outputfile.append(".png");

        reader.saveImage(seg, outputfile);
    }
    return 0;
}