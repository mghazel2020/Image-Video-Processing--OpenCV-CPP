//-------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API
//-------------------------------------------------------------------------
// File : edge_detection_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 15, 2021
//-------------------------------------------------------------------------
// Specifications :
//------------------------------------------------------------------------- 
// To demonstrate the most basic OpenCV C++ API functionalities for 
// image edge detection.
//-------------------------------------------------------------------------= 
// History
//-------------------------------------------------------------------------= 
// Date                      Changes                        Author
//------------------------------------------------------------------------- 
// Mar 15, 2021              Initial definition             mghazel2020
//-------------------------------------------------------------------------= 
// MIT License :
//-------------------------------------------------------------------------= 
// Copyright(c) 2021 mghazel2020
//-------------------------------------------------------------------------= 
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
#include < direct.h >
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
// create array to store images
//-------------------------------------------------------------------------
Mat src;
// gray-scale image
Mat src_gray;
// edge detection results
Mat dst, detected_edges;
//-------------------------------------------------------------------------
// edge thresholding parameters
//-------------------------------------------------------------------------
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int canny_ratio = 3;
const int kernel_size = 3;

//-------------------------------------------------------------------------
// window name
//-------------------------------------------------------------------------
const char* window_name = "Canny Edge Detection Results";
//-------------------------------------------------------------------------
// Canny threshold detector
//-------------------------------------------------------------------------
static void CannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * canny_ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}

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
    output_folder = output_folder + "Demo-04-edge-detection" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }
    //-------------------------------------------------------------------------------------------
    // Step 3: Convert the input image to gray-scale:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 4: Convert the input image to gray-scale:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // Convert the image to Gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    //------------------------------------------------------------------------------------------
    // Step 4: Create a Track-Bar to run the image edge-detection functionality:
    //------------------------------------------------------------------------------------------
    // - This allows us to interactively select different threshold values
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 5: Create a Track-Bar to run the image edge-detection functionality:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // initialize the output image
    dst.create(src.size(), src.type());
    // initialize the display window
    namedWindow(window_name, WINDOW_AUTOSIZE);
    // create the TrackBar display
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    // Call the canny edge detector
    CannyThreshold(0, 0);

    //-------------------------------------------------------------------------------------------
    // Step 5: Wait for a keystroke in the window to close it
    //------------------------------------------------------------------------------------------
    // Wait for a keystroke in the window
    // - this keeps the window and the image displayed until the user hits any key
    waitKey(0);
    // close all windows once the user hits any key
    cv::destroyAllWindows();

    // display a final message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Program executed successfully!\nPress any key to continue... " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;

    // return success
    return 0;
}
