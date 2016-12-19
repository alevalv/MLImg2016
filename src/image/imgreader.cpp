#include <dirent.h>
#include <iostream>
#include "imgreader.h"
#include "../util.h"

using namespace cv;
using namespace std;

ImgReader::ImgReader(const string baseUrl)
{
    this->baseurl = baseUrl;
}

vector<string> ImgReader::getUrls(const string folder)
{
    vector<string> imageUrls;
    string path = baseurl + folder;
    auto directory = opendir(path.c_str());
    auto entity = readdir(directory);
    while (entity != NULL)
    {
        if(entity->d_type == DT_REG)
        {
            imageUrls.push_back(string(entity->d_name));
        }
        entity = readdir(directory);
    }

    closedir(directory);

    return imageUrls;
}

vector<string> ImgReader::getAbsoluteUrls(const string folder)
{
    vector<string> imageUrls;
    string path = baseurl + folder;
    auto directory = opendir(path.c_str());
    auto entity = readdir(directory);
    while (entity != NULL)
    {
        if(entity->d_type == DT_REG)
        {
            imageUrls.push_back(path + string(entity->d_name));
        }
        entity = readdir(directory);
    }

    closedir(directory);

    return imageUrls;
}

Mat ImgReader::readImageAbsolute(const string url)
{
    Mat image = imread(url);

    return preprocessing(image);
}

cv::Mat ImgReader::readImage(const std::string url)
{
    return readImageAbsolute(baseurl + url);
}

Mat ImgReader::readImageAbsoluteNoPreprocessing(const string url)
{
    return imread(url);
}

cv::Mat ImgReader::readImageNoPreprocessing(const std::string url)
{
    return readImageAbsoluteNoPreprocessing(baseurl + url);
}

void ImgReader::saveImage(Mat image, const string filename)
{
    imwrite(filename, image);
}

void ImgReader::saveImages(string url, string name, std::vector<Mat>& images, int initialNumber)
{
    int digits = Util::countDigits(images.size());
    int currentNumber = initialNumber;
    string mask = "%0";
    mask += std::to_string(digits);
    mask += "d";

    for (Mat current : images)
    {
        char number[digits];
        sprintf(number, mask.c_str(), currentNumber);
        string absoluteFilename = baseurl + url + number + name;
        saveImage(current, absoluteFilename);
        currentNumber++;
    }
}

void ImgReader::setPreprocessing(const std::function<cv::Mat(cv::Mat&)> &function)
{
    this->preprocessing = function;
}

map<int, array<Mat, 2> > ImgReader::readWithGroundTruth(string originalImagePath, string groundTruthPath, string numberDelim)
{
    vector<string> imageFilenames = getUrls(originalImagePath);
    map<int, array<Mat, 2> > images;
    for (string imageName : imageFilenames)
    {
        int id = atoi(imageName.substr(0, imageName.find(numberDelim)).c_str());
        //cout<<"Reading: "+ originalImagePath + imageName + "\n";
        Mat image = readImage(originalImagePath + imageName);
        images[id][0] = image;
    }

    imageFilenames = getUrls(groundTruthPath);
    for (string imageName : imageFilenames)
    {
        int id = atoi(imageName.substr(0, imageName.find(numberDelim)).c_str());

        //cout<<"Reading: "+ groundTruthPath + imageName + "\n";
        Mat image = readImageNoPreprocessing(groundTruthPath + imageName);
        images[id][1] = image;
    }

    return images;
}
