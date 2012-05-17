#include "header.h"

/* This function return cosine of the angle formed by 3 points - 'pt1' -- 'pt0' -- 'pt2' with 'pt0' being the middle point. Simple trigonometry is used for the angle calculation.
*/
double angle( CvPoint* pt1, CvPoint* pt2, CvPoint* pt0 )
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;
	double dx2 = pt2->x - pt0->x;
	double dy2 = pt2->y - pt0->y;
	return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// This functions detects and stores all rectangles and trapezia in the image

CvSeq* findSquares4( IplImage* img, CvMemStorage* storage )
{
	// All the declarations start now
	CvSeq* contours;
	int i, c, l, N = 11, thresh=50, s=0, sloperet=0;
	IplImage* timg = cvCloneImage( img );						// Make a copy of input image
	IplImage* gray = cvCreateImage( cvGetSize(img), 8, 1 );
	IplImage* pyr = cvCreateImage( cvSize((img->width)/2, (img->height/2)), 8, 1 );
	IplImage* puch = NULL;
	CvSeq* result;
	CvPoint *pp1 = NULL,*pp2 = NULL,*pp3 = NULL,*pp4 = NULL;
	double s2=0,t=0,sl=0,ht=0;
	double area=0,p=0,metric=0,len1=0,len2=0;
	// End of declarations
	
	// Create empty sequence that will contain points - 4 points per square (the square's vertices)
	CvSeq* squares = cvCreateSeq( 0, sizeof(CvSeq), sizeof(CvPoint), storage );

	// Select the entire image as ROI now
	cvSetImageROI( timg, cvRect( 0, 0, img->width, img->height ));

	// Down-scale and up-scale the image to filter out the noise
	cvPyrDown( timg, pyr, 7 );
	cvPyrUp( pyr, timg, 7 );
	
	// Since, we are using a grayscale image, we don't need to loop through 3 channels - hence the terminating condition 'c<1'
	for( c = 0; c < 1; c++ )
		{
		// If you are using a color image, put the channel extraction code here
		
		// try several threshold levels
		for( l = 1; l < N; l++ )
			{
			// Hack: use Canny instead of zero threshold level. Canny helps to catch squares with gradient shading
			if( l == 0 )
			{
			// Apply Canny. Take the upper threshold from slider and set the lower to 0 (which forces edges merging)
			   cvCanny( tgray, gray, 0, thresh, 5 );
			// Dilate canny output to remove potential holes between edge segments
			   cvDilate( gray, gray, 0, 1 );
			// We did not need to apply Canny as threshold for our images was in the range 70-110. You can try ignoring it too!   
			}
			else
			{
			// Apply threshold if l!=0:
			cvThreshold( timg, gray, (l+1)*255/N, 255, CV_THRESH_BINARY );
			}

			// Find contours and store them all as a list
			cvFindContours( gray, storage, &contours, sizeof(CvContour),CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE );
			puch = cvCreateImage(cvGetSize(gray),gray->depth,3);
			
			// Loop through each contour
			while( contours )
				{
				// approximate contour with accuracy proportional to the contour perimeter
				result = cvApproxPoly( contours, sizeof(CvContour), storage,
				CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0 );
				// Square contours should have 4 vertices after approximation, a relatively large area (to filter out noisy contours) and be convex.
				// Note: Absolute value of an area is used because Area may be positive or negative - in accordance with the contour orientation
				area = fabs(cvContourArea(contours,CV_WHOLE_SEQ));
				p = fabs(cvArcLength(contours,CV_WHOLE_SEQ,-1));
				metric = 16*area/(p*p);
				if( result->total == 4 && cvCheckContourConvexity(result) && area>100 )
					{
					s = 0;
					s2 = 0;

					for( i = 0; i < 5; i++ )
						{
						// Find compare angle between joint edges (comparison of cosines)
							if( i >= 2 )
								{
								t= fabs(angle((CvPoint*)cvGetSeqElem( result, i),(CvPoint*)cvGetSeqElem( result, i-2),(CvPoint*)cvGetSeqElem( result, i-1)));
								s2 = s2 > t ? s2 : t; // Consistently update s2 with the maximum value of cosines

								len1 = length((CvPoint*)cvGetSeqElem( result, i),(CvPoint*)cvGetSeqElem( result, i-1));
								len2 = length((CvPoint*)cvGetSeqElem( result, i-1),(CvPoint*)cvGetSeqElem( result, i-2));

								if (inbetween(len1*len2,area,0.1) == 1) // Area criterion - checking if product of adjacent sides ~ Area of contour
									{
									++s;
									//printf("s value %d\n",s);
									}
								}
						}

					// If cosines of all angles are small (all angles are ~90 degree) and area criterion is also satisfied for 3 pairs of sides then write quandrange vertices to resultant sequence
					if( s == 3 && s2<0.1 )
						{
						for( i = 0; i < 4; i++ )
							cvSeqPush( squares,	(CvPoint*)cvGetSeqElem( result, i));
						}
					
					else
						{
							pp1 = (CvPoint*)cvGetSeqElem( result, 0);
							pp2 = (CvPoint*)cvGetSeqElem( result, 1);
							pp3 = (CvPoint*)cvGetSeqElem( result, 2);
							pp4 = (CvPoint*)cvGetSeqElem( result, 3);
							sloperet = findparallel(pp1,pp2,pp3,pp4); // This function can be found in "allied.cc" and gives information about the parallel pair of sides.

							if(sloperet == 1)
							{
							sl = slope(pp1,pp2);
							ht = fabs(((pp3->y - pp1->y)-(sl*(pp3->x - pp1->x)))/sqrt((sl*sl) + 1));
							if (inbetween(0.5*(length(pp1,pp2) + length(pp3,pp4))*ht,area,0.5) == 1) // This is checking for trapezium - if the marker is seen at an angle, the rectangle will look like a trapezium
								{
								cvSeqPush( squares,pp1);
								cvSeqPush( squares,pp2);
								cvSeqPush( squares,pp3);
								cvSeqPush( squares,pp4);
								}
							}

							else if(sloperet == 2)
								{
								sl = slope(pp1,pp3);
								ht = fabs(((pp4->y - pp1->y)-(sl*(pp4->x - pp1->x)))/sqrt((sl*sl) + 1));
								if (inbetween(0.5*(length(pp1,pp3) + length(pp2,pp4))*ht,area,0.2) == 1)
									{
									cvSeqPush( squares,pp1);
									cvSeqPush( squares,pp2);
									cvSeqPush( squares,pp3);
									cvSeqPush( squares,pp4);
									}
								}
							else if(sloperet == 3)
								{
								sl = slope(pp1,pp4);
								ht = fabs(((pp4->y - pp3->y)-(sl*(pp4->x - pp3->x)))/sqrt((sl*sl) + 1));
								if (inbetween(0.5*(length(pp1,pp4) + length(pp2,pp3))*ht,area,0.5) == 1)
									{
									cvSeqPush( squares,pp1);
									cvSeqPush( squares,pp2);
									cvSeqPush( squares,pp3);
									cvSeqPush( squares,pp4);
									}
								}
						}
					}
				contours = contours->h_next;
				}
			}
		}

	// Clean up!
	cvReleaseImage( &gray );
	cvReleaseImage( &pyr );
	cvReleaseImage( &timg );
	cvReleaseImage( &puch );
	return squares;
}


