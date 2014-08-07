// NoiseReduction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cv.h>
#include <highgui.h>

int main()
{
	IplImage* imgRed[25];
	IplImage* imgGreen[25];
	IplImage* imgBlue[25];

	for(int i=0;i<25;i++)
	{
		IplImage* img;

		char filename[150];
		sprintf(filename, "%d.jpg", (i+1));
		img = cvLoadImage(filename);

		imgRed[i] = cvCreateImage(cvGetSize(img), 8, 1);
		imgGreen[i] = cvCreateImage(cvGetSize(img), 8, 1);
		imgBlue[i] = cvCreateImage(cvGetSize(img), 8, 1);

		cvSplit(img, imgRed[i], imgGreen[i], imgBlue[i], NULL);

		cvReleaseImage(&img);
	}
	
	CvSize imgSize = cvGetSize(imgRed[0]);
	IplImage* imgResultRed = cvCreateImage(imgSize, 8, 1);
	IplImage* imgResultGreen = cvCreateImage(imgSize, 8, 1);
	IplImage* imgResultBlue = cvCreateImage(imgSize, 8, 1);

	IplImage* imgResult = cvCreateImage(imgSize, 8, 3);

	for(int y=0;y<imgSize.height;y++)
	{
		for(int x=0;x<imgSize.width;x++)
		{
			int theSumRed=0;
			int theSumGreen=0;
			int theSumBlue=0;
			for(int i=0;i<25;i++)
			{
				theSumRed+=cvGetReal2D(imgRed[i], y, x);
				theSumGreen+=cvGetReal2D(imgGreen[i], y, x);
				theSumBlue+=cvGetReal2D(imgBlue[i], y, x);
			}

			theSumRed = (float)theSumRed/25.0f;
			theSumGreen = (float)theSumGreen/25.0f;
			theSumBlue = (float)theSumBlue/25.0f;

			cvSetReal2D(imgResultRed, y, x, theSumRed);
			cvSetReal2D(imgResultGreen, y, x, theSumGreen);
			cvSetReal2D(imgResultBlue, y, x, theSumBlue);
		}
	}

	cvMerge(imgResultRed, imgResultGreen, imgResultBlue, NULL, imgResult);

	cvNamedWindow("averaged");
	cvShowImage("averaged", imgResult);
	
	cvWaitKey(0);

	return 0;
}