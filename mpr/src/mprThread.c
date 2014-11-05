#include "mpr.h"

PUBLIC MprOsThread mprGetCurrentOsThread(void)
{   
#if PLATFORM_LINUX
    return (MprOsThread) pthread_self();
#endif
}