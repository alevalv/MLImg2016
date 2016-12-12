//
// Created by alevalv on 11/12/16.
//

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "../src/ml/kmeans/KMeans.h"

using namespace cv;

namespace test
{
    class KMeansTest : public ::testing::Test
    {
    protected:
        Mat input;

        KMeansTest()
        {
            input = imread("../../DRIVE/test/images/01_test.tif");
        }
    };

    TEST_F(KMeansTest, execute)
    {
        KMeans kmeans(2);
        kmeans.execute(input);
        ASSERT_TRUE(input.cols > 0);
    }
}

