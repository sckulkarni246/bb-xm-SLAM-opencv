/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

/* While executing, pass the name of the image as the first argument and the number of peripheral circles in the marker as the second argument. This file will take the image as input, try to detect the marker and report the circle parameters if the marker is detected and print "circles not found" on the console if the marker is not found.
*/

#include "header.h"
#include "find_identifier.cc"
#include "find_border.cc"
#include "makeroi.cc"

int main(int argc, char **argv)
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	IplImage *img0=NULL, *img = NULL;
	int periphery = 0; // Keeps track of the number of periphery circles found by the circle identifying function
	bool brk = false;
	int pc = (int)argv[2][0] - 48 ;
		
	img0=cvLoadImage(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	cvNamedWindow("original image",CV_WINDOW_AUTOSIZE);
	cvShowImage("original image",img0);
	cvWaitKey(0); 					// // Display the image before starting the processing - press a key to continue
	
	img=cvCloneImage(img0);			// Make a copy of the image  

	CvSeq* val = findSquares4(img,storage );	// This function exists in the file "find_border.cc" - it returns a sequence containing sets of 4 points that form rectangles or trapezia - which narrows down the search for the identifier circles
	
	for(int index=0;index<val->total ; index += 4)
	{
		CvRect myroi = makeROI(val,index);		// This function exists in the file "makeroi.cc" - it returns a CvRect structure that contains data required to describe the region of interest for various functions
		periphery = findcircles(img,storage,myroi,pc);// This function exists in "find_identifier.cc" - it returns the number of peripheral circles found in the region of interest specified in the arguments
		if(periphery >= pc)						// This is the breaking condition - indicating that marker has been found
			{
			printf("circles found\n");
			brk = true;
			break;
			}
	}
	if(!brk)									// This is the case when the marker has not been detected
		printf("\ncircles not found\n");		
		
	cvReleaseImage(&img0);
	cvReleaseImage(&img);
	cvClearMemStorage( storage );
	cvReleaseMemStorage( &storage );
	return 0;
}

