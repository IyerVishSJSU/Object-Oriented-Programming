#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include<vector>
#include<math.h>
using namespace std;
//----------------------------CLASS DEFINITION------------------------------------
ostream& operator<< (ostream &out, vector<bool> &vect)
{

    for(unsigned int i=0; i< vect.size();i++)
    {
        out<<vect[i];
    }

    return out;
}

class ShiftReg
{
public:
    vector <bool> vec;
    vector <bool> result;
    vector<bool> num_one;
    vector<bool> subt;
    bool c=0;
    int i,bit_count,x;
    int feedBit(char* s_ival,char* s_sval);
    int feedDecimal(char* s_ival,char* s_sval);
    int shiftLeft(char* s_lval,int s_vval);
    int shiftRight(char* s_rval,int s_vval);
    int shift_add(vector <bool> reg2);
    int display(int pval,int dval,int hval);
    int res_display(int pval,int dval,int hval);
    int two_comp();
    void conv_bintodec(int n2);
    void conv_bintohex(int n2);
private:
    int n1=0,r=0;
};
int ShiftReg::two_comp()
{
    subt=vec;
    subt.flip();
    bool x=0,sum=0;
    int t=0;
    num_one.insert(num_one.begin(),vec.size()-1,0);
    num_one.push_back(1);

    for(t=(subt.size()-1);t>=0;t--)
        {
            sum=subt[t]^num_one[t]^x;
            x= (subt[t]&num_one[t])|(num_one[t]&x)|(subt[t]&x);
            subt[t]=sum;
        }
    return 0;
}
int ShiftReg::feedDecimal(char*s_ival,char*s_sval)
{
    string bin_val;
    char *final_val=new char[15];
    char holder=' ';
    int reg_size=atoi(s_sval);

    if(strncmp(s_ival,"-",1)==0)
    {
       char *last;
       s_ival++;
       int num=atoi(s_ival);
       //itoa(num,hex_num,16);
        while(num!=0)
        {
            holder=num%2+'0';
            bin_val=holder+bin_val;
            num=num/2;
        }
        copy(bin_val.begin(),bin_val.end(),final_val);
        final_val[bin_val.size()]='\0';
        last=strrchr(final_val,'1');
        //cout<<last-final_val+1<<endl;
        for(int i=0;i<(last-final_val);i++)
        {
            if(final_val[i]=='0')
            {
                final_val[i]='1';
            }
            else
            {
                final_val[i]='0';
            }
        }
        char *send_val=new char[reg_size+1];
        if(reg_size>bin_val.size())
        {
            int m=0;
            for(m=0;m<(reg_size-bin_val.size());m++)
            {
                send_val[m]='1';
            }
            for(m=(reg_size-bin_val.size());m<reg_size;m++)
            {
                send_val[m]=final_val[m-(reg_size-bin_val.size())];
            }
        }
        else
        {
          send_val=final_val;
        }
                     feedBit(send_val,s_sval);
        delete[] send_val;
        delete[]final_val;
    }
    else
    {
        int num= atoi(s_ival);
        //itoa(num,hex_num,16);

        while(num!=0)
        {
            holder=num%2+'0';
            bin_val=holder+bin_val;
            num=num/2;
        }
            copy(bin_val.begin(),bin_val.end(),final_val);
            final_val[bin_val.size()]='\0';
            feedBit(final_val,s_sval);
            delete[]final_val;
    }
    return 0;
}

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
                cout<<"Please put D at the end to use decimal value.The usage is ./shiftregister -i1234D -s4"<<endl;
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
                cout<<"Please put D at the end to use decimal value.The usage is ./shiftregister -i1234D -s4"<<endl;
                return -1;
            }
            else
            {
                 vec.push_back(s_ival[i]-'0'); //i=0;i<bit_count;i++
            }
        }
}
return 0;
}

int ShiftReg::shiftLeft(char* s_lval, int s_vval)
{
    int v_size=vec.size();
    int shift_val=atoi(s_lval);

    int sntl_val= v_size-shift_val;

        for(i=0;i<sntl_val;i++)
        {
            vec[i]=vec[i+shift_val];
        }
        if(s_vval==1)
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
return 0;
}

int ShiftReg::shiftRight(char* s_rval,int s_vval)
{
    int v_size=vec.size();
    int shift_val=atoi(s_rval);

     int sntl_val= v_size-shift_val;

        for(i=(v_size-1);i>=shift_val;i--)
        {
            vec[i]=vec[i-shift_val];
        }

        if(s_vval==1)
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
return 0;
}

