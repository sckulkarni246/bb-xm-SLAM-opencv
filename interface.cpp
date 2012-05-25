/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

/*
This is a simple code that will allow you to test your camera and interface it using OpenCV. On execution, a window will open that will display the capture stream of the camera.
*/
#include "header.h"

int main(void)
{
	IplImage *frame = NULL;
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);
	if(!capture)
		{
		printf("No capture");
		return 1;
		}
	cvNamedWindow("display",CV_WINDOW_AUTOSIZE);
	int i=1;
	while(i<10000)
		{
		frame = cvQueryFrame( capture );
		if(!frame)
			{
			printf("Capture but null frame!");
			return 2;
			}
		cvShowImage("display",frame);
		cvWaitKey(10);
		++i;
		}
	cvReleaseCapture( &capture );
	cvReleaseImage( &frame );
	cvDestroyWindow("display");
	return 0;
}
