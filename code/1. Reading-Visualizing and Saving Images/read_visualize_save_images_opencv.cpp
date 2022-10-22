//--------------------------------------------------------------------------
// Project: Image and live video stream processing using OpenCV C++ API
//--------------------------------------------------------------------------
// File : read_visualize_save_images_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 15, 2021
//--------------------------------------------------------------------------
// Specifications :
//-------------------------------------------------------------------------- 
// To demonstrate the most basic OpenCV C++ API functionalities for loading
// visualizing and saving images 
//-------------------------------------------------------------------------- 
// History
//-------------------------------------------------------------------------- 
// Date                      Changes                        Author
//-------------------------------------------------------------------------- 
// Mar 15, 2021              Initial definition             mghazel2020
//-------------------------------------------------------------------------- 
// MIT License :
//-------------------------------------------------------------------------- 
// Copyright(c) 2021 mghazel2020
//-------------------------------------------------------------------------- 
// References:
//--------------------------------------------------------------------------
// Include statements
// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
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

//--------------------------------------------------------------------------
// Input data:
//--------------------------------------------------------------------------
// the input folder
string input_folder = "..\\images\\";

// the input image file name
string input_image_fname = "lena.jpg";

//--------------------------------------------------------------------------
// Output folder:
//--------------------------------------------------------------------------
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
    // Declare a cv::Mat to store the input image
    Mat src_img;
    // set the input image full-path file name
    string input_image_full_path_fname = input_folder + input_image_fname;
    // read the input image file and store the image in src_img Mat
    src_img = imread(input_image_full_path_fname, IMREAD_COLOR);
    // always check for invalid input
    if (!src_img.data)                              
    {
        cout << "Could not open or find the image: " << input_image_fname << std::endl;
        return -1;
    }
    // display a success message 
    cout << "The input image was loaded and read successfully! " <<  endl;

    //-------------------------------------------------------------------------------------------
    // Step 2: Visualize the read input image:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 2: Visualize the read input image = " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // create a window for display.
    namedWindow("Input image", WINDOW_AUTOSIZE);
    // display our image inside the created window 
    imshow("Input image", src_img);       
   
   //-------------------------------------------------------------------------------------------
   // Step 3: Create the output directory:
   //------------------------------------------------------------------------------------------
   // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 3: Create the output directory:" << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // the new output directory
    // update the output folder name
    output_folder = output_folder + "Demo-01-Load-visualize-save-images" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }

    //-------------------------------------------------------------------------------------------
    // Step 4: Save the image:
    //------------------------------------------------------------------------------------------
    // display a message
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "Step 3: Save the image = " << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
    // set the output image full-path file name
    string output_image_full_path_fname = output_folder + input_image_fname;
    // save the output image
    imwrite(output_image_full_path_fname, src_img );

    //-------------------------------------------------------------------------------------------
    // Wait for a keystroke in the window
    //-------------------------------------------------------------------------------------------
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