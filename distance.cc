/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include "header.h"

// Definition of classes used

class line
{
	public:
		double m,c;
};

/*
This is one of the most critical functions of our project. This takes 'height' of the circle as an argument and returns the distance of the camera from the marker as a double value. The method used by us was that we logged the circle heights for every 50 cm of physical distance and carried out linear interpolation between these readings. For instance:

Physical distance      Circle-height
-----------------      ------------
     100 cm               90 px
     150 cm		          70 px
     200 cm 	          40 px
	 
Then, on reciving the height input as 80 px, the distance returned would be 125 cm. The same for 50 px will be 183.33 cm.
Please note, this piece of code contains values from our experimental data.

We were able to achieve an accuracy of +- 2.5 cm with this crude method. More data points will only increase the accuracy.
*/

int located(float loc, float a, float b)
{
	if(loc>=a && loc<=b)
	return 1;
	else
	return 0;
}

double distance(double height, float arr_height[], line arr_lines[])
{
	int rows = get_rows("calibrate.txt");	
	double dist=0.0;
	for(int i=0;i<rows-1;++i)
		{
		if(located(height,arr_height[i],arr_height[i+1]) == 1)
			{
			dist = arr_lines[i].m*height + arr_lines[i].c;
			break;
			}
		}
	return dist;
}
