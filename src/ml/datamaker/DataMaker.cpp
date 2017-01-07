//
// Created by alevalv on 11/12/16.
//

#include <cstdlib>
#include <random>
#include <unordered_set>
#include <functional>
#include "DataMaker.h"
#include "../../retina/RetinaUtils.h"
#include "../../util.h"

using namespace std;
using namespace cv;

int DataMaker::maxCount = 1000;
int DataMaker::windowSize = 30;

/**
 * this method creates a set of windows for all given images, sorting them in two groups, one that in the center has
 * a pixel that is a vein and one that does not.
 */
map<int, array<vector<Mat>, 2>> DataMaker::createData(
    map<int, array<Mat, 2> > &inputImages, int threshold)
{
    map<int, array<vector<Mat>, 2> > createdImages;
    for (auto const &item : inputImages)
    {
        Mat oImage = item.second[0];
        Mat gtImage = item.second[1];
        int halfWS = windowSize / 2;
        int currentImageCountYes = 0;
        int currentImageCountNo = 0;
        for (int y = windowSize; y < (oImage.rows - windowSize); y++)
        {
            for (int x = windowSize; x < (oImage.cols - windowSize); x++)
            {
                if (currentImageCountYes < maxCount && oImage.at<int>(y, x) > threshold &&
                    gtImage.at<int>(y, x) > threshold)
                {
                    Rect roi(x - halfWS, y - halfWS, windowSize, windowSize);
                    createdImages[item.first][0].push_back(oImage(roi));
                    currentImageCountYes++;
                }
                if (currentImageCountNo < (maxCount * 8) && oImage.at<int>(y, x) > threshold &&
                    gtImage.at<int>(y, x) < threshold)
                {
                    Rect roi(y - halfWS, x - halfWS, windowSize, windowSize);
                    createdImages[item.first][1].push_back(oImage(roi));
                    currentImageCountNo++;
                }
            }
        }
    }

    //randomly select the same quantity of images as yes for no category
    mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> random;  //TODO make it truly random
    for (auto &item : createdImages)
    {
        unordered_set<long> selectedImageIds;
        long maxImageCount = item.second[0].size();
        long imageCount = 0;
        vector<Mat> selectedImages;
        while (imageCount < maxImageCount)
        {
            long imageId = random() % item.second[0].size();
            if (selectedImageIds.find(imageId) == selectedImageIds.end())
            {
                selectedImageIds.insert(imageId);
                selectedImages.push_back(item.second[1][imageId]);
                imageCount++;
            }
        }
        item.second[1] = selectedImages;
    }
    //debugInfo(createdImages);
    return createdImages;
}

const function<array<Mat, 2>(map<int, array<Mat, 2> > &, bool)> OPTICAL_DISK = [](map<int, array<Mat, 2> > &images,
                                                                                  bool corner) -> array<Mat, 2>
{
    vector<Mat> trainingDataVector;
    vector<Mat> labelsVector;

    for (auto &item : images)
    {
        Mat channels[3];
        split(item.second[0], channels);

        vector<double> opticalDisk = RetinaUtils::findOpticalDisk(channels[0], corner);

        //Util::showImage(RetinaUtils::drawOpticalDiskLocation(opticalDisk, channels[0]));
        //cout<<item.first<<" "<<opticalDisk<<endl;

        vector<Point2d> points;
        for (int i = 10; i <= 15; i += 1)
        {
            vector<Point2d> tmpPoints = Util::getCircle((int) opticalDisk[0], (int) opticalDisk[1], i, channels[0].rows,
                                                        channels[0].cols);
            points.insert(std::end(points), std::begin(tmpPoints), std::end(tmpPoints));
        }

        Mat tmpTrainingData(points.size(), 3, CV_32F, 0.0);
        Mat tmpLabels(points.size(), 1, CV_32SC1, 0.0);
        int currentTD = 0;

        for (auto &point : points)
        {
            tmpTrainingData.at<float>(currentTD, 0) = channels[0].at<float>(point.x, point.y);
            tmpTrainingData.at<float>(currentTD, 1) = channels[1].at<float>(point.x, point.y);
            tmpTrainingData.at<float>(currentTD, 2) = channels[2].at<float>(point.x, point.y);

            if (images[1][1].at<int>(point.x, point.y) > 50)
            {
                tmpLabels.at<int>(currentTD, 0) = 1;
            }
            else
            {
                tmpLabels.at<int>(currentTD, 0) = 0;
            }
            currentTD++;
        }

        //cout << "input vectors: " << tmpTrainingData.rows << " features: " << tmpTrainingData.cols << "\n";
        trainingDataVector.push_back(tmpTrainingData);
        labelsVector.push_back(tmpLabels);
    }

    int count = 0;
    for (auto &tData : trainingDataVector)
    {
        count += tData.rows;
    }
    Mat trainingData(count, 3, CV_32FC1, 0.0);
    Mat labels(count, 1, CV_32SC1, 0.0);
    int currentRow = 0;
    for (int j = 0; j < trainingDataVector.size(); j++)
    {
        for (int i = 0; i < trainingDataVector[j].rows; i++)
        {
            trainingData.at<int>(currentRow, 0) = trainingDataVector[j].at<int>(i, 0);
            trainingData.at<int>(currentRow, 1) = trainingDataVector[j].at<int>(i, 1);
            trainingData.at<int>(currentRow, 2) = trainingDataVector[j].at<int>(i, 2);
            labels.at<int>(currentRow, 0) = labelsVector[j].at<int>(i, 0);
        }
        currentRow++;
    }
    array<Mat, 2> output;
    output[0] = trainingData;
    output[1] = labels;
    return output;
};

