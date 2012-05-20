/* Original code by: Shashank Kulkarni and Aditya Buddhavarapu. Please share and re-share this code. And give due credits
wherever possible. Thank you! You are awesome!
*/

#include <stdio.h>

/*
This is one of the most critical functions of our project. This takes 'width' of the circle as an argument and returns the distance of the camera from the marker as a double value. The method used by us was that we logged the circle widths for every 50 cm of physical distance and carried out linear interpolation between these readings. For instance:

Physical distance      Circle-width
-----------------      ------------
     100 cm               90 px
	 150 cm				  70 px
	 200 cm 			  40 px
	 
Then, on reciving the width input as 80 px, the distance returned would be 125 cm. The same for 50 px will be 183.33 cm.
Please note, this piece of code contains values from our experimental data.

We were able to achieve an accuracy of +- 5 cm with this crude method. More data points will only increase the accuracy.
*/

double distance(double width)
{
	double dist=0;
	if(width >= 47 && width <= 89)
		{	
		if(width >= 62)
			dist = (7150-50*width)/27;
		else
			dist = (1070-10*width)/3;
		}
	else if(width >= 30 && width <= 47)
		{
		if(width >= 36)
			dist = (4550-50*width)/11;
		else
			dist = (1650-25*width)/3;
		}
	else if(width >= 22 && width <= 30)
		dist = (1350-25*width)/2;
	else if(width >= 18 && width <= 22)
		dist = 950-25*width;
		
		return dist;
}
