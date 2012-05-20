/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include "header.h"

// This is a simple function to return the smaller of two input integers

int minimum(int a, int b)
 {
  if (a<b)
	  return a;
  else
	  return b;
 }

 // This is a simple function to return the larger of two input integers
 
 int maximum(int a, int b)
 {
  if (a>b)
  	  return a;
  else
  	  return b;
 }

 /* This function basically identifies the minimum and maximum 'x' and 'y' coordinates among the four points extracted from the input sequence 'squares'. These values help us establish a rectangular area that will be treated as the Region of Interest (ROI) for all future operations thus making the program more efficient by not wasting the processing resources.
 */

CvRect makeROI(CvSeq* squares,int index)
{
	int xmin=0, xmax=0, ymin=0, ymax=0, width=0, height=0;

	xmin =  minimum(minimum(minimum(((CvPoint*)cvGetSeqElem(squares,index))->x,((CvPoint*)cvGetSeqElem(squares,index+1))->x),
				((CvPoint*)cvGetSeqElem(squares,index+2))->x),((CvPoint*)cvGetSeqElem(squares,index+3))->x);
	xmax =  maximum(maximum(maximum(((CvPoint*)cvGetSeqElem(squares,index))->x,((CvPoint*)cvGetSeqElem(squares,index+1))->x),
				((CvPoint*)cvGetSeqElem(squares,index+2))->x),((CvPoint*)cvGetSeqElem(squares,index+3))->x);

	ymin =  minimum(minimum(minimum(((CvPoint*)cvGetSeqElem(squares,index))->y,((CvPoint*)cvGetSeqElem(squares,index+1))->y),
				((CvPoint*)cvGetSeqElem(squares,index+2))->y),((CvPoint*)cvGetSeqElem(squares,index+3))->y);
	ymax =  maximum(maximum(maximum(((CvPoint*)cvGetSeqElem(squares,index))->y,((CvPoint*)cvGetSeqElem(squares,index+1))->y),
				((CvPoint*)cvGetSeqElem(squares,index+2))->y),((CvPoint*)cvGetSeqElem(squares,index+3))->y);

	width = abs(xmax-xmin); // Width of the rectangular ROI
	height = abs(ymax-ymin); // Height of the rectangular ROI

	// printf("x min = %d, x max = %d, y min = %d, y max = %d, width = %d, height = %d\n",xmin,xmax,ymin,ymax,width,height);
	CvRect rect = cvRect(xmin,ymin,width,height);
	return rect;
}
