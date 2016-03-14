#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
using namespace std;

int write(char *file_name, char *no_of_times, char *snt)
{
    ofstream out_stream;
    out_stream.open(file_name);
    int y= atoi(no_of_times);
    //cout<< "The number of times is:"<<y<<endl;
        for(int i=1; i<=y;i++)
            {
                out_stream<<snt;
            }
    out_stream.close();
    return 0;
}

int read(char *file_name)
{
    ifstream in_stream;

    //cout<<"The file name within function is:"<<file_name<<endl;

    in_stream.open(file_name);

            if(in_stream.fail())
             {
               cerr<<"Could not open file\n";
             }
            else
             {
               char x;
               while (in_stream.get(x))
               cout<< x;
               in_stream.close();
             }
    return 0;
}

int main (int argc, char *argv[])
{
    int rflag = 0;
    int wflag = 0;
    int fflag = 0;
    int pflag = 0;
    int nflag = 0;

    char *fvalue = NULL;
    char *pvalue = NULL;
    char *nvalue = NULL;

    int c;

    while ((c = getopt (argc, argv,"rwf:p:n:"))!= -1)
        switch (c)
        {
        case 'r':
            rflag = 1;
            break;

        case 'w':
            wflag = 1;
            break;

        case 'f':
            fflag = 1;
            fvalue = optarg;
            if (optarg[0]=='-')
                {
                  wflag=0;
                  cerr<<"Please specify the proper file name"<<endl;
                }
            break;

        case 'p':
            pflag = 1;
            pvalue = optarg;
            if (optarg[0]=='-')
                {
                  wflag=0;
                  cerr<<"Please specify string to write"<<endl;
                }
            break;

        case 'n':
            nflag = 1;
            nvalue = optarg;
            if (optarg[0]=='-')
                {
                  wflag=0;
                  cerr<<"Please specify number of times to write a string"<<endl;
                }
            break;

        case '?':
            if (optopt=='f')
                {
                    cerr<<"Please specify a file name"<<endl;
                //    break;
                }
            else if (optopt =='p')
                {
                    cerr<<"A string should be given as an argument"<<endl;
                 //   break;
                }
            else if (optopt =='n')
                {
                    cerr<<"Please give the number of times to write in a file"<<endl;
                   // break;
                }
            else
                {
                    rflag=0;
                    wflag=0;
                    cerr<<"Unknown Option"<<endl;
                    break;
                }
        return 1;
        default:
            cerr<<"getopt"<<endl;
        }

 //cout<<"rflag:"<<rflag<<" wflag:"<<wflag<<" fflag:"<<fflag<<" pflag:"<<pflag<<" nflag:"<<nflag<<endl;



    if(wflag==1)
    {
		if(nflag==0 && pflag==0)
		{
			wflag=0;
			cerr<<"Please try command again by adding string(-p) and number of times to repeat the string(-n)"<<endl;
		}
        //cout<<"File name:"<<fvalue<<" No of times:"<<nvalue<<" String:"<<pvalue<<endl;
        else
        {
			write(fvalue,nvalue,pvalue);
	    }
        //read(fvalue);
    }
    if(rflag==1)
    {
         //cout<<"File name:"<<fvalue<<endl;
            read(fvalue);
    }

}
