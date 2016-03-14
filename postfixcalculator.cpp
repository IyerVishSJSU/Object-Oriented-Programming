#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <stack>
using namespace std;

class postfixCalc
{
public:
    int CalculatePostfix(string str);
    int PerformOperation(char operation, int operand1, int operand2);
    bool chkOperator(char C);
    bool chkNumber(char C);
    int chkflag();
    int flag;

    postfixCalc()
    {
		flag=0;
	}

};
int postfixCalc::CalculatePostfix(string str)
{
    stack<int> S;
    unsigned int i=0;
    int operand2=0,operand1=0;
    for(i = 0;i< str.length();i++)
    {
       if(str[i] == ' ' || str[i] == ',')
            continue;

        else if(chkOperator(str[i])) {
			// Pop two operands.
			if(!S.empty())
			{
				operand2 = S.top(); S.pop();
			}
			else
			{
				cerr<<"No numbers in stack"<<endl;
				flag=-1;
				return EXIT_FAILURE;
			}

			if(!S.empty())
			{
				operand1 = S.top(); S.pop();
			}
			else
			{
				cerr<<"There are less numbers for operation"<<endl;
				flag=-1;
				return EXIT_FAILURE;
			}

			// Perform operation
			//cout<<"Op1:"<<operand1<<" Op2:"<<operand2<<endl;
			int result = PerformOperation(str[i], operand1, operand2);
			//Push back result of operation on stack.
			//cout<<"Result:"<<result<<endl;
			S.push(result);
		}
		else if(chkNumber(str[i])){
			int operand = 0;
			while(i<str.length() && chkNumber(str[i])) {

				operand = (operand*10) + (str[i] - '0');
				i++;
			}

			i--;
			// Push operand on stack.
			S.push(operand);
		}
    }
    return S.top();
}
int postfixCalc::PerformOperation(char operation, int operand1, int operand2)
{
    if(operation == '+') return operand1 +operand2;
	else if(operation == '-') return operand1 - operand2;
	else if(operation == '*') return operand1 * operand2;
	else if(operation == '/') return operand1 / operand2;

	else cout<<"Unexpected Error \n";
	return -1;
}
bool postfixCalc::chkOperator(char C)
{
    if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}
bool postfixCalc::chkNumber(char C)
{
    if(C >= '0' && C <= '9') return true;
	return false;
}
int postfixCalc::chkflag()
{
	return flag;
}

int main (int argc, char *argv[])
{
    //int eflag = 0;

    char *ex_value = NULL;

    int c;

    while ((c = getopt (argc, argv,"e:"))!= -1)
        switch (c)
        {

        case 'e':
            //eflag = 1;
            ex_value = optarg;
            break;

        case '?':
            if (optopt=='e')
                {
                    cerr<<"Please specify expression for postfix calculator. Usage: -e 2,3,+,4,*"<<endl;
                //    break;
                }
            else
                {
                    cerr<<"Unknown Option"<<endl;
                    break;
                }
            return 1;
        default:
            cerr<<"getopt"<<endl;
        }
 //cout<<"The expression entered is: "<<ex_value<<endl;
postfixCalc p;
int res=0,f=0;

res=p.CalculatePostfix(ex_value);
f=p.chkflag();
if(f<0)
{
	return -1;
}
cout<<res<<endl;
}
