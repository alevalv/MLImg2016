#include <dirent.h>
#include <iostream>
#include "imgreader.h"
#include "util.h"

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

Mat ImgReader::preprocessing(const Mat& image)
{
    Mat channels[3];
    split(image.clone(), channels);

    return channels[1];
}

Mat ImgReader::readImage(const string url)
{
    Mat image = imread(url);

    return preprocessing(image);
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
