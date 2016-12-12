//
// Created by alevalv on 11/12/16.
//

#include "Harris.h"

using namespace cv;

Harris::Harris(int threshold)
{
    this->threshold = threshold;
}

Mat Harris::getHarrisCorners(const Mat &image)
{
    Mat dest, dest_normalized, dest_norm_scaled;
    Mat result = image.clone();

    cornerHarris(image, dest, 2, 3, 0.04, BORDER_DEFAULT);
    normalize(dest, dest_normalized, 0, 255, NORM_MINMAX, CV_8U, Mat());
    convertScaleAbs(dest_normalized, dest_norm_scaled);

    for (int j = 0; j < dest_normalized.rows; j++)
    {
        for (int i = 0; i < dest_normalized.cols; i++)
        {
            if ((int) dest_normalized.at<float>(j, i) > threshold)
            {
                circle(result, Point(i, j), 5, Scalar(255), 2, 8, 0);
            }
        }
    }

    return result;
}