// The function draws all the squares in the image

void drawSquares( IplImage* img, CvSeq* squares )
{
    IplImage* imgcontours = NULL;
	CvPoint pt[4];
	//printf("squares->total %d\n",squares->total);

	CvSeqReader reader;
    IplImage* cpy = cvCloneImage( img );
    int i,count;
	
    // Initialize reader of the sequence
    cvStartReadSeq( squares, &reader, 0 );
    cvNamedWindow("draw squares",CV_WINDOW_AUTOSIZE);
    // Read 4 sequence elements at a time (all vertices of a square)
    for( i = 0; i < squares->total; i += 4 )
		{
			CvPoint* rect = pt;
			count = 4;

			// Read 4 vertices
			memcpy( pt, reader.ptr, squares->elem_size );
			CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
			memcpy( pt + 1, reader.ptr, squares->elem_size );
			CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
			memcpy( pt + 2, reader.ptr, squares->elem_size );
			CV_NEXT_SEQ_ELEM( squares->elem_size, reader );
			memcpy( pt + 3, reader.ptr, squares->elem_size );
			CV_NEXT_SEQ_ELEM( squares->elem_size, reader );

			// Draw the square as a closed polyline
			imgcontours = cvCreateImage(cvGetSize(cpy),8,3);
			cvCvtColor( cpy, imgcontours, CV_GRAY2BGR );
			cvPolyLine( imgcontours, &rect, &count, 1, 1, CV_RGB(0,255,0), 1, 8 );

			cvShowImage("draw squares",imgcontours);
			cvWaitKey(0);

		}
    cvReleaseImage( &cpy );
    cvReleaseImage(&imgcontours);
}
