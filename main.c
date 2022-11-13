/********************************************************************
* File: main.c
*
* Description: main file for sobel filter algorithm
*
* Author: Ethan Najmy
*
* Revision History:
*	- 1.0: file created
*
********************************************************************/
#include "sobel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/imgcodecs.hpp>

/*--------------------------------------------------------------
* Function: main()
*
* Description: main function, runs program
*
* cv::Mat frame: used to store individual video frames
* cv::Mat grayFrame: used to store grayscale video frames
* cv::Mat sobelFiltered: used to store Sobel filtered frames
*
* return: int
*-------------------------------------------------------------*/
int main(void){
	// Variable declarations
	cv::Mat frame, grayFrame, sobelFiltered;
	
	// Use OpenCV to read a video file
	cv::VideoCapture capture("motocross.mp4");
	
	// While loop to read all frames
	while(1){
		
		// Save individual frame (starting at first frame)
		capture.read(frame);
		
		// If frame is empty (video is over), break and end
		if (frame.empty())
			break;
		
		// Call grayscale function to convert RGB to grayscale
		to442_grayscale(frame, grayFrame);
		
		// Call sobel function to convert grayscale to Sobel filtered
		to442_sobel(grayFrame, sobelFiltered);
		
		// Show the image/frame that has been filtered
		imshow("Sobel Filter", sobelFiltered);
		
		// Delay
		cv::waitKey(1);
	}
	return 0;
}
