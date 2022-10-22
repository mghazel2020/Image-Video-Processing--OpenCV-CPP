#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

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
// https://docs.opencv.org/3.4/da/d5c/tutorial_canny_detector.html
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

static void CannyThreshold(int, void*)
{
    blur(src_gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * canny_ratio, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow(window_name, dst);
}
int main(int argc, char** argv)
{
    src = imread(input_image_fname, IMREAD_COLOR); // Load an image
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return -1;
    }
    dst.create(src.size(), src.type());
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
    CannyThreshold(0, 0);
    waitKey(0);
    return 0;
}