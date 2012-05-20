/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include  "header.h"
#include "distance.cc"

using namespace std;

// This function returns the centre of the rectangle encompassing the circles

CvPoint2D32f marker_centre(CvRect rect)
{ 
	double x_cen,y_cen;
	x_cen = (2*rect.x + rect.width)/2 ;
	y_cen = (2*rect.y + rect.height)/2 ;
	CvPoint2D32f centre = cvPoint2D32f(x_cen,y_cen);
	return centre;
}

// This function returns the distance of a point from the centre of the image - in the X direction

double disp(double act_ht, double img_ht, double a)
{ 
	double dis;
	dis = (act_ht*(320-a))/img_ht;// 320 depends on image size, take parameter
	return dis;
}

/* In this function, 'decoded' is the decoded value of your marker - you can choose any scheme. We used simple binary system - the first circle from the bottom right is the MSB and the first circle from the top left is the LSB. Each hollow circle is a '1' and filled circle is a '0'. To see the markers we used, see the 'Downloads' section.
*/

void coord(int decoded, double width, double height, CvRect rect)
{
	if(decoded >= 0) 		// you can change this file to complicate your application. eg: for multiple markers, there will be an if-else ladder	
	{
	 cout<<" x = "<<disp(10,height,marker_centre(rect).x)<<",y = "<<distance(height)<<endl; //10 also parameter taken as input
	}

	else
	{
	 cout<<" x = "<<distance(height)<<",y = "<<disp(10,height,marker_centre(rect).x)<<endl;
	}
}

/* We are varying x or y value depending on decoded value. With an angle input in your program, you can vary both simultaneously. This implementation is only indicative.
*/ 



