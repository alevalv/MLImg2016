//
// Created by alevalv on 11/12/16.
//

#include "preprocessor.h"

const std::function<Mat(Mat&)> Preprocessor::EXTRACT_GREEN = [] (Mat& image) -> Mat
{
Mat channels[3];
split(image.clone(), channels);
return channels[1];
};