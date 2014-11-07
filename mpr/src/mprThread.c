#include "mpr.h"

PUBLIC MprOsThread mprGetCurrentOsThread(void)
{   
#if PLATFORM_LINUX
    return (MprOsThread) pthread_self();
#elif PLATFORM_WIN32
	return (MprOsThread) GetCurrentThreadId();
#endif
}