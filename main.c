#include "mpr.h"
#include <stdio.h>

int main(void)
{
    MprOsThread t = mprGetCurrentOsThread();
    printf("%08x\n", t);
    return 0;
}