int ShiftReg::shift_add(vector<bool> reg2)
{
    bool sum=0;
    int m=0;
    if(vec.size()>=reg2.size())
    {
        reg2.insert(reg2.begin(),vec.size()-reg2.size(),0);
        for(m=(vec.size()-1);m>=0;m--)
        {
            sum=vec[m]^reg2[m]^c;
            c= (vec[m]&reg2[m])|(reg2[m]&c)|(vec[m]&c);
            result.insert(result.begin(),sum);
        }
    }
    else if(reg2.size()>vec.size())
    {
      vec.insert(vec.begin(),reg2.size()-vec.size(),0);
      for(m=(reg2.size()-1);m>=0;m--)
        {
            sum=vec[m]^reg2[m]^c;
            c= (vec[m]&reg2[m])|(reg2[m]&c)|(vec[m]&c);
            result.insert(result.begin(),sum);
        }
    }
        return 0;
}
void ShiftReg::conv_bintodec(int n2)
{
    if(n2==1)
    {
       for(i=vec.size()-1;i>=0;i--)
        {
            n1=vec[i]* pow(2,((vec.size()-1)-i))+n1;
        }
    }
    else if(n2==2)
    {
       for(i=result.size()-1;i>=0;i--)
        {
            r=result[i]* pow(2,((result.size()-1)-i))+r;
        }
    }

}

int ShiftReg::display(int pval,int dval,int hval)
{
    if(pval==1&&dval==0&&hval==0)
    {
        cout<<vec;
     cout<<'\n';
    }
    else if(pval==1&&dval==1&&hval==0)
    {
        conv_bintodec(1);
        cout<<vec;
         cout<<"("<<n1<<")";
         cout<<'\n';
    }
    else if(pval==1&&dval==0&&hval==1)
    {
       char hex_num[5];
        conv_bintodec(1);
        sprintf(hex_num,"%x",n1);
        cout<<vec;
         cout<<"(0x"<<hex_num<<")";
         cout<<'\n';
    }
    else if(pval==1&&dval==1&&hval==1)
    {
        conv_bintodec(1);
        char hex_num[5];
        sprintf(hex_num,"%x",n1);
        cout<<vec;
        cout<<"("<<n1<<")";
        cout<<"(0x"<<hex_num<<")";
        cout<<'\n';
    }
    return 0;
}
int ShiftReg::res_display(int pval,int dval,int hval)
{
    if(pval==1&&dval==0&&hval==0)
    {
    cout<<result<<"("<<c<<")";
    cout<<'\n';
    }
    else if(pval==1&&dval==1&&hval==0)
    {
        conv_bintodec(2);
        cout<<result<<"("<<c<<")";
         cout<<"("<<r<<")";
         cout<<'\n';
    }
    else if(pval==1&&dval==0&&hval==1)
    {
        char hex_num[5];
        conv_bintodec(2);
        sprintf(hex_num,"%x",r);
        cout<<result<<"("<<c<<")";
         cout<<"(0x"<<hex_num<<")";
         cout<<'\n';
    }
    else if(pval==1&&dval==1&&hval==1)
    {
        conv_bintodec(2);
        char hex_num[5];
        sprintf(hex_num,"%x",r);
        cout<<result<<"("<<c<<")";
        cout<<"("<<r<<")";
        cout<<"(0x"<<hex_num<<")";
        cout<<'\n';
    }
    return 0;
}
//---------------------MAIN FUNCTION BEGINS--------------------------------

int main (int argc, char *argv[])
{
    ShiftReg sr,sr1;

    int iflag = 0,sflag = 0,rflag = 0,lflag = 0,vflag = 0,oflag=0;
    int iflag1=0,sflag1=0,rflag1=0,lflag1=0;
    int pflag = 0,dflag=0,hflag=0,vval=0;

    char *ival=NULL,*sval=NULL,*rval=NULL,*lval=NULL;
    char *ival1=NULL,*sval1=NULL,*rval1=NULL,*lval1=NULL,*oval=NULL;

    int c;

    char sim_opt[10];
    char *arg_opt[10];
    int sim_idx=0;
    int arg_idx=0;
    while ((c = getopt (argc, argv,"pdhi:s:r:l:I:S:R:L:v:o:"))!= -1)
        switch (c)
        {
//---------------------------------------------------
        case 'i':
            iflag = 1;
            ival = optarg;
            break;
        case 'I':
            iflag1 = 1;
            ival1 = optarg;
            break;
//-----------------------------------------------------
        case 'p':
            pflag = 1;
            break;
        case 'd':
            dflag = 1;
            break;
        case 'h':
            hflag = 1;
            break;
//-----------------------------------------------------
        case 's':
            sflag = 1;
            sval = optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for size of shift register"<<endl;
                  return -1;
                }
            break;
        case 'S':
            sflag1 = 1;
            sval1 = optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for size of shift register"<<endl;
                  return -1;
                }
            break;
//----------------------------------------------------
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
        case 'R':
            rflag1 = 1;
            sim_opt[sim_idx++] = c;
            rval1 = optarg;
            arg_opt[arg_idx++]=optarg;
            if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for right shift value"<<endl;
                  return -1;
                }
            break;
