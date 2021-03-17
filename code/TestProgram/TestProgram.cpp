#include <opencv2/gapi/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

//==============================================================================================
// Reference:
//==============================================================================================
// https://www.docs.opencv.org/2.4/doc/tutorials/introduction/display_image/display_image.html
//==============================================================================================

//==============================================================================================
// Input data:
//==============================================================================================
// the input folder
string input_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\data\\";

// the input image file name
string input_image_fname = input_folder + "in000100.jpg";

//==============================================================================================
// Output folder:
//==============================================================================================
// output folder name
string output_folder = "C:\\Users\\mghaz\\Documents\\MyProfDev\\MyPD-2021\\Udemy\\Courses\\Completed\\OpenCV\\Course-001\\Exercises\\OpenCV-Installation\\results\\";

/// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;


int mainNew(int argc, char** argv)
{
    //==============================================================================================
    // Part 1: Read and display an image:
    //==============================================================================================
    // display the input image file name
    cout << "Input image file name = " << input_image_fname << endl;

    Mat img;
    img = imread(input_image_fname, IMREAD_COLOR);   // Read the file

    if (!img.data)                              // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", img);                   // Show our image inside it.
   
    // save the input image
    imwrite(output_folder + "in000100.jpg", img );
    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();

    //==============================================================================================
    // Part 2: Capture Images from Webcam
    //==============================================================================================
    // Reference:
    //==============================================================================================
    // https://www.docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html?highlight=video%20capture
    //============================================================================================== 
    // Create a Mat object to store the frame
    Mat frame;

    // Declare a VideoCapure variable:
    // - It will cature frames from the webcam
    // VideoCapture cap;

    // a video frame counter
    int frame_counter = 0;

    // Declare a VideoCapure variable:
    // - It will cature frames from the webcam
    VideoCapture cap(0); // open the default camera
    if (!cap.isOpened())  // check if we succeeded
        return -1;

    for (int frame_counter = 0; frame_counter < 10; frame_counter++)
    {
        // Capure a frame and store in the image
        cap >> frame;

        // Create a window for display.
        namedWindow("The next video frame", WINDOW_AUTOSIZE);

        // display the captured frame
        imshow("The next video frame", frame);

        // save the frame to disk
        imshow("The next video frame", frame);

        // set the video frame file name
        string frame_fname = output_folder + "frame-" + std::to_string(frame_counter) + ".jpg";

        // save the video frame
        imwrite(frame_fname, frame);

        // Wait for a keystroke in the window
        if (waitKey(10) >= 0) break;
    }

    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();

    //==============================================================================================
    // Part 3: Color Space oOnversions
    //==============================================================================================
    // Reference:
    //==============================================================================================
    // https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html
    //============================================================================================== 
    // 3.1) Convert to RGB to grayscale image
    //==============================================================================================
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_RGB2GRAY);
    // save the input image
    imwrite(output_folder + "in000100-gray.jpg", img_gray);
    // Display the origonal image
    namedWindow("RGB image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("RGB image", img);                   // Show our image inside it.
    // Display the grayscale image
    namedWindow("Grayscale image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Grayscale image", img_gray);                   // Show our image inside it.

    //==============================================================================================
    // 3.2) Convert to RGB to HSV image
    //==============================================================================================
    Mat img_hsv;
    cvtColor(img, img_hsv, COLOR_RGB2HSV);
    // save the input image
    imwrite(output_folder + "in000100-hsv.jpg", img_hsv);
    // Display the HSV image
    namedWindow("HSV image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("HSV image", img_hsv);                   // Show our image inside it.

    //==============================================================================================
    // 3.3) Convert to RGB to CIELAB image
    //==============================================================================================
    Mat img_lab;
    cvtColor(img, img_lab, COLOR_RGB2Lab);
    // save the input image
    imwrite(output_folder + "in000100-lab.jpg", img_lab);
    // Display the CIELAB image
    namedWindow("CIELAB image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("CIELAB image", img_lab);                   // Show our image inside it.

    //==============================================================================================
    // 3.4) Convert to RGB to YCrCb image
    //==============================================================================================
    Mat img_ycrcb;
    cvtColor(img, img_ycrcb, COLOR_RGB2YCrCb);
    // save the input image
    imwrite(output_folder + "in000100-ycrcb.jpg", img_ycrcb);
    // Display the YCrCb image
    namedWindow("YCrCb image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("YCrCb image", img_lab);                   // Show our image inside it.

    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();

    //==============================================================================================
    // Part 4: Image Smoothing:
    //==============================================================================================
    // Reference:
    //==============================================================================================
    // https://www.docs.opencv.org/2.4/doc/tutorials/imgproc/gausian_median_blur_bilateral_filter/gausian_median_blur_bilateral_filter.html?highlight=image%20smoothing
    //============================================================================================== 
    // the input image file name
    input_image_fname = input_folder + "lena.jpg";
    // Load the source image
    Mat src = imread(input_image_fname, IMREAD_COLOR);   // Read the file
    // Check for invalid input
    if (!src.data)                              
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Display window", src);                   // Show our image inside it.

    // save the input image
    imwrite(output_folder + "lena.jpg", src);

    //==============================================================================================
    // 4.1) Blur Filter
    //==============================================================================================
    // make a copy of the input image
    Mat dst = src.clone();
    // Apply the Blur filter
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        blur(src, dst, Size(i, i), Point(-1, -1));
    }
    // save the input image
    imwrite(output_folder + "lena-blur.jpg", dst);
    // Display the Blur image
    namedWindow("Blur image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Blur image", dst);                   // Show our image inside it.


    //==============================================================================================
    // 4.2) Gaussian Blur Filter
    //==============================================================================================
    // make a copy of the input image
    dst = src.clone();
    // Apply the Blur filter
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
    }
    // save the input image
    imwrite(output_folder + "lena-gauss-blur.jpg", dst);
    // Display the Blur image
    namedWindow("Gaussian Blur image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Gaussian Blur image", dst);                   // Show our image inside it.

    //==============================================================================================
    // 4.3) Median Blur Filter
    //==============================================================================================
    // make a copy of the input image
    dst = src.clone();
    // Apply the Blur filter
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        medianBlur(src, dst, i);
    }
    // save the input image
    imwrite(output_folder + "lena-median-blur.jpg", dst);
    // Display the Blur image
    namedWindow("Median Blur image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Median Blur image", dst);                   // Show our image inside it.

    //==============================================================================================
    // 4.3) Bilateral  Filter
    //==============================================================================================
    // make a copy of the input image
    dst = src.clone();
    // Apply the Blur filter
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        bilateralFilter(src, dst, i, i * 2, i / 2);
    }
    // save the input image
    imwrite(output_folder + "lena-bilateral.jpg", dst);
    // Display the Blur image
    namedWindow("Bilateral image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Bilateral image", dst);                   // Show our image inside it.

    // Wait for a keystroke in the window
    waitKey(0);
    // close all windows
    cv::destroyAllWindows();

    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;

}