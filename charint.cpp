#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "charint.h"

CharInt::CharInt(char* c)
   // :text(c)
{
    integ=to_int(c);
    dfloat=to_float(c);
}

long int CharInt::to_int(char*c)
{
    int tmp=0;
    long int d=0;
    for (int i=0;i<60;i++)
    {
        if (c[i]<='\0') break; 
        tmp = (int)c[i]-48;
        if (tmp>9 || tmp<0)
        {
 //           std::cerr<<"\nstop  : "<<tmp<<"\n    error data not numeric\n";
            break;
        }
        d=d*10+tmp;
//        std::cout<<"\n"<<c<<"i="<<i<<": "<<c[i]<<"- "<<(int)c[i]-48<<'>'<<d;
    }
    return d;
}

double CharInt::to_float(char*c)
{
    int tmp=0;
    int t=0;
    double d=0;
    for (int i=0;i<60;i++)
    {
        if (c[i]<='\0') break; 
        tmp = (int)c[i]-48;
        if (tmp==-2)
        {
            t=1;
            continue;
        }
        if (tmp>9 || tmp<0)
        {
           // std::cerr<<"\nstop  : "<<tmp<<"\n    error data not numeric\n";
            break;
        }
        d=d*10+tmp;
        t*=10;
    //    std::cout<<"\n"<<c<<"i="<<i<<": "<<c[i]<<"- "<<(int)c[i]-48<<"d="<<d<<" t="<<t;
    }
    if(t==0) t=1;
    return d/t;
}
CharInt::~CharInt()
{
}

