/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

/* This is the file in which the input image is obtained directly from the camera at run-time. The executable generated from this file has 2 arguments - first is the number of peripheral circles in the marker and the second is  number to be appended to the logfile. eg: logfileX.txt - X = 0 to 9. 
This file will take the image as input, try to detect the marker and report the circle parameters if the marker is detected and print "circles not found" on the console if the marker is not found.
*/

#include "header.h"
#include "find_identifier.cc"
#include "find_border.cc"
#include "makeroi.cc"


int main(int argc, char **argv)
{
	CvCapture* capture = NULL ;
    
	CvMemStorage* storage = cvCreateMemStorage(0);
	IplImage *img0=NULL, *img = NULL;               // Always initialize pointers to NULL if not assigning

	int periphery = 0;
	bool brk = false;
	int pc = (int)argv[1][0] - 48 ;                 // The first argument - number of peripheral circles to detect
	int hc = (int)argv[2][0] - 48 ;					// The second argument - number of hollow circles to detect
	int pospos = (int)argv[3][0] - 48;				// The third argument - append this to the logfile name	 
	int i;
	
	int rows = get_rows("calibrate.txt");			// This file should always exist in the same folder
	
	float arr_height[rows];
	float arr_dist[rows];
	float arr_width[rows];
	line arr_lines[rows-1];							// The definition of this class is included in the "distance.cc" file
	
	gen_calibdata("calibrate.txt",arr_height, arr_width, arr_dist,rows);	// This function will generate the calibration data

	for(i=1;i<=20;++i)
		{
		brk = false;
		capture = cvCaptureFromCAM(1);                  // '1' - select an external webcam, '-1' - select any webcam

		if(!capture)
			{
			printf("Null capture!");
			return 11;									    // End execution if capture is NULL	
			}

		img0=cvQueryFrame(capture);						// Get a frame from the capture					  

		img=cvCreateImage(cvGetSize(img0),img0->depth,1);  
		cvCvtColor(img0,img,CV_RGB2GRAY);				// Convert the color image into grayscale

		CvSeq* val = findSquares4(img,storage );		// This function exists in the file "find_border.cc" - it returns a sequence containing sets of 4 points that form rectangles or trapezia - which narrows down the search for the identifier circles
	
		for(int index=0;index<val->total ; index += 4)
			{
			CvRect myroi = makeROI(val,index);			// This function exists in the file "makeroi.cc" - it returns a CvRect structure that contains data required to describe the region of interest for various functions
			periphery = findcircles(img,storage,myroi,pc,hc,pospos,arr_height,arr_lines); // This function exists in "find_identifier.cc" - it returns the number of peripheral circles found in the region of interest specified in the arguments

			if(periphery >= pc)							// This is the breaking condition - indicating that marker has been found
				{		
				printf("Circles found - exiting\n");				
				brk = true;
				break;
				}
			}

		if(!brk)										//  This is the case when the marker has not been detected
			{
			printf("\ncircles not found - %d\n",i);
			}

		cvReleaseCapture(&capture);
		printf("\n\n%d\n",i);
		}

	cvReleaseImage(&img0);
	cvReleaseImage(&img);
	cvClearMemStorage( storage );
	cvReleaseMemStorage( &storage );				// Release all memory allocated by you

	return 0;
	}

