#include "stdlib.h"

int abs(int n)
{
    if(n < 0)
    {
        n *= -1;
    }

    return n;
}