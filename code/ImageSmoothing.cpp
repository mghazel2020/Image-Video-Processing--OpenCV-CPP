#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global Variables
int DELAY_CAPTION = 2000;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src; Mat dst;
char window_name[] = "Filter Demo 1";

/// Function headers
int display_caption(const char* caption);
int display_dst(int delay);


//==============================================================================================
// Reference:
//==============================================================================================
// https://www.docs.opencv.org/2.4/doc/tutorials/imgproc/threshold/threshold.html?highlight=basic%20thresholding%20operations
//==============================================================================================

//==============================================================================================
// Input data:
//==============================================================================================
// the input folder
string input_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\data\\";

// the input image file name
string input_image_fname = input_folder + "lena.jpg";

//==============================================================================================
// Output folder:
//==============================================================================================
// output folder name
string output_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\results\\";

/**
 * function main
 */
int main(int argc, char** argv)
{
    namedWindow(window_name, WINDOW_AUTOSIZE);

    /// Load the source image
    src = imread(input_image_fname, 1);

    if (display_caption("Original Image") != 0) { return 0; }

    dst = src.clone();
    if (display_dst(DELAY_CAPTION) != 0) { return 0; }

    /// Applying Homogeneous blur
    if (display_caption("Homogeneous Blur") != 0) { return 0; }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        blur(src, dst, Size(i, i), Point(-1, -1));
        if (display_dst(DELAY_BLUR) != 0) { return 0; }
    }

    /// Applying Gaussian blur
    if (display_caption("Gaussian Blur") != 0) { return 0; }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
        if (display_dst(DELAY_BLUR) != 0) { return 0; }
    }

    /// Applying Median blur
    if (display_caption("Median Blur") != 0) { return 0; }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        medianBlur(src, dst, i);
        if (display_dst(DELAY_BLUR) != 0) { return 0; }
    }

    /// Applying Bilateral Filter
    if (display_caption("Bilateral Blur") != 0) { return 0; }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        bilateralFilter(src, dst, i, i * 2, i / 2);
        if (display_dst(DELAY_BLUR) != 0) { return 0; }
    }

    /// Wait until user press a key
    display_caption("End: Press a key!");

    waitKey(0);
    return 0;
}

int display_caption(const char* caption)
{
    dst = Mat::zeros(src.size(), src.type());
    putText(dst, caption,
        Point(src.cols / 4, src.rows / 2),
        FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

    imshow(window_name, dst);
    int c = waitKey(DELAY_CAPTION);
    if (c >= 0) { return -1; }
    return 0;
}

int display_dst(int delay)
{
    imshow(window_name, dst);
    int c = waitKey(delay);
    if (c >= 0) { return -1; }
    return 0;
}