//---------------------------------------------
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
        case 'L':
            lflag1 = 1;
            sim_opt[sim_idx++] = c;
            lval1 = optarg;
            arg_opt[arg_idx++]=optarg;
          if (optarg[0]=='-')
                {
                  cerr<<"You have either entered negative number or forgot to put values for left shift value"<<endl;
                  return -1;
                }
            break;
//------------------------------------------------
        case 'v':
            vflag = 1;
            vval = atoi(optarg);

            break;
//------------------------------------------------------
        case 'o':
           oflag=1;
           oval=optarg;
           if(*optarg!='+'&& *optarg!='-')
            {
                //cout<<" The value of vval is:"<<*optarg<<endl;
                cerr<<"Only + and - are allowed!!"<<endl;
                return -1;
            }
           break;
//-------------------------------------------------------
        case '?':
            if (optopt=='i'||optopt=='I')
                {
                    cerr<<"Please specify binary bit to enter"<<endl;
                }
            else if (optopt =='s'||optopt=='S')
                {
                    cerr<<"Please specify number of bits in your register"<<endl;
                }
            else if (optopt =='r'||optopt =='l'||optopt=='R'||optopt=='L')
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
            cout<<"Please fill the size of the shift register 1. Usage ./shiftregister.cpp -i0000 -s4"<<endl;
            return -1;
        }
        else
        {
            char* found = strchr(ival,'D');
            if(found!=NULL)
            {
                n=sr.feedDecimal(ival,sval);
            }
            else
                {
                            n=sr.feedBit(ival,sval);
                }
        }

        if(n!=0)
            return -1;
    }

if(iflag1!=1&&sflag1!=1)
    {
       n=sr1.feedBit("00000","5");
    }
    else
    {
        if(iflag1!=1)
        {
            n=sr1.feedBit("00000",sval1);
        }
        else if(sflag1!=1)
        {
            cout<<"Please fill the size of the shift register 2. Usage ./shiftregister.cpp -I0000 -S4"<<endl;
            return -1;
        }
        else
        {
            char* found = strchr(ival1,'D');
            if(found!=NULL)
            {
                n=sr1.feedDecimal(ival1,sval1);
            }
            else
                {
                            n=sr1.feedBit(ival1,sval1);
                }
        }

        if(n!=0)
            return -1;
    }

/*FUNCTION CALL IF ONLY ONE OF THE OPERATION IS ASKED -- RIGHT OR LEFT*/
if((rflag==1&&lflag==0)||(lflag==1&&rflag==0)||(rflag1==1&&lflag1==0)||(lflag1==1&&rflag1==0))
{
     if(lflag==1)
    {
        if(vflag==1)
        {
            n=sr.shiftLeft(lval,vval);
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
            n=sr.shiftRight(rval,vval);
        }
        else
        {
            n=sr.shiftRight(rval,0);
        }

        if(n!=0)
            return -1;
    }

    if(rflag1==1)
    {
       if(vflag==1)
        {
            n=sr1.shiftRight(rval1,vval);
        }
        else
        {
            n=sr1.shiftRight(rval1,0);
        }

        if(n!=0)
            return -1;
    }

         if(lflag1==1)
    {
        if(vflag==1)
        {
            n=sr1.shiftLeft(lval1,vval);
        }
        else
        {
            n=sr1.shiftLeft(lval1,0);
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
                    n=sr.shiftRight(arg_opt[m],vval);
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
                    n=sr.shiftLeft(arg_opt[m],vval);
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

if(rflag1==1&&lflag1==1)
{

    int m;
    for(m=0;m<sim_idx;m++)
    {
        switch(sim_opt[m])
        {
        case 'R':
            {
                if(vflag==1)
                {
                    n=sr1.shiftRight(arg_opt[m],vval);
                }
                else
                {
                    n=sr1.shiftRight(arg_opt[m],0);
                }

                if(n!=0)
                    return -1;
            }
            break;
        case 'L':
            {
                if(vflag==1)
                {
                    n=sr1.shiftLeft(arg_opt[m],vval);
                }
                else
                {
                    n=sr1.shiftLeft(arg_opt[m],0);
                }

                if(n!=0)
                    return -1;
            }
            break;
        }
    }
    //return 0;
}
/*FUNCTION CALL FOR ADDITION-SUBTRACTION*/
if(oflag==1)
{
    switch(*oval)
    {
    case '+':
        n=sr.shift_add(sr1.vec);
        break;
    case '-':
        sr1.two_comp();
        n=sr.shift_add(sr1.subt);
        break;
    }
    if(n!=0)
        return -1;
}
/*FUNCTION CALL TO DISPLAY OUTPUT*/
if(pflag==1)
{
        sr.display(pflag,dflag,hflag);
        sr1.display(pflag,dflag,hflag);
        sr.res_display(pflag,dflag,hflag);
        return 0;
}
if(pflag==0&&(dflag==1||hflag==1))
{
    cout<<"Please put -p to display the values. Usage: ./shiftregister -p -i5D -s4 -d"<<endl;
    return -1;
}
return n;
}
