/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include "header.h"
#include "allied.cc"
#include "logdata.cc"
#include "coordinate.cc"

/* This function detects all the circles and ellipses it can find in the ROI specified by 'rect'. The parameter 'pospos' is the number to be appended to the logfile to be generated. eg: if pospos = 2, the name of the file is logfile2.txt.
The parameter 'pc' is the number of peripheral circles to be detected. It is passed to the main application 'get_capture.cpp' or 'get_image.cpp' as an argument.
*/
int findcircles(IplImage* img, CvMemStorage* storage, CvRect rect, int pc, int hc,int pospos,float arr_height[],line arr_lines[])
{
// All the declarations go here
IplImage *imgcpy = NULL, *imbinary=NULL, *impyr = NULL, *imcontour=NULL ;
CvBox2D ellipse1,ellipse2;
CvSeq* reqdcontours = NULL;
CvSeq* checkcontours = NULL;
CvMemStorage* memellipse1 = cvCreateMemStorage(0);
CvMemStorage* memellipse2 = cvCreateMemStorage(0);
int l=0, N=11, thresh=50, periphery=0, hollow=0,decode=0,pow1=pc;
double area=0, p=0, metric=0.0, calc_area=0 ;
char nameof[15];
// End of declarations

// Create a copy of the input image for processing ahead 
imgcpy=cvCloneImage(img);
impyr = cvCreateImage( cvSize(img->width/2, img->height/2), 8, 1 );

// Scale down and scale up to remove the noise from the image
cvPyrDown( imgcpy, impyr, 7 );
cvPyrUp( impyr, imgcpy, 7 );

// Set the ROI to the desired area passed to the function as a parameter
cvSetImageROI(imgcpy,rect);

imbinary = cvCreateImage(cvSize(rect.width,rect.height),8,1);

for( l = 0; l < N ; l++ )
	{
	reqdcontours = NULL;
	//printf("value of periphery = %d at start\n",periphery);

	//apply threshold if l!=0:
	cvThreshold( imgcpy, imbinary, (l+1)*255/N, 255, CV_THRESH_BINARY_INV );

	int Nc = cvFindContours(imbinary,storage,&reqdcontours,sizeof(CvContour),CV_RETR_TREE);
	//printf("Nc = %d\n",Nc);

	if (Nc >= pc)
		{
		//printf("cnt = %d, threshold = %d\n",cnt,l);// Optional print for debugging
		for( ; ; reqdcontours=reqdcontours->v_next)
			{
			// Resetting values - very critical step
			periphery = 0;
			hollow = 0;
			pow1 = pc;
			decode = 0;
			
			checkcontours = reqdcontours;
			if(samelevel(checkcontours) >= pc)
				{
				for( ; ; checkcontours = checkcontours->h_next )
					{
					ellipse1 = cvMinAreaRect2(checkcontours,memellipse1);
					area = fabs(cvContourArea(checkcontours,CV_WHOLE_SEQ));
					calc_area = 0.785*(ellipse1.size.height)*(ellipse1.size.width);

					if(inbetween(calc_area,area,0.1))
						{
						// printf("outer --> ht = %f,wt = %f\n",ellipse1.size.height,ellipse1.size.width);// Optional print for debugging
						//printf("calc area=%f, contour area=%f\n",calc_area,area);// Optional print for debugging
						periphery ++;
						--pow1;
						//printf("periphery = %d\n",periphery);// Optional print for debugging
						if(inbetween(ellipse1.size.height,ellipse1.size.width,0.1))
							{
							//printf("\nouter circle --> ht = %f,wt = %f\n\n",ellipse1.size.height,ellipse1.size.width);// Optional print for debugging
							//printf("Outer circle\n\n");// Optional print for debugging
							}
						else
							{
							//printf("\nouter ellipse --> ht = %f,wt = %f\n\n",ellipse1.size.height/2,ellipse1.size.width/2);// Optional print for debugging
							//printf("Outer ellipse\n\n");// Optional print for debugging
							}
						if(checkcontours->v_next != NULL)
							{
							ellipse2 = cvMinAreaRect2(checkcontours->v_next,memellipse2);
							area = fabs(cvContourArea(checkcontours->v_next,CV_WHOLE_SEQ));
							calc_area = 0.785*(ellipse2.size.height)*(ellipse2.size.width);

							if(inbetween(calc_area,area,0.1))
								{
								//printf("inner --> ht = %f,wt = %f\n",ellipse2.size.height/2,ellipse2.size.width/2);// Optional print for debugging
								//printf("calc area=%f, contour area=%f\n",calc_area,area); // Optional print for debugging
								hollow ++;
								decode += pow(2,pow1);
								//printf("outer --> ht = %f,wt = %f\n",ellipse1.size.height,ellipse1.size.width);
								//printf("hollow = %d\n",hollow); // Optional print for debugging

								if(inbetween(ellipse2.size.height,ellipse2.size.width,0.1))
									{
									//printf("inner circle --> ht = %f,wt = %f\n\n",ellipse2.size.height/2,ellipse2.size.width/2);// Optional print for debugging
									}
								else
									{
									//printf("inner ellipse --> ht = %f,wt = %f\n\n",ellipse2.size.height/2,ellipse2.size.width/2);// Optional print for debugging
									}
								}
							}
						}
					if(checkcontours->h_next == NULL || periphery == pc)
					break;
					}
				}
				if(reqdcontours->v_next == NULL || periphery == pc)
				break;
			}
		//printf("no of periphery circles is = %d\n",periphery); // Optional print for debugging
		//printf("no of hollow = %d\n",hollow); // // Optional print for debugging
		}
	// Check if the marker has been completely found
	if(periphery == pc && hollow == hc) // In our case, we have used markers with 3 hollow circles compulsorily
		{
		cvResetImageROI(imgcpy);
		printf("Decoded value --> %d\n",decode);
		printf("Peripheral circles --> %d, Hollow circles --> %d\n",periphery,hollow);
		printf("outer --> ht = %f,wt = %f\n",ellipse1.size.height,ellipse1.size.width);
		sprintf(nameof,"logfile%d.txt",pospos);		// Uncomment to log data
		logdata(ellipse1.size.width,ellipse1.size.height,decode,pospos); // Uncomment to log data					
		logspace(nameof); // Introduces a new line in the log file - enhances readability of logfile generated
		coord(decode,ellipse1.size.width,ellipse1.size.height,rect,arr_height,arr_lines); // Call to the most important function - found in "coordinate.cc" - for printing the coordinate on the console
		break;
		}
	}
cvReleaseImage(&imgcpy);
cvReleaseImage(&imbinary);
cvReleaseImage(&impyr);
cvReleaseImage(&imcontour);
cvClearMemStorage( memellipse1 );
cvReleaseMemStorage( &memellipse1 );
cvClearMemStorage( memellipse2 );
cvReleaseMemStorage( &memellipse2 );
return periphery;
}
