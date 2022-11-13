/********************************************************************
* File: sobel.c
*
* Description: this file implements a sobel filtering algorithm
*
* Author: Ethan Najmy
*
* Revisions:
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
* Function: to442_grayscale()
*
* Description: will convert an image/frame to grayscale
*
* cv::Mat &image: takes the video frame Mat object
* cv::Mat &grayImage: outputs grayscale frame
* cv::Mat temp: used to create a 1 channel Mat object the same
* 	size as the input image
* blue, green, red, gray: stores the appropriate RBG/grayscale value
* 
* 
* return: void (modifies parameters inputted rather than return)
*-------------------------------------------------------------*/
void to442_grayscale(cv::Mat &image, cv::Mat &grayImage){	

	/* Create temp Mat object for 1 channel use
	 * Need to use a temp Mat to initialize same row/col
	 * as the input image for proper sizing */
	cv::Mat temp(image.rows, image.cols, CV_8UC1);

	// Itterate through columns and rows grabbing RGB values
	for (int i=0; i<image.rows; i++){
		for (int j=0; j<image.cols; j++){
			
			/* Grab RGB values:
			 * - Index [0] is blue
			 * - Index [1] is green
			 * - Index [2] is red
			 * OpenCV uses BGR rather than RGB */
			int blue = image.at<cv::Vec3b>(i,j)[0];
			int green = image.at<cv::Vec3b>(i,j)[1];
			int red = image.at<cv::Vec3b>(i,j)[2];
			
			// Apply ITU-R (BT.709) grayscale filtering
			double gray = (blue * 0.0722) 
				+ (green * 0.7152) + (red * 0.2126);
				
			// Save grayscale value to temporary Mat
			temp.at<uchar>(i,j) = gray;
		}	
	}
	// Clone temp Mat to grayImage for output
	grayImage = temp.clone();
}

/*--------------------------------------------------------------
* Function: to442_sobel()
*
* Description: applies the sobel filter algorithm to a frame
*
* cv::Mat &grayImage: takes in the grayscale Mat object
* cv::Mat &sobelImage: outputs the Sobel Filtered object
* cv::Mat temp: used to create a Mat same size at grayImage
*
* return: void (modifies parameters inputted rather than return)
*-------------------------------------------------------------*/
void to442_sobel(cv::Mat &grayImage, cv::Mat &sobelImage){	

	/* Create temp Mat object for 1 channel use
	 * Need to use a temp Mat to initialize same row/col
	 * as the input image for proper sizing */
	cv::Mat temp(grayImage.rows, grayImage.cols, CV_8UC1);

	/* Itterate through all cols & rows (except border cols/rows
	* for sobel filtering */
	for (int i=1; i<(sobelImage.rows - 1); i++){
		for (int j=1; j<(sobelImage.cols - 1); j++){
		
			/* Calculate the x-component of Sobel using the
			 * following matrix:
			 * [-1 0 1
			 *  -2 0 2
			 *  -1 0 1] 
			 * Take absolute value as well */
			int x = abs((grayImage.at<uchar>(i-1,j-1) * -1)
				+ (grayImage.at<uchar>(i,j-1) * -2)
				+ (grayImage.at<uchar>(i+1,j-1) * -1)
				+ (grayImage.at<uchar>(i-1,j+1))
				+ (grayImage.at<uchar>(i,j+1) * 2)
				+ (grayImage.at<uchar>(i+1,j+1)));
				
			// Ensure values are within grayscale range (0-255)
			if (x < 0)
				x = 0;
			else if (x > 255)
				x = 255;
				
			/* Calculate the y-component of Sobel using the
			 * following matrix:
			 * [ 1  2  1
			 *   0  0  0
			 *  -1 -2 -1 ] 
			 * Take absolute value as well */
			int y = abs((grayImage.at<uchar>(i-1,j-1))
				+ (grayImage.at<uchar>(i-1,j) * 2)
				+ (grayImage.at<uchar>(i-1,j+1))
				+ (grayImage.at<uchar>(i+1,j-1) * -1)
				+ (grayImage.at<uchar>(i+1,j) * -2)
				+ (grayImage.at<uchar>(i+1,j+1) * -1));
				
			// Ensure values are within grayscale range (0-255)
			if (y < 0)
				y = 0;
			else if (y > 255)
				y = 255;
				
			// Add x & y components and save to temp Mat
			temp.at<uchar>(i,j) = (x+y);
		}	
	}
	// Clone temp Mat object to sobelImage for output
	sobelImage = temp.clone();
}
