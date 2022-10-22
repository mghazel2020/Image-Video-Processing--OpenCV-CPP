#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int canny_ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

//==============================================================================================
// References:
//==============================================================================================
// Using inrange function to detect a single colour in an image
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

int main(int argc, char** argv)
{
    ///////////////////////////////////////////////////////////////////////////////
    namedWindow("Control", WINDOW_AUTOSIZE); //Window for track bar

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 255;

    createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 179);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);
    ///////////////////////////////////////////////////////////////////////////////

    Mat img, gray, out;
    //if (argc != 2 || !(src = imread(argv[1], 0)).data)
    //    return -1;
    // read the input image
    img = imread(input_image_fname, IMREAD_COLOR); // Load an image
    if (!img.data)                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    //namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    //imshow("Display window", img);                   // Show our image inside it.
    //// Wait for a keystroke in the window
    //waitKey(0);
    //// close all windows
    //cv::destroyAllWindows();
    
    // Convert to grayscale image
    cvtColor(img, gray, COLOR_BGR2HSV); //converting itbto SV
    // use inrange
    inRange(gray, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), out); //inrange function

    imshow("Original image", img); //Displaying orignal sreamm
    imshow("Single-color image", out); //displaying with single colour

    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();
    return 0;
}