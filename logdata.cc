/* This file contains functions for data-logging. The call to these functions have been made in the file "find_identifer.cc".*/
using namespace std;

int logdata(double width, double height, int decode,int position)
{
char filename[15];
int k=sprintf(filename,"logfile%d.txt",position);
ofstream buddha;
buddha.open(filename,ios::out | ios::app | ios::binary); // Open the file in append mode
buddha<<"Width = "<<width<<" Height = "<<height<<" Decoded value = "<<decode<<endl;
buddha.close();
return 1;
}

// This function adds a newline to the log file. Uncomment the call to this function to make the logfile more readable.

int logspace(char filename[])
{
ofstream buddha;
buddha.open(filename,ios::out | ios::app | ios::binary);
buddha<<endl;
buddha.close();
return 0;
}
