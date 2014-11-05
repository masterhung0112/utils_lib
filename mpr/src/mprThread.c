#include "mpr.h"

PUBLIC MprOsThread mprGetCurrentOsThread(void)
{   
#if PLATFORM_UNIX
    return (MprOsThread) pthread_self();
#endif
}