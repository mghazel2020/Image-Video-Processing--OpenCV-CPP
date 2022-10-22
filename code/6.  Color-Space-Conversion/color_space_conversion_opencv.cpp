//-------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API
//-------------------------------------------------------------------------
// File : color_space_convertion_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 16, 2021
//-------------------------------------------------------------------------
// Specifications:
//------------------------------------------------------------------------- 
// To demonstrate a basic image processing in OpenCV C++ API functionality  
// involving color space conversion from RGB to 4 other color spaces:
//   - RGB to GRAY
//   - RGB to HSV
//   - RGB to CIELAB
//   - RGB to YrCB.
//-------------------------------------------------------------------------
// History
//-------------------------------------------------------------------------
// Date                      Changes                        Author
//------------------------------------------------------------------------- 
// Mar 15, 2021              Initial definition             mghazel2020
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
// declare cv::Mat to store images
//-------------------------------------------------------------------------
// original image
Mat img; 
// gray-scale image
Mat img_gray;
// HSV color-space
Mat img_hsv;
// LAB color-space
Mat img_lab;
// YCrCb color-space
Mat img_ycrcb;

//-------------------------------------------------------------------------
// Input data:
//-------------------------------------------------------------------------
// the input folder
string input_folder = "..\\images\\";

// the input image file names
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
    //-------------------------------------------------------------------------
    // Create the output directory:
    //-------------------------------------------------------------------------
    // the output directory
    output_folder = output_folder + "Demo-06-color-space-conversion" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }
    else
    {
        cout << "The output folder created successfully!" << output_folder << endl;
    }

    //-------------------------------------------------------------------------
    // Read the input image
    //-------------------------------------------------------------------------
    // set the input image full-path file name
    string input_image_full_path_fname = input_folder + input_image_fname;
    // read the input image file and store the image in img Mat
    img = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!img.data)
    {
        cout << "Could not open or find the image: " << input_image_fname << std::endl;
        return -1;
    }
    // Display the original image
    namedWindow("RGB image", WINDOW_AUTOSIZE);
    // Show our image inside it.
    imshow("RGB image", img);                  
    // save the input image
    imwrite(output_folder + "lena_original.jpg", img);

    //------------------------------------------------------------------------- 
    // 3.1) Convert to BGR to gray-scale image
    //-------------------------------------------------------------------------
    // convert to gray-scale
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    // save the input image
    imwrite(output_folder + "lena_gray.jpg", img_gray);
    // Display the gray-scale image
    // Create a window for display.
    namedWindow("Grayscale image", WINDOW_AUTOSIZE);
    // Show our image inside it.
    imshow("Grayscale image", img_gray);                  

    //-------------------------------------------------------------------------
    // 3.2) Convert to BGR to HSV image
    //-------------------------------------------------------------------------
    cvtColor(img, img_hsv, COLOR_BGR2HSV);
    // save the input image
    imwrite(output_folder + "lena_hsv.jpg", img_hsv);
    // Display the HSV image
     // Show our image inside it.
    namedWindow("HSV image", WINDOW_AUTOSIZE);
    // Show our image inside it.
    imshow("HSV image", img_hsv);                   

    //-------------------------------------------------------------------------
    // 3.3) Convert to BGR to CIELAB image
    //-------------------------------------------------------------------------
    cvtColor(img, img_lab, COLOR_BGR2Lab);
    // save the input image
    imwrite(output_folder + "lena_lab.jpg", img_lab);
    // Display the CIELAB image
    // Create a window for display.
    namedWindow("CIELAB Image", WINDOW_AUTOSIZE);
    // Show our image inside it.
    imshow("CIELAB Image", img_lab);                   

    //-------------------------------------------------------------------------
    // 3.4) Convert to BGR to YCrCb image
    //-------------------------------------------------------------------------
    cvtColor(img, img_ycrcb, COLOR_BGR2YCrCb);
    // save the input image
    imwrite(output_folder + "lena_ycrcb.jpg", img_ycrcb);
    // Display the YCrCb image
    // Create a window for display.
    namedWindow("YCrCb Image", WINDOW_AUTOSIZE);
    // Show our image inside it.
    imshow("YCrCb Image", img_lab);                   

    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();

    // return 
    return 0;
}
