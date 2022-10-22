//------------------------------------------------------------------------- 
// Project: Image and live video stream processing using OpenCV C++ API
//= ========================================================================
// File : live_video_stream_processing_opencv.cpp
// Author : Mohsen Ghazel(mghazel2020)
// Date : Mar 15, 2021
//------------------------------------------------------------------------- 
// Specifications:
//-------------------------------------------------------------------------  
// To demonstrate live video stream processing using OpenCV C++ API built-in 
// functionalities.
//------------------------------------------------------------------------- = 
// History
//------------------------------------------------------------------------- = 
// Date                      Changes                        Author
//= ======================================================================== 
// Mar 15, 2021              Initial definition             mghazel2020
//------------------------------------------------------------------------- = 
// MIT License:
//------------------------------------------------------------------------- = 
// Copyright(c) 2021 mghazel2020
//------------------------------------------------------------------------- = 

// Include statements
// OpenCV
#include <opencv2/imgproc/imgproc.hpp>
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
// declare cv::Mat to store captured frames and their processed versions
//------------------------------------------------------------------------- 
// input frame
Mat frame;
// gray-scale image
Mat gray;
// blurred image
Mat blurred;
// edge detection 
Mat edges;

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
    output_folder = output_folder + "Demo-07-live-video-stream-processing" + "\\";
    // create the output directory
    if (_mkdir(output_folder.c_str()) != 0)
    {
        cout << "Unable to create the output folder: " << output_folder << endl;
    }
    else
    {
        cout << "The output folder created successfully!" << output_folder << endl;
    }

    // initialize the frame counter
    int frame_counter = 0;

    // start capturing and processing frames 
    while (true)
    {
        //----------------------------------------------------
        // 1) Capture a new frame from camera
        //----------------------------------------------------
        // open the default camera
        VideoCapture cap(0); 
        // check if we succeeded
        if (!cap.isOpened())  
            return -1;

        // capture the next frame
        cap >> frame; 
        // check if frame data was captured successfully
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        // save the captured frame
        imwrite(output_folder + "frame-original-" + to_string(frame_counter) + ".jpg", frame);
        // display the frame
        namedWindow("frame", WINDOW_AUTOSIZE);
        // display the frame
        imshow("frame", frame);

        //----------------------------------------------------
        // 2) Process the captured frame
        //----------------------------------------------------
        // 2.1) Convert to gray-scale
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        imwrite(output_folder + "frame-gray-" + to_string(frame_counter) + ".jpg", gray);
        // display the frame
        namedWindow("gray", WINDOW_AUTOSIZE);
        imshow("gray", gray);
        // 2.2) Apply Gaussian blur
        GaussianBlur(gray, blurred, Size(7, 7), 1.5, 1.5);
        imwrite(output_folder + "frame-blurred-" + to_string(frame_counter) + ".jpg", blurred);
        // display the frame
        namedWindow("blurred", WINDOW_AUTOSIZE);
        imshow("blurred", blurred);
        // 2.3) Apply Canny edge detection
        Canny(blurred, edges, 0, 30, 3);
        imwrite(output_folder + "frame-edges-" + to_string(frame_counter) + ".jpg", edges);
        // display the frame
        namedWindow("edges", WINDOW_AUTOSIZE);
        imshow("edges", edges);
        //----------------------------------------------------
        // increment the frame counter
        //----------------------------------------------------
        frame_counter++;

        //----------------------------------------------------
        // Wait for a keystroke in the window
        waitKey(0);
        // close all windows
        cv::destroyAllWindows();
        
        //----------------------------------------------------
        // if user hits ESC then quit
        //----------------------------------------------------
        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    // return
    return 0;
}