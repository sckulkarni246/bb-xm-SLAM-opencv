#include  <stdio.h>
#include <iostream>
#include "distance.cc"

using namespace std;

/* In this function, 'decoded' is the decoded value of your marker - you can choose any scheme. We used simple binary system - the first circle from the bottom right is the MSB and the first circle from the top left is the LSB. Each hollow circle is a '1' and filled circle is a '0'. To see the markers we used, see the 'Downloads' section.
*/

void coord(int decoded, double width)
{
	if(decoded >= 10)               // you can change this file to complicate your application. eg: for multiple markers, there will be an if-else ladder
		cout<<" x = 0, y = "<<distance(width)<<endl;
	else
		cout<<" x = "<<distance(width)<<",y = 0 "<<endl;
}

/* We are varying x or y value depending on decoded value. With an angle input in your program, you can vary both simultaneously. This implementation is only indicative.
*/