const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> DataMaker::OPTICAL_DISK_CORNERS = [](
    map<int, array<Mat, 2> > &images) -> array<Mat, 2>
{
    return OPTICAL_DISK(images, true);
};

const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> DataMaker::OPTICAL_DISK_SURF = [](
    map<int, array<Mat, 2> > &images) -> array<Mat, 2>
{
    return OPTICAL_DISK(images, false);
};

const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> DataMaker::WINDOW = [](
    map<int, array<Mat, 2> > &inputImages) -> array<Mat, 2>
{
    map<int, array<vector<Mat>, 2> > images = createData(inputImages);
    int imageCount = 0;
    int imageSize = images[1][0][0].cols * images[1][0][0].rows;
    int windowSize = images[1][0][0].cols;
    for (auto const &item : images)
    {
        imageCount += 60;
        //imageCount+=item.second[0].size() + item.second[1].size();
    }
    //cout<<imageCount<<":"<<imageSize<<endl;

    Mat trainingData(imageCount, imageSize, CV_32F);

    mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> random;

    int currentImage = 0;
    for (auto const &item: images)
    {
        for (int cmi = 0; cmi < 30; cmi++)
        {
            long randomImage = random() % item.second[0].size();
            int currentColumn = 0;
            for (int y = 0; y < item.second[0][randomImage].rows; y++)
            {
                for (int x = 0; x < item.second[0][randomImage].cols; x++)
                {
                    trainingData.at<int>(currentImage, currentColumn) = item.second[0][randomImage].at<int>(y, x);
                    trainingData.at<int>(currentImage + 1, currentColumn) =
                        item.second[1][randomImage].at<int>(y, x);
                    currentColumn++;
                }
            }
            currentImage += 2;
        }
    }

    Mat labels(imageCount, 1, CV_32SC1);

    for (int i = 1; i <= imageCount; i++)
    {
        labels.at<int>(i - 1, 0) = (i % 2);
    }

    array<Mat, 2> output;
    output[0] = trainingData;
    output[1] = labels;

    return output;
};

const function<array<Mat, 2>(map<int, array<Mat, 2> > &)> DataMaker::RANDOM_PIXELS = [](
    map<int, array<Mat, 2> > &inputImages) -> array<Mat, 2>
{
    Mat trainingData(maxCount*(inputImages.size()), 3, CV_32FC1, 0.0);
    Mat labels(maxCount*(inputImages.size()), 1, CV_32SC1);
    int currentImage = 0;

    mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> random;

    for (auto &item : inputImages)
    {
        Mat channels[3];
        split(item.second[0], channels);
        int localCount = 0;
        while((localCount+1) % (maxCount+1))
        {
            int x = random() % item.second[0].cols;
            int y = random() % item.second[0].rows;
            trainingData.at<int>(currentImage, 0) = channels[0].at<int>(y, x);
            trainingData.at<int>(currentImage, 1) = channels[1].at<int>(y, x);
            trainingData.at<int>(currentImage, 2) = channels[2].at<int>(y, x);
            if (item.second[1].at<int>(y, x) > 50)
            {
                labels.at<int>(y, x) = 1;
            }
            else
            {
                labels.at<int>(y, x) = 0;
            }
            currentImage++;
            localCount++;
        }
    }

    array<Mat, 2> output;
    output[0] = trainingData;
    output[1] = labels;

    return output;
};
