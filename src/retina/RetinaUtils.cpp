//
// Created by alevalv on 16/12/16.
//

#include "RetinaUtils.h"
#include "../featuredetection/Corner.h"
#include "../util.h"
#include "../ml/kmeans/KMeans.h"

using namespace std;
using namespace cv;

vector<double> RetinaUtils::findOpticalDisk(Mat &image)
{
    Corner corner(200);
    vector<vector<double> > corners = corner.shiTomasiGetCorners(image);
    vector<vector<double> > initialCentroids(3, vector<double>(2, 0));

    /*
     * Centroids are set as shown in the image below, ideally, the middle centroid should be the optical disk (citation required).
     *
     * 0 1 2 3 4 5 6 7 8
     * + + + + C + + + + 0
     * + + + + + + + + + 1
     * + + + + + + + + + 2
     * + + + + + + + + + 3
     * + + + + C + + + + 4
     * + + + + + + + + + 5
     * + + + + + + + + + 6
     * + + + + + + + + + 7
     * + + + + C + + + + 8
     */
    initialCentroids[0][0] = image.rows/2.0;
    initialCentroids[1][0] = image.rows;
    initialCentroids[1][1] = image.cols/2.0;
    initialCentroids[2][0] = image.rows/2.0;
    initialCentroids[2][1] = image.cols/2.0;

    KMeans kmeans(initialCentroids);
    vector<int> tags = kmeans.execute(corners);
    return KMeans::findBiggestCentroid(tags, kmeans.getCentroids());
}
