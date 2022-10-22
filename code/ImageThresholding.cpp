#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo(int, void*);


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
 * @function main
 */
int main(int argc, char** argv)
{
    /// Load an image
    src = imread(input_image_fname, 1);

    /// Convert the image to Gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    /// Create a window to display results
    namedWindow(window_name, WINDOW_AUTOSIZE);

    /// Create Trackbar to choose type of Threshold
    createTrackbar(trackbar_type,
        window_name, &threshold_type,
        max_type, Threshold_Demo);

    createTrackbar(trackbar_value,
        window_name, &threshold_value,
        max_value, Threshold_Demo);

    /// Call the function to initialize
    Threshold_Demo(0, 0);

    /// Wait until user finishes program
    while (true)
    {
        int c;
        c = waitKey(20);
        if ((char)c == 27)
        {
            break;
        }
    }

}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo(int, void*)
{
    /* 0: Binary
       1: Binary Inverted
       2: Threshold Truncated
       3: Threshold to Zero
       4: Threshold to Zero Inverted
     */

    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);

    imshow(window_name, dst);
}