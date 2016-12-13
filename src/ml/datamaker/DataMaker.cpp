//
// Created by alevalv on 11/12/16.
//

#include <stdlib.h>
#include <random>
#include <unordered_set>
#include "DataMaker.h"

using namespace std;
using namespace cv;

DataMaker::DataMaker(int maxCountImages, int threshold, int windowSize)
{
    this->maxCountImages = maxCountImages;
    this->threshold = threshold;
    this->windowSize = windowSize;
}

void debugInfo(map<int, array<vector<Mat>, 2>> &createdImages)
{
    for (auto const &item : createdImages)
    {
        cout << "Image " << item.first << " Yes:" << item.second[0].size() << "No:" << item.second[1].size() << "\n";
    }
}

map<int, array<vector<Mat>, 2>> DataMaker::createData(map<int, array<Mat, 2> > &inputImages)
{
    std::map<int, array<vector<Mat>, 2> > createdImages;
    for (auto const &item : inputImages)
    {
        Mat oImage = item.second[0];
        Mat gtImage = item.second[1];
        int halfWS = windowSize / 2;
        int currentImageCountYes = 0;
        int currentImageCountNo = 0;
        for (int i = windowSize; i < (oImage.cols - windowSize); i++)
        {
            for (int j = windowSize; j < (oImage.rows - windowSize); j++)
            {
                if (currentImageCountYes < maxCountImages && oImage.at<int>(j, i) > threshold &&
                    gtImage.at<int>(i, j) > threshold)
                {
                    Rect roi(i - halfWS, j - halfWS, windowSize, windowSize);
                    createdImages[item.first][0].push_back(oImage(roi));
                    currentImageCountYes++;
                }
                if (currentImageCountNo < (maxCountImages * 8) && oImage.at<int>(j, i) > threshold &&
                    gtImage.at<int>(i, j) < threshold)
                {
                    Rect roi(i - halfWS, j - halfWS, windowSize, windowSize);
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
        0xefc60000, 18, 1812433253> random;
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
