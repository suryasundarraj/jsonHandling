#include <stdio.h>
#include <stdlib.h>


#define MAX_PRECISION   (13)
#if (0)
static const double rounders[MAX_PRECISION + 1] =
{
    0.5,                // 0
    0.05,               // 1
    0.005,              // 2
    0.0005,             // 3
    0.00005,            // 4
    0.000005,           // 5
    0.0000005,          // 6
    0.00000005,         // 7
    0.000000005,        // 8
    0.0000000005,       // 9
    0.00000000005,      // 10
    0.000000000005,     //11
    0.0000000000005,    //12
    0.00000000000005    //13
    
};
#endif

char * ftoa(double f, char * buf, int precision)
{
    char * ptr = buf;
    char * p = ptr;
    char * p1;
    char c;
    long intPart;
    char* temp_str;

    // check precision bounds
    if (precision > MAX_PRECISION)
        precision = MAX_PRECISION;

    // sign stuff
    if (f < 0)
    {
        f = -f;
        *ptr++ = '-';
    }

    if (precision < 0)  // negative precision == automatic precision guess
    {
        if (f < (double)1.0) precision = 6;
        else if (f < (double)10.0) precision = 5;
        else if (f < (double)100.0) precision = 4;
        else if (f < (double)1000.0) precision = 3;
        else if (f < (double)10000.0) precision = 2;
        else if (f < (double)100000.0) precision = 1;
        else precision = 0;
    }

    // round value according the precision
    //if (precision)
    //    f += rounders[precision];

    // integer part...
    intPart = f;
    f -= intPart;

    if (!intPart)
        *ptr++ = '0';
    else
    {
        // save start pointer
        p = ptr;

        // convert (reverse order)
        while (intPart)
        {
            *p++ = '0' + intPart % 10;
            intPart /= 10;
        }

        // save end pos
        p1 = p;

        // reverse result
        while (p > ptr)
        {
            c = *--p;
            *p = *ptr;
            *ptr++ = c;
        }

        // restore end pos
        ptr = p1;
    }

    // decimal part
    if (precision)
    {
        // place decimal point
        *ptr++ = '.';

        // convert
        while (precision--)
        {
            f *= (double)10.0;
            c = f;
            *ptr++ = '0' + c;
            f -= c;
        }
    }

    // terminating zero
    *ptr = 0;

    temp_str = --ptr;
    while(*temp_str != '.')
    { 
        if(*temp_str == '0')
        {
            *temp_str = '\0';
        }
        else
        {
            break;
        }
        temp_str--;
    }   

    if((*(temp_str+1) == '\0') && (*temp_str == '.'))
    {
        *(temp_str+1) = '0';
    }

    return buf;
}


