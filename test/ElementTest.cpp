//
// Created by alevalv on 11/12/16.
//

#include "gtest/gtest.h"
#include "../src/ml/kmeans/element/Element.h"

namespace tests
{
    class ElementTest : public ::testing::Test
    {

    };

    TEST_F(ElementTest, distance)
    {
        Element element({2, 2, 2}), element2({4, 4, 4});

        double distance = element.distance(element);

        EXPECT_EQ(0, distance);

        distance = element.distance(element2);

        EXPECT_EQ(12, distance);
    }

    TEST_F(ElementTest, bracketOperator)
    {
        Element element;

        EXPECT_EQ(0, element[0]);

        element[0] = 20;

        EXPECT_EQ(20, element[0]);
    }
}