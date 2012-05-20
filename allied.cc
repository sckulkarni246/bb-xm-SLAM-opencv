/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include "header.h"

/* The following function returns the number of members at a particular level in a sequence stored as a tree.
   The parameter 'contour' is assumed to be the first node in that particular level from the left. For instance:
   1-2
   |
   3-4-5
     | |
     6 7
   
   The 'contour' should point to 1,3 and 6/7 for first, second and third level respectively.
*/

int samelevel(CvSeq* contour)
{
	CvSeq* cpcontour=NULL;
	cpcontour = contour;
	int members=0;
	for(;;cpcontour=cpcontour->h_next)
		{
			if(cpcontour->h_next != NULL)
				++members;
			else
				{
				++members;
				break;
				}
		}
	return members;
}

// The following function returns the length of the line segment joining 2 points 'pt1' and 'pt0'

double length( CvPoint* pt1, CvPoint* pt0)
{
	double dx1 = pt1->x - pt0->x;
	double dy1 = pt1->y - pt0->y;

    return sqrt(dx1*dx1 + dy1*dy1);
}

// The following  function checks if the value 'inner' lies in a range of values determined by 'outer' and 'range' parameters

int inbetween(double outer, double inner, double range)
{
	if(inner > (1-range)*outer && inner < (1+range)*outer)
		return 1;
	else
		return 0;
}

// The following function returns the slope of the line segment joining 2 points 'pt1' and 'pt2'

double slope(CvPoint* pt1,CvPoint* pt2)
{
	double sl = (double)(pt2->y - pt1->y)/(pt2->x - pt1->x);
	//printf("Requested slope-> %f\n",sl);
	return sl;
}

// The following function finds out the 2 pairs of points for which the lines joining the paired points are parallel

int findparallel(CvPoint* pt1,CvPoint* pt2,CvPoint* pt3,CvPoint* pt4)
{
	double range  = 0.1;
	if( inbetween(slope(pt1,pt2)/length(pt1,pt2),slope(pt3,pt4)/length(pt3,pt4),range))
		return 1;
	else if( inbetween(slope(pt1,pt3)/length(pt1,pt3),slope(pt2,pt4)/length(pt2,pt4),range))
		return 2;
	else if( inbetween(slope(pt1,pt4)/length(pt1,pt4),slope(pt2,pt3)/length(pt2,pt3),range))
		return 3;
	else
		return 0;
}


