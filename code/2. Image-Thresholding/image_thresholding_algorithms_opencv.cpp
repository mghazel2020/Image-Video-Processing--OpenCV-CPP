//-------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API:
//-------------------------------------------------------------------------
// File : image_thresholding_algorithms_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 15, 2021
//-------------------------------------------------------------------------
// Specifications:
//------------------------------------------------------------------------- 
// To demonstrate a basic image processing in OpenCV C++ API functionality  
// # involving interactively thresholding the image pixel-values.
//------------------------------------------------------------------------- 
// History
//-------------------------------------------------------------------------
// Date                      Changes                        Author
//------------------------------------------------------------------------- 
// Mar 15, 2021              Initial definition             mghazel2020
//------------------------------------------------------------------------- 
// MIT License:
//-------------------------------------------------------------------------
// Copyright(c) 2021 mghazel2020
//-------------------------------------------------------------------------
// Include statements
// OpenCV
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

// IO streams
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include < direct.h>
// string utilities
#include <string>

// Name-spaces shorthands
// OpenCV
using namespace cv;
// std
using namespace std;

//-------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------
// Global variables
// initialize the threshold value
int threshold_value = 0;
// initialize the thresholding type
int threshold_type = 3;;
// initialize the max threshold value
int const max_value = 255;
// initialize the max type
int const max_type = 4;
// initialize the max binary value
int const max_BINARY_value = 255;

// Declare a cv::Mat to store the input source image
cv::Mat src;
// Declare a cv::Mat to store the gray-scale image
cv::Mat src_gray;
// Declare a cv::Mat to store the output image
cv::Mat dst;

// the window names
const char* window_name = "Image Thresholding";
// the thresholding type options
const char* trackbar_type = "Type: \n 0:Binary \n 1: Binary-Inverted \n 2: Truncate \n 3: To-Zero \n 4: To-Zero-Inverted";
// the threshold value
const char* trackbar_value = "Threshold-value";

/// Function header
void Threshold_Demo(int, void*);

//-------------------------------------------------------------------------
// Input data:
//-------------------------------------------------------------------------
// the input folder
string input_folder = "..\\images\\";

// the input image file name
string input_image_fname = "lena.jpg";

//-------------------------------------------------------------------------
// Output folder:
//-------------------------------------------------------------------------
// output folder name
string output_folder = "..\\results\\";

/**
 * function main
 */
int main(int argc, char** argv)
{
    //------------------------------------------------------------------------------------------
    // Step 1: Load the input image file:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 1: Load and read the input image file = " << input_image_fname << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // set the input image full-path file name
    string input_image_full_path_fname = input_folder + input_image_fname;
    // read the input image file and store the image in src_img Mat
    src = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src.data)
    {
        cout << "Could not open or find the image: " << input_image_fname << std::endl;
        return -1;
    }
    // display a success message 
    cout << "The input image was loaded and read successfully! " << endl;

    //-------------------------------------------------------------------------------------------
    // Step 2: Create the output directory:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 3: Create the output directory:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // the new output directory
    // update the output folder name
    output_folder = output_folder + "Image_thresholding" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }
    //-------------------------------------------------------------------------------------------
    // Step 3: Convert the input image to gray-scale:
    //------------------------------------------------------------------------------------------
    // // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 4: Convert the input image to gray-scale:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // Convert the image to Gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    //-------------------------------------------------------------------------------------------
    // Step 5: Create a Track-bar to run the image thresholding functionality:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 5: Create a Track-bar to run the image thresholding functionality:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    /// Create a window to display results
    namedWindow(window_name, WINDOW_AUTOSIZE);
    /// Create Track-bar to choose type of Thresholding operation
    createTrackbar(trackbar_type, window_name, &threshold_type, max_type, Threshold_Demo);
    /// Create Track-bar to choose type of Thresholding value
    createTrackbar(trackbar_value, window_name, &threshold_value,max_value, Threshold_Demo);

    /// Call the BarTrack thresholding function
    Threshold_Demo(0, 0);

    /// Terminate when user presses escape
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

//----------------------------------------
// @function Threshold_Demo
//----------------------------------------
// - The TrackBar user interface
//----------------------------------------
void Threshold_Demo(int, void*)
{
    /* 0: Binary
        1: Binary Inverted
        2: Threshold Truncated
        3: Threshold to Zero
        4: Threshold to Zero Inverted
        */
    // apply the threshold operation using OpenCV threshold() function
    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
    // display the output image
    imshow(window_name, dst);
}