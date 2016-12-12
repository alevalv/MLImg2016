
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

using namespace cv;

#define NW "window_name"

Mat esobel(const Mat& image)
{
    Mat gauss;
    Mat src_gray, grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    GaussianBlur(image, gauss, Size(5, 5), 50, 50, BORDER_DEFAULT );

    cvtColor(gauss, src_gray, COLOR_BGR2GRAY );

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    //Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );

    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );

    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );

    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );

    Mat edgeMap;
    threshold(grad, edgeMap, 5, 255, CV_THRESH_BINARY);
    return edgeMap;
}

Mat test1(Mat& image)
{
    Mat sobel = esobel(image);
    Mat erodetgt;
    erode(sobel, erodetgt, getStructuringElement(MORPH_ELLIPSE, Size(5, 5), Point(3, 3)));
    return erodetgt;
}

Mat test2(Mat& image)
{
    int kernel_size = 5;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    Mat src = image.clone();
    Mat channels[3];
    Mat src_gray, dst, abs_dst, outputM;
    Mat mask, resultr;
    namedWindow("window_name", WINDOW_FREERATIO);
    split(src, channels);

    medianBlur(channels[1], src_gray, 31);

    resize(channels[1], src_gray, Size(), 0.07, 0.07, INTER_AREA);
    resize(src_gray, mask, src.size(), 0, 0, INTER_LINEAR);

    subtract(channels[1], mask, resultr);

    imshow( "window_name", resultr);
    waitKey(0);

    GaussianBlur( resultr, resultr, Size(3,3), 0, 0, BORDER_DEFAULT );


    Laplacian( resultr, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( dst, abs_dst );
    subtract(abs_dst, mask, outputM);

    return outputM;
}

Mat test3(Mat& image)
{
    int kernel_size = 5;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    Mat src = image.clone();
    Mat channels[3];
    Mat src_gray, dst, abs_dst, outputM;
    Mat mask, resultr;
    split(src, channels);
    medianBlur(channels[1], src_gray, 41);
    Mat element = getStructuringElement(2, Size(17,17), Point(4, 4));
    morphologyEx(src_gray, dst, 5, element);
    return dst;
}

int old(int argc, char** argv )
{
    Mat src, src_gray;
    Mat grad;
    const char* window_name = "Imagen";
    src = imread( argv[1], IMREAD_COLOR ); // Load an image

    namedWindow(NW, WINDOW_FREERATIO);

    if( src.empty() )
      { return -1; }


//    Mat sobel = test1(src);
//    imshow( window_name, sobel);
//    waitKey(0);

//    Mat laplace = test2(src);
//    imshow( window_name, laplace);
//    waitKey(0);

    //imwrite("median.png",
    imshow(NW,
            test3(src));
    waitKey(0);
    return 0;

    // http://stackoverflow.com/questions/12166562/radon-transform-matrix-representation
}
