Hello everyone.
For a basic understanding of this project, please visit the project page at http://sckulkarni246.github.com/shashank-kulkarni/ .

In this HOWTO file, I will be telling you the <strong>various interconnections</strong> and <strong>purpose of each file</strong> present in this repo. 

Before we move ahead, please note: <strong>the functions are all defined in *.cc files and the main applications in *.cpp files.</strong>

First, we understand the purpose served by each file.

1) <strong>runthis.sh</strong> - This is the bash file that we used for execution. In this file, changing the value of the terminating condition for the for-loop will help you control the number of times the executable executes. Also, this file assumes that the name of the executable is 'capture' with parameters 6 and 4. For the explanation of the parameters, read on!

2) <strong>get_capture.cpp</strong> - This is the file with which the user interacts. In this file, an image capture is started from the webcam, the image grabbed is sent to various other functions for performing operations and at the end of it, if the circle is not found, a message is printed on the console accordingly.

3) <strong>get_image.cpp</strong> - This is the file very similar to get_capture.cpp in all respects except the fact that instead of an image capture, an existing image from the drive can be loaded. This is the file we used during the testing phase of our project.

4) <strong>find_border.cc</strong> - This is the file which contains the function for detection of the border of our marker i.e. the rectangles and the trapezia (if seen at an angle).

5) <strong>find_identifier.cc</strong> - This is the file which contains the function for detection of the identifier of our marker i.e. the circles and the ellipses (if seen from an angle).
6) allied.cc - This is the file that contains allied functions that are generic in nature.

7) <strong>coordinate.cc</strong> - This is the file that uses the identified parameters from the marker in order to generate the coordinate of the camera with respect to the marker.

8) <strong>distance.cc</strong> - This is the file that contains the function to calculate the distance of the camera from the marker. The values used in this file will vary from implementation to implementation.

9) <strong>header.h</strong> - This is the common header file we used throughout the project so that we don't need to type the include files everywhere.

10) <strong>makeroi.cc</strong> - This is the file that is used to restrict the region of interest of our operation to the bounded area given to us by find_border.cc. This greatly improved the efficiency of our system.
 
Please note, all the files are well-commented. But, in case of any doubt or query, please contact:

1) <strong>Shashank Kulkarni</strong> - shanky.kulkarni@gmail.com

2) <strong>Aditya Buddhavarapu</strong> - bn.aditya.1@gmail.com