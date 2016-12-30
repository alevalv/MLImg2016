
#include <cstdlib>
#include <unistd.h>
#include <getopt.h>
#include "image/imgreader.h"
#include "image/preprocessor.h"
#include "featuredetection/Corner.h"
#include "featuredetection/Feature.h"
#include "ml/datamaker/DataMaker.h"
#include "ml/svm/mSVM.h"
#include "util.h"
#include "retina/RetinaUtils.h"
#include "../lib/prettyprint.hpp"
#include "ml/knearest/KNearest.h"

using namespace std;
using namespace cv;

#define USAGE "maclea -c -f -s -a -k kernel_type -w window_size -i image_count -d image_dir -o source_dir(relpath) -g groundt_dir(relpath) -t target_image_path \n"

static const char *optString = "cfsna:k:w:i:d:o:g:t:!:h?";

static const struct option longOpts[] =
    {
        {"corner",            no_argument,       NULL, 'c'},
        {"feature",           no_argument,       NULL, 'f'},
        {"mSVM",              no_argument,       NULL, 's'},
        {"mSVM2",             required_argument, NULL, 'a'},
        {"kernel-type",       required_argument, NULL, 'k'},
        {"window-size",       required_argument, NULL, 'w'},
        {"image-count",       required_argument, NULL, 'i'},
        {"help",              no_argument,       NULL, '?'},
        {"image-directory",   required_argument, NULL, 'd'},
        {"sourcei-directory", required_argument, NULL, 'o'},
        {"groundt-directory", required_argument, NULL, 'g'},
        {"target-image",      required_argument, NULL, 't'},
        {"k-means",           no_argument,       NULL, '0'}
    };

int main(int argc, char *argv[])
{
    bool testing = false;
    int option = 0;
    int corner = 0, feature = 0, use_svm = 0,  use_svm2 = 0, use_corner = 0, use_kmeans = 0, use_knearest = 0,
        kernel = -1, window_size = 30, image_count = 5000;
    int long_index;
    string image_dir, source_images_dir, ground_truth_dir, target_image_path;
    if (argc < 2)
    {
        cout << USAGE;
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
            case 'a':
                use_svm2 = 1;
                use_corner = atoi(optarg);
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
            case '0':
                use_kmeans = 1;
                break;
            case 'n':
                use_knearest = 1;
                break;
            case 'h':
            case '?':
            default:
                cout << USAGE;
                exit(EXIT_FAILURE);
                break;
        }
    }

    //sets the image reader with the given folder path
    ImgReader reader = ImgReader(image_dir);
    reader.setPreprocessing(Preprocessor::EXTRACT_GREEN);

    if (testing)
    {
        Mat image = reader.readImageAbsolute(target_image_path);
        vector<double> od = RetinaUtils::findOpticalDisk(image, false);

        cout << Util::getCircle(od[0], od[1], 10, 1000, 1000);
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
            Corner cornerC;
            cornerC.runAll(reader, images[0], "corner");
        }
        else
        {
            Feature featureC;
            Mat image = featureC.SURFDrawImage(images[0]);
            reader.saveImage(image, "surf.png");
        }
    }
    else if (use_svm || use_svm2)
    {
        if (source_images_dir.empty() || ground_truth_dir.empty())
        {
            cout << "-o and -g are mandatory for -s\n";
            exit(EXIT_FAILURE);
        }
        Mat seg;
        string outputFile = "svm" + to_string(kernel) + "-" + to_string(window_size);
        if (use_svm)
        {
            DataMaker::maxCount = image_count;
            DataMaker::windowSize = window_size;
            reader.setPreprocessing(Preprocessor::EXTRACT_GREEN);
            map<int, std::array<Mat, 2> > images = reader.readWithGroundTruth(source_images_dir, ground_truth_dir, "_");
            mSVM mSvm(DataMaker::WINDOW, window_size, kernel);
            mSvm.train(images);
            Mat image = reader.readImage(target_image_path);
            seg = mSvm.predict(image);
            outputFile+="ts";
        }
        else
        {
            reader.setPreprocessing(Preprocessor::GREEN_DUAL_GRADIENT);
            map<int, std::array<Mat, 2> > images = reader.readWithGroundTruth(source_images_dir, ground_truth_dir, "_");
            mSVM mSVM(DataMaker::OPTICAL_DISK_SURF, window_size, kernel);
            if (use_corner)
            {
                mSVM.setDataMaker(DataMaker::OPTICAL_DISK_CORNERS);
            }
            mSVM.train(images);
            Mat image = reader.readImage(target_image_path);
            seg = mSVM.predict2(image);
            outputFile+="ta";
        }
        outputFile+=".png";
        Util::showImage(seg);
        //reader.saveImage(seg, outputFile);
    }
    else if(use_knearest)
    {
        DataMaker::maxCount = 4100;
        reader.setPreprocessing(Preprocessor::GREEN_DUAL_GRADIENT);
        map<int, std::array<Mat, 2> > images = reader.readWithGroundTruth(source_images_dir, ground_truth_dir, "_");

        Mat image = reader.readImage(target_image_path);
        KNearest knearest(DataMaker::RANDOM_PIXELS);
        knearest.train(images);
        Mat output = knearest.predict(image);
        Util::showImage(output);
    }
    return 0;
}