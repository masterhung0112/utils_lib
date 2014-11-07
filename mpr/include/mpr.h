#ifndef __MPR_H__
#define __MPR_H__

#include "platform_config.h"

#if PLATFORM_LINUX
#include "pthread.h"
#elif PLATFORM_WIN32
#include <Windows.h>
#endif

#if PLATFORM_LINUX
    typedef pthread_t   MprOsThread;
#elif PLATFORM_WIN32
	typedef int			MprOsThread;
#else
    #warning "Unsupported OS in MprThread definition in mpr.h"
#endif

typedef struct MprMutex {
#if PLATFORM_LINUX
    pthread_mutex_t cs;
#elif PLATFORM_WIN32
	CRITICAL_SECTION cs;
#else
    #warning "Unsupported OS in MprMutex definition in mpr.h"
#endif
    MprOsThread owner;
} MprMutex;

/*
 * Create a Mutex lock object.
 * @description This call creates a Mutex lock object that can be used in #mprLock, #mprTryLock, #mprUnlock calls.
 * @ingroup MprSynch
 */
PUBLIC MprMutex *mprCreateLock();

/*
 * Initialize a statically allocated Mutex lock object.
 * @description This call initializes a Mutex lock object without allocation.
 *              This object can then be used in #mprLock, #mprTryLock, and #mprUnlock calls.
 * @param mutex Reference to an MprMutex structure to initialize
 * @returns A reference to the supplied mutex. Returns null on errors.
 * @ingroup MprSynch
 */
PUBLIC MprMutex *mprInitLock(MprMutex *mutex);

/*
 * Lock access
 * @description This call asserts a lock on the given \a lock mutex so that other threads calling mprLock
 *              will block until the current thread calls mprUnlock.
 * @ingroup MprSynch
 */
PUBLIC void mprLock(MprMutex *lock);

/*
 * Unlock a mutex
 */
PUBLIC void mprUnlock(MprMutex *lock);

/**
 * Get the OS Thread
 * @description Get the OS thread ID for the currently executing thread.
 * @return Returns a platform specific OS thread ID.
 * @ingroup MprThread
 */
PUBLIC MprOsThread mprGetCurrentOsThread(void);

#endif // __MPR_H__