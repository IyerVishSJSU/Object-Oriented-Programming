#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include<vector>
using namespace std;
//----------------------------CLASS DEFINITION------------------------------------
class ShiftReg
{
public:
    vector <int> vec;
    int i,bit_count,x;
    int feedBit(char*s_ival,char*s_sval);
    int shiftLeft(char* s_lval,int s_vval);
    int shiftRight(char* s_rval,int s_vval);
    int display();
};
int ShiftReg::feedBit(char*s_ival,char*s_sval)
{
    bit_count=strlen(s_ival);
    //cout<<"The binary input is:"<<s_ival<<endl;
    x=atoi(s_sval)-bit_count;

    if(bit_count<=atoi(s_sval))
{
   for(i=0;i<x;i++)
        {
            vec.push_back(0);

        }
    for(i=x;i<atoi(s_sval);i++)
        {
            if(s_ival[(i-x)]>49)
            {
                cout<<"You can have only 1 and 0 in your shift register"<<endl;
                return -1;
            }
            else
            {
                 vec.push_back(s_ival[(i-x)]-'0'); //i=0;i<bit_count;i++
            }
        }
}
else
{
    for(i=0;i<atoi(s_sval);i++)
        {
            if(s_ival[i]>49)
            {
                cout<<"You can have only 1 and 0 in your shift register"<<endl;
                return -1;
            }
            else
            {
                 vec.push_back(s_ival[i]-'0'); //i=0;i<bit_count;i++
            }
        }
}

    /*cout<<"The input number in shift register is:"<<endl;
    for(i=0;i<vec.size();i++)
     {
         cout<<vec[i];
     }
     cout<<'\n';*/
return 0;
}

int ShiftReg::shiftLeft(char* s_lval, int s_vval)
{
    int v_size=vec.size();
    int shift_val=atoi(s_lval);

        /*if(shift_val>=v_size)
        {
            cout<<"\nThe shift value cannot be greater than the number of bits that is "<<v_size<<" bits"<<endl;
            return -1;
        }*/
    int sntl_val= v_size-shift_val;

        for(i=0;i<sntl_val;i++)
        {
            vec[i]=vec[i+shift_val];
        }
        if((s_vval-48)==1)
        {
            for(i=sntl_val;i<v_size;i++)
            {
                vec[i]=1;
            }
        }
        else
        {
          for(i=sntl_val;i<v_size;i++)
            {
                vec[i]=0;
            }
        }
    /*
    cout<<"\nThe binary bit after left shift is as follows:"<<endl;
        for(i=0;i<vec.size();i++)
         {
             cout<<vec[i];
         }*/
return 0;
}

int ShiftReg::shiftRight(char* s_rval,int s_vval)
{
    int v_size=vec.size();
    int shift_val=atoi(s_rval);
        /*if(shift_val>=v_size)
            {
                cout<<"\nThe shift value cannot be greater than the number of bits that is "<<v_size<<" bits"<<endl;
                return -1;
            }*/

     int sntl_val= v_size-shift_val;

        for(i=(v_size-1);i>=shift_val;i--)
        {
            vec[i]=vec[i-shift_val];
        }

        if((s_vval-48)==1)
        {
            for(i=0;i<shift_val;i++)
            {
                vec[i]=1;
            }
        }
        else
        {
            for(i=0;i<shift_val;i++)
            {
                vec[i]=0;
            }
        }
        /*cout<<"\nThe binary bit after right shift is as follows:"<<endl;
        for(i=0;i<vec.size();i++)
        {
            cout<<vec[i];
        }*/

return 0;
}

int ShiftReg::display()
{
    cout<<"The final number in shift register is:"<<endl;
    for(i=0;i<vec.size();i++)
     {
         cout<<vec[i];
     }
     return 0;
}
//---------------------MAIN FUNCTION BEGINS--------------------------------

