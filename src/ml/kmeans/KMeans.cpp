//
// Created by alevalv on 06/12/16.
//

#include <iostream>
#include "KMeans.h"
#include "../../util.h"

using namespace std;
using namespace cv;

KMeans::KMeans(int centroidCount, int elementSize, int maxValue)
{
    mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
        0x9908b0df, 11,
        0xffffffff, 7,
        0x9d2c5680, 15,
        0xefc60000, 18, 1812433253> random;

    std::random_device r;
    random.seed(r());

    for (int i = 0; i < centroidCount; i++)
    {
        vector<double> centroid;
        for (int j = 0; j < elementSize; j++)
        {
            centroid.push_back(random() % maxValue);
        }
        centroids.push_back(centroid);
    }
}

KMeans::KMeans(std::vector<vector<double> > centroids)
{
    this->centroids = centroids;
}

void KMeans::execute(Mat image)
{

}

void KMeans::execute(std::vector<vector<double> > elements)
{
    int iterations = 0;
    vector<vector<double> > oldCentroids;
    vector<int> labels(elements.size(), -1);

    while(Util::distance(oldCentroids, centroids) != 0 && iterations < 1000)
    {
        oldCentroids = centroids;
        iterations++;

        double currentDistance = numeric_limits<double>::max();
        for(int i=0; i < elements.size(); i++)
        {
            int newCentroid = -1;
            for (int j=0; j < centroids.size(); j++)
            {
                double centroidDistance = Util::distance(elements[i], centroids[j]);
                if (centroidDistance < currentDistance)
                {
                    currentDistance = centroidDistance;
                    newCentroid = j;
                }
            }
            labels[i] = newCentroid;
        }

        vector<int> count(centroids.size(), 0);
        vector<vector<double> > newCentroids(centroids.size(), vector<double>(centroids[0].size(), 0));
        for(int i=0; i < elements.size(); i++)
        {
            count[labels[i]]++;
            for (int j=0; j <elements[i].size(); j++)
            {
                newCentroids[labels[i]][j]+=elements[i][j];
            }
        }

        centroids = newCentroids;
    }

}

std::vector<std::vector<double> > KMeans::getCentroids()
{
    return centroids;
}
