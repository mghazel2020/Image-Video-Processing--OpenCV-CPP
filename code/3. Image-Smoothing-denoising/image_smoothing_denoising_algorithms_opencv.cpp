//-------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API:
//-------------------------------------------------------------------------
// File : image_smoothing_denoising.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 16, 2021
//-------------------------------------------------------------------------
// Specifications:
//------------------------------------------------------------------------- 
// To demonstrate a basic image processing in OpenCV C++ API functionality  
// # involving image smoothing and denoising.
//------------------------------------------------------------------------- 
// History
//-------------------------------------------------------------------------
// Date                      Changes                        Author
//------------------------------------------------------------------------- 
// Mar 16, 2021              Initial definition             mghazel2020
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

// The filter size for the different methods
// AVERAGE/MEAN filter
const int MEAN_FILTER_SIZE = 5;
// MEDIAN filter
const int MEDIAN_FILTER_SIZE = 5;
// GAUSSIAN filter
const int GAUSS_FILTER_SIZE = 11;
// BILATERAL-FILTER filter
const int BILATERAL_FILTER_SIZE = 21;
// NON-LOCAL-mean filter
int NON_LOCAL_MEANS_FILTER_SIZE = 101;
// Filter size for the Non-Local Means filter Algorithm
int KERNEL_LENGTH_NLM = 101;

// declare cv:Mat arrays to store images
// input image
Mat src;
// gray-scale image
Mat src_gray; 
// output image
Mat dst;
Mat out_img;

// the display window name
char window_name[] = "Image smoothing and denoising";

/// Function headers
int display_caption(const char* caption);
// display the output image
int display_dst(int delay);

//------------------------------------------------------------------------- 
// Input data:
//------------------------------------------------------------------------- 
// the input folder
string input_folder = "..\\images\\";

// the input image file name
string input_image_fname = input_folder + "DiscoveryMuseum_NoiseAdded.jpg";

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
    // Step 3: Create the output directory:
    //------------------------------------------------------------------------- 
    // display a message
    // the new output directory
    // update the output folder name
    output_folder = output_folder + "Demo-03-image-smoothing-denoising" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }
    
    // Read the source image
    src = imread(input_image_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src.data)
    {
        cout << "Could not open or find the image: " << input_image_fname << std::endl;
        return -1;
    }
    // display a success message 
    cout << "The input image was loaded and read successfully! " << endl;

    //------------------------------------------------------------------------- 
    // Step 3: Convert the input image to gray-scale:
    //------------------------------------------------------------------------- 
    // // display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 4: Convert the input image to gray-scale:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // Convert the image to gray-scale
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    // set the output image full-path file name
    string output_image_full_path_fname = output_folder + "noisy_image.jpg";
    // save the output image
    imwrite(output_image_full_path_fname, src_gray);
   
    //------------------------------------------------------------------------- 
    // Step 4: Step 4: Apply the Homogeneous/Averaging Filter:
    //------------------------------------------------------------------------- 
    // display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 4: Apply the Homogeneous Mean/Averaging Filter:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // Apply Homogeneous average/mean blur
    blur(src_gray, dst, Size(MEAN_FILTER_SIZE, MEAN_FILTER_SIZE), Point(-1, -1));
    // set the output image full-path file name
    output_image_full_path_fname = output_folder + "mean_blur_" + to_string(MEAN_FILTER_SIZE) + ".jpg";
    // save the output image
    imwrite(output_image_full_path_fname, dst);
    
    //------------------------------------------------------------------------- 
    // Step 5: Apply the Median Filter:
    //------------------------------------------------------------------------- 
    //  display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 5: Apply the Median Filter:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // Apply Median-blur filter
    medianBlur(src_gray, dst, MEDIAN_FILTER_SIZE);
    // set the output image full-path file name
    output_image_full_path_fname = output_folder + "median_blur_" + to_string(MEDIAN_FILTER_SIZE) + ".jpg";
    // save the output image
    imwrite(output_image_full_path_fname, dst);

    //------------------------------------------------------------------------- 
    // Step 6: Apply the Gaussian Filter:
    //------------------------------------------------------------------------- 
    // display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 6: Apply the Gaussian Filter:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // Apply Gaussian-blur filter
    GaussianBlur(src_gray, dst, Size(GAUSS_FILTER_SIZE, GAUSS_FILTER_SIZE), 0, 0);
    // set the output image full-path file name
    output_image_full_path_fname = output_folder + "gauss_blur_" + to_string(GAUSS_FILTER_SIZE) + ".jpg";
    // save the output image
    imwrite(output_image_full_path_fname, dst);

    //------------------------------------------------------------------------- 
    // Step 7: Apply the Bilateral Filter:
    //------------------------------------------------------------------------- 
    // display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 7: Apply the Bilateral Filter:" << endl;
    cout << "------------------------------------------------------------------" << endl;
    // Apply Bilateral Filter
    bilateralFilter(src_gray, dst, BILATERAL_FILTER_SIZE, 2 * BILATERAL_FILTER_SIZE, BILATERAL_FILTER_SIZE / 2);
    // set the output image full-path file name
    output_image_full_path_fname = output_folder + "bilateral_filter_" + to_string(BILATERAL_FILTER_SIZE) + ".jpg";
    // save the output image
    imwrite(output_image_full_path_fname, dst);
      
    //------------------------------------------------------------------------- 
    // Step 8: Apply NON-LOCAL-MEANS FILTERING on the input image:
    //------------------------------------------------------------------------- 
    // display a message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Step 8: Apply NON-LOCAL-MEANS FILTERING on the input image: " << endl;
    cout << "------------------------------------------------------------------" << endl;
    //------------------------------------------------------------------------- 
    // Apply the NON-LOCAL-MEANS FILTERING bilateralFilter() functionality:
    //------------------------------------------------------------------------- 
    // - For color images
    //------------------------------------------------------------------------- 
    // fastNlMeansDenoisingColored(src_img, out_img, 10.0, 15.0, 21, NON_LOCAL_MEANS_FILTER_SIZE);
    //------------------------------------------------------------------------- 
    // - For gray-scale images:
    //------------------------------------------------------------------------- 
    fastNlMeansDenoising(src_gray, dst, 10, 21, NON_LOCAL_MEANS_FILTER_SIZE);
    // create a window for display.
    namedWindow("After NON-LOCAL-MEANS FILTERING", WINDOW_AUTOSIZE);
    // display our image inside the created window 
    imshow("After NON-LOCAL-MEANS FILTERING", dst);
    // set the output image full-path file name
    output_image_full_path_fname = output_folder + "input_img_NLM_filter_size_" + to_string(NON_LOCAL_MEANS_FILTER_SIZE) + "x" + to_string(NON_LOCAL_MEANS_FILTER_SIZE) + ".jpg";
    // save the output image
    imwrite(output_image_full_path_fname, dst);

    //------------------------------------------------------------------------- 
    // Wait for a keystroke in the window
    //------------------------------------------------------------------------- 
    // - this keeps the window and the image displayed until the user hits any key
    waitKey(0);
    // close all windows once the user hits any key
    cv::destroyAllWindows();

    // display a final message
    cout << "------------------------------------------------------------------" << endl;
    cout << "Program executed successfully!\nPress any key to continue... " << endl;
    cout << "------------------------------------------------------------------" << endl;

    // return success
    return 0;

}
