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
string input_image_fname = input_folder + "building.jpg";

//==============================================================================================
// Output folder:
//==============================================================================================
// output folder name
string output_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\results\\";

int main(int argc, char** argv)
{
    Mat src, dst, color_dst;
    //if (argc != 2 || !(src = imread(argv[1], 0)).data)
    //    return -1;
    // read the input image
    src = imread(input_image_fname, IMREAD_COLOR); // Load an image
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, color_dst, COLOR_GRAY2BGR);

#if 0
    vector<Vec2f> lines;
    HoughLines(dst, lines, 1, CV_PI / 180, 100);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        Point pt1(cvRound(x0 + 1000 * (-b)),
            cvRound(y0 + 1000 * (a)));
        Point pt2(cvRound(x0 - 1000 * (-b)),
            cvRound(y0 - 1000 * (a)));
        line(color_dst, pt1, pt2, Scalar(0, 0, 255), 3, 8);
    }
#else
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI / 180, 80, 30, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        line(color_dst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
    }
#endif
    namedWindow("Source", 1);
    imshow("Source", src);

    namedWindow("Detected Lines", 1);
    imshow("Detected Lines", color_dst);

    waitKey(0);
    return 0;
}