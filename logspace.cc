using namespace std;

int logspace(char *filename)
{
ofstream buddha;
buddha.open(filename,ios::out | ios::app | ios::binary);
buddha<<endl;
buddha.close();
return 0;
}
