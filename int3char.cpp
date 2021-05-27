#include "int3char.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

IntChar::IntChar(int in)
{
   integ=in;
    char c;
    int ost=integ;
    int tmp,j=0;

    for(int i=0;ost>0;i++)
    {
        tmp=(ost%10+48);
        c=(char)tmp;
        txt[i]=c;
        ost/=10;
        j++;
        //std::cout << tmp << txt[i] << ost<< "\n";
    }
    int jj=0;
    for(j;j>0;j--)
    {
        text[jj]=txt[j-1];
        //std::cout << jj <<"-jj "<<j<<"-j "<<text[jj]<<"\n";
        jj++;
    }
    text[jj]='\0';
}

IntChar::~IntChar()
{
}
