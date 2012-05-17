#!/bin/bash

# This shell file can be changed as much as you want. It depends only on the implementation. Please use the shell file only after you are done with testing the 
# executable.
for ((c=1;c<=10;++c)) # change the terminating condition to change the number of times the executable runs - each increment gives 10 more runs
do
./capture 6 4         # run the executable - the first parameter is the number of peripheral circles, second is the number appended to logfile. eg: logfile4.txt
echo $c               # display the value of c at the end of each cycle
done
# This file may not execute directly in Linux. You need to run the following command to make this work: dos2unix runthis.sh