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
// https://www.docs.opencv.org/2.4/modules/imgproc/doc/feature_detection.html?highlight=edge%20detection#canny
//==============================================================================================
//==============================================================================================
// Input data:
//==============================================================================================
// the input folder
string input_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\data\\";

// the input image file name
string input_image_fname = input_folder + "circles2.jpg";

//==============================================================================================
// Output folder:
//============================================================================================== 
// output folder name
string output_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\results\\";

int main(int argc, char** argv)
{
    Mat img, gray;
    //if (argc != 2 || !(src = imread(argv[1], 0)).data)
    //    return -1;
    // read the input image
    img = imread(input_image_fname, IMREAD_COLOR); // Load an image
    if (!img.data)                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", img);                   // Show our image inside it.
    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();
    cvtColor(img, gray, COLOR_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);
    vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 2, gray.rows / 4, 200, 100);
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(img, center, 3, Scalar(0, 255, 0), -1, 8, 0);
        // draw the circle outline
        circle(img, center, radius, Scalar(0, 0, 255), 3, 8, 0);
    }
    namedWindow("circles", 1);
    imshow("circles", img);
    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();
    return 0;
}