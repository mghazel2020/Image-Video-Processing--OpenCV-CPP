//-------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API
//-------------------------------------------------------------------------
// File : features_detection_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 15, 2021
//-------------------------------------------------------------------------
// Specifications :
//------------------------------------------------------------------------- 
// To demonstrate feature detections using OpenCV C++ API built-in 
// functionalities, including:
// 
//  - Line detection
//  - Circle detection
//  - Corner detection
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
#include < direct.h >
// string utilities
#include <string>

// Name-spaces shorthands
// OpenCV
using namespace cv;
// std
using namespace std;

//-------------------------------------------------------------------------
// Global Variables:
//-------------------------------------------------------------------------
// create cv::Mat arrays to store images:
//-------------------------------------------------------------------------
// the input image
Mat src;
// the input image converted to gray-scale
Mat src_gray;
// the edge detection results
Mat dst_edges;
// the line detection results
Mat dst_lines;
// the circle detection results
Mat dst_circles;
// the Harris corners detection results
Mat dst_corners;
//-------------------------------------------------------------------------
// Harris corners detection parameters:
//-------------------------------------------------------------------------
int thresh = 200;
int max_thresh = 255;
const char* source_window = "Input image";
const char* corners_window = "Harris Corners detection results";
void cornerHarris_demo(int, void*);

//-------------------------------------------------------------------------
// Input images:
//-------------------------------------------------------------------------
// the input folder
string input_folder = "..\\images\\";

// the input image file names
//-------------------------------------------------------------------------
// - Test image for line detection
//-------------------------------------------------------------------------
// test image 1
string input_image_fname_1 = "building.jpg";
//-------------------------------------------------------------------------
// - Test image for circle detection
//-------------------------------------------------------------------------
// test image 2
string input_image_fname_2 = "circles.jpg";
//-------------------------------------------------------------------------
// - Test image for Harris corners detection
//-------------------------------------------------------------------------
// test image 3
string input_image_fname_3 = "checkerboard.jpg";

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
    output_folder = output_folder + "Demo-05-feature-detection" + "\\";
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
    // 1) Line Detection using Hough Transform:
    //-------------------------------------------------------------------------
    cout << "------------------------------------------------------------------" << endl;
    cout << "1) Line Detection using Hough Transform:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // set the input image full-path file name
    string input_image_full_path_fname = input_folder + input_image_fname_1;
    // read the input image file and store the image in src_img Mat
    src = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src.data)
    {
        cout << "Could not open or find the image: " << input_image_fname_1 << std::endl;
        return -1;
    }
    
    //-------------------------------------------------------------------------
    // Convert the input image to gray-scale:
    //-------------------------------------------------------------------------
    // Convert the image to Gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    // display the gray-scale image 
    namedWindow("Input image", 1);
    imshow("Input image", src);

    //-------------------------------------------------------------------------
    // Detect edges using Canny(...)
    //-------------------------------------------------------------------------
    Canny(src_gray, dst_edges, 150, 200, 3);

    //-------------------------------------------------------------------------
    // Detect lines via HoughLinesP(...)
    //-------------------------------------------------------------------------
    // a vector to store the detected lines
    vector<Vec4i> lines;
    // apply the Hough transform
    HoughLinesP(dst_edges, lines, 1, CV_PI / 180, 80, 30, 10);
    // iterate over the detected lines
    for (size_t i = 0; i < lines.size(); i++)
    {
        // draw the line on the input image
        line(src, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
    }
    // display the gray-scale image 
    namedWindow("Line detection results", 1);
    imshow("Line detection results", src);
    //-------------------------------------------------------------------------
    // save the line detection results
    //-------------------------------------------------------------------------
    // output file name
    string output_fname = output_folder + "line_detection_results.jpg";
    // save the output image
    imwrite(output_fname, src);

    //-------------------------------------------------------------------------
    // 2) Circle Detection using Hough Transform:
    //-------------------------------------------------------------------------
    cout << "------------------------------------------------------------------" << endl;
    cout << "2) Circle Detection using Hough Transform:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // set the input image full-path file name
    input_image_full_path_fname = input_folder + input_image_fname_2;
    // read the input image file and store the image in src_img Mat
    src = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src.data)
    {
        cout << "Could not open or find the image: " << input_image_fname_2 << std::endl;
        return -1;
    }
    // display a success message 
    cout << "The input image was loaded and read successfully! " << endl;

    //-------------------------------------------------------------------------
    // Convert the input image to gray-scale:
    //-------------------------------------------------------------------------
    // Convert the image to Gray
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    // display the gray-scale image 
    namedWindow("Input image", 1);
    imshow("Input image", src);

    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);
    vector<Vec3f> circles;
    HoughCircles(src_gray, circles, HOUGH_GRADIENT, 2, src_gray.rows / 4, 200, 100);
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        // draw the circle outline
        circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }

    // display the gray-scale image 
    namedWindow("Circle detection results", 1);
    // display the output image
    imshow("Circle detection results", src);
    //-------------------------------------------------------------------------
    // save the line detection results
    //-------------------------------------------------------------------------
    // output file name
    output_fname = output_folder + "circle_detection_results.jpg";
    // save the output image
    imwrite(output_fname, src);

    //-------------------------------------------------------------------------
    // 3) Corner Detection using Harris Corner Detector
    //-------------------------------------------------------------------------
    cout << "------------------------------------------------------------------" << endl;
    cout << "3) Corner Detection using Harris Corners Detector:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // set the input image full-path file name
    input_image_full_path_fname = input_folder + input_image_fname_3;
    // read the input image file and store the image in src_img Mat
    src = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src.data)
    {
        cout << "Could not open or find the image: " << input_image_fname_3 << std::endl;
        return -1;
    }
    // display a success message 
    cout << "The input image was loaded and read successfully! " << endl;

    //-------------------------------------------------------------------------
    // Convert the input image to gray-scale:
    //-------------------------------------------------------------------------
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(source_window);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);
    cornerHarris_demo(0, 0);

    //-------------------------------------------------------------------------
    // Step 6: Wait for a keystroke in the window to close it
    //-------------------------------------------------------------------------
    // Wait for a keystroke in the window
    // - this keeps the window and the image displayed until the user hits any key
    waitKey(0);
    // close all windows once the user hits any key
    cv::destroyAllWindows();

    return 0;
}

//-------------------------------------------------------------------------
// Harris corner detection functionality:
//-------------------------------------------------------------------------
void cornerHarris_demo(int, void*)
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    Mat dst = Mat::zeros(src.size(), CV_32FC1);
    cornerHarris(src_gray, dst, blockSize, apertureSize, k);
    Mat dst_norm, dst_norm_scaled;
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);
    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            if ((int)dst_norm.at<float>(i, j) > thresh)
            {
                //----------------------------------------------------------------------------
                //  circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0), 2, 8, 0 );
                //----------------------------------------------------------------------------
                // overlay the detected circles on the original image
                //----------------------------------------------------------------------------
                circle(src, Point(j, i), 5, Scalar(0, 0, 255), 10, LINE_8, 0);
            }
        }
    }
    //----------------------------------------------------------------------------
    // Update the display after overlaying the detected corners
    //----------------------------------------------------------------------------
    imshow(source_window, src);
}