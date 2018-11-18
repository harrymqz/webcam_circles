//OpenCV 
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

// Std
#include <iostream>
#include <cstdlib>
#include <vector>

// Constants
const int GAUSSIAN_BLUR_SIZE = 7;
const double GAUSSIAN_BLUR_SIGMA = 2; 
const double CANNY_EDGE_TH = 150;
const double HOUGH_ACCUM_RESOLUTION = 2;
const double MIN_CIRCLE_DIST = 40;
const double HOUGH_ACCUM_TH = 70;
const int MIN_RADIUS = 20;
const int MAX_RADIUS = 100;

int main(int argc, char *argv[]) 
{
    // OpenCV video capture object
    cv::VideoCapture camera;

    // OpenCV image object
    cv::Mat image;

    // Camera id. Associated to device number in /dev/videoX
	int cam_id;
    cv::Mat gray_image;
    std::vector<cv::Vec3f> circles;
    cv::Point center;
    int radius;
    
	// Check user args
	switch(argc)
	{
        // No argument provided, so try /dev/video0
		case 1:
			cam_id = 0;  
			break;
        // An argument is provided. Get it and set cam_id
		case 2:
			cam_id = atoi(argv[1]);
			break; 
		default: 
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl; 
			std::cout << "EXIT program." << std::endl; 
			break; 
	}
	
	// Advertising to the user 
	std::cout << "Opening video device " << cam_id << std::endl;

    // Open the video stream and make sure it's opened
    if( !camera.open(cam_id) ) 
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    // Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		// Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image)) 
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }
        		
        // **************** Find circles in the image ****************************
        
        // Clear previous circles
        circles.clear();

        // If input image is RGB, convert it to gray 
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);

        // Reduce the noise so we avoid false circle detection
        cv::GaussianBlur( gray_image, gray_image, cv::Size(GAUSSIAN_BLUR_SIZE, GAUSSIAN_BLUR_SIZE), GAUSSIAN_BLUR_SIGMA );

        // Apply the Hough Transform to find the circles
        cv::HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, HOUGH_ACCUM_RESOLUTION, MIN_CIRCLE_DIST, CANNY_EDGE_TH, HOUGH_ACCUM_TH, MIN_RADIUS, MAX_RADIUS );
        
        // Draw circles on the image      
        for(unsigned int ii = 0; ii < circles.size(); ii++ )
        {
            if ( circles[ii][0] != -1 )
            {
                    center = cv::Point(cvRound(circles[ii][0]), cvRound(circles[ii][1]));
                    radius = cvRound(circles[ii][2]);
                    cv::circle(image, center, 5, cv::Scalar(0,0,255), -1, 8, 0 );// circle center in green
                    cv::circle(image, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );// circle perimeter in red
            }
        }      
        
        // ********************************************************************
    
        // Show image
        cv::imshow("Output Window", image);

		// Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        // if(cv::waitKey(1) >= 0) break;
        if((unsigned char)(cv::waitKey(1)) == 'q') break;
    }   
}