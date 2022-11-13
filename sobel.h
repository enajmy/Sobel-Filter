/********************************************************************
* File: sobel.h
*
* Description: header file for sobel.c (sobel filtering)
*
* Author: Ethan Najmy
*
* Revision History:
*	- 1.0: file created
*
********************************************************************/
#ifndef _SOBEL_H
#define _SOBEL_H
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>
#include <opencv2/imgcodecs.hpp>

// Function Declaration
void getFile(cv::Mat &file);
void to442_grayscale(cv::Mat &image, cv::Mat &grayImage);
void to442_sobel(cv::Mat &grayImage, cv::Mat &sobelImage);

#endif