int main (int argc, char *argv[])
{
    ShiftReg sr;

    int iflag = 0;
    int pflag = 0;
    int sflag = 0;
    int rflag = 0;
    int lflag = 0;
    int vflag = 0;

    char *ival=NULL,*sval=NULL,*rval=NULL,*lval=NULL,*vval=NULL;
    int c;

    char sim_opt[10];
    char *arg_opt[10];
    int sim_idx=0;
    int arg_idx=0;

    while ((c = getopt (argc, argv,"pi:s:r:l:v:"))!= -1)
        switch (c)
        {

        case 'i':
            iflag = 1;
            ival = optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"(-) symbol is not allowed in between binary bits. Please fill the binary number."<<endl;
                  return -1;
                }
            break;

        case 'p':
            pflag = 1;
            break;

        case 's':
            sflag = 1;
            sval = optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for size of shift register"<<endl;
                  return -1;
                }
            break;

        case 'r':
            rflag = 1;
            sim_opt[sim_idx++] = c;
            rval = optarg;
            arg_opt[arg_idx++]=optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for right shift value"<<endl;
                  return -1;
                }
            break;

        case 'l':
            lflag = 1;
            sim_opt[sim_idx++] = c;
            lval = optarg;
            arg_opt[arg_idx++]=optarg;
          if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for left shift value"<<endl;
                  return -1;
                }
            break;

        case 'v':
            vflag = 1;
            vval = optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for vacant bits"<<endl;
                  return -1;
                }
            if(*optarg!='0'&& *optarg!='1')
            {
                //cout<<" The value of vval is:"<<*optarg<<endl;
                cerr<<"Only binary digits 1 and 0 allowed!!"<<endl;
                return -1;
            }
            break;

        case '?':
            if (optopt=='i')
                {
                    cerr<<"Please specify binary bit to enter"<<endl;
                }
            else if (optopt =='s')
                {
                    cerr<<"Please specify number of bits in your register"<<endl;
                }
            else if (optopt =='r'||optopt =='l')
                {
                    cerr<<"Please specify number of bits to shift"<<endl;
                }
            else if (optopt =='v')
                {
                    cerr<<"Please specify vacant bits as v option is left blank."<<endl;
                }
            else
                {
                    cerr<<"Unknown Option"<<endl;
                    //break;
                }
        return -1;
        default:
            cerr<<"getopt"<<endl;
        }
//--------------------------------FUNCTION CALL BEGINS HERE---------------------------------------

// cout<<"iflag:"<<iflag<<" sflag:"<<sflag<<" rflag:"<<rflag<<" lflag:"<<lflag<<" vflag:"<<vflag<<" pflag:"<<pflag<<endl;
int n;
/*FUNCTION CALL FOR FEEDING BITS INTO SHIFT REGISTER*/

if(iflag!=1&&sflag!=1)
    {
       n=sr.feedBit("00000","5");
    }
    else
    {
        if(iflag!=1)
        {
            n=sr.feedBit("00000",sval);
        }
        else if(sflag!=1)
        {
            cout<<"Please fill the size of the shift register. Usage ./shiftregister.cpp -i0000 -s4"<<endl;
            return -1;
        }
        else
        {
            n=sr.feedBit(ival,sval);
        }

        if(n!=0)
            return -1;
    }
/*FUNCTION CALL IF ONLY ONE OF THE OPERATION IS ASKED -- RIGHT OR LEFT*/
if((rflag==1&&lflag==0)||(lflag==1&&rflag==0))
{
     if(lflag==1)
    {
        if(vflag==1)
        {
            n=sr.shiftLeft(lval,*vval);
        }
        else
        {
            n=sr.shiftLeft(lval,0);
        }
        if(n!=0)
           return -1;

    }
    if(rflag==1)
    {
       if(vflag==1)
        {
            n=sr.shiftRight(rval,*vval);
        }
        else
        {
            n=sr.shiftRight(rval,0);
        }

        if(n!=0)
            return -1;
    }
}

/*FUNCTION CALL IF BOTH RIGHT AND LEFT OPERATION ARE CALLED*/
if(rflag==1&&lflag==1)
{

    int m;
    for(m=0;m<sim_idx;m++)
    {
        switch(sim_opt[m])
        {
        case 'r':
            {
                if(vflag==1)
                {
                    n=sr.shiftRight(arg_opt[m],*vval);
                }
                else
                {
                    n=sr.shiftRight(arg_opt[m],0);
                }

                if(n!=0)
                    return -1;
            }
            break;
        case 'l':
            {
                if(vflag==1)
                {
                    n=sr.shiftLeft(arg_opt[m],*vval);
                }
                else
                {
                    n=sr.shiftLeft(arg_opt[m],0);
                }

                if(n!=0)
                    return -1;
            }
            break;
        }
    }
    //return 0;
}
/*FUNCTION CALL TO DISPLAY OUTPUT*/
if(pflag==1)
{
    n= sr.display();
}
return n;
}

