#include "mpr.h"

#if 0
PUBLIC MprMutex *mprCreateLock()
{
    MprMutex *lock = NULL;
#if PLATFORM_UNIX
    pthread_mutexattr_t attr;
    if (unlikely(pthread_mutexattr_init(&attr)))
        abort();
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
    if (unlikely(pthread_mutex_init(&lock->cs, &attr)))
        abort();
    pthread_mutexattr_destroy(&attr);
#endif
    return lock;
}
#endif

PUBLIC MprMutex *mprInitLock(MprMutex *lock)
{
#if PLATFORM_UNIX
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
    pthread_mutex_init(&lock->cs, &attr);
    pthread_mutexattr_destroy(&attr);
#endif
    return lock;
}

PUBLIC void mprLock(MprMutex *lock)
{
    if (lock == NULL)
        return;
#if PLATFORM_UNIX
    pthread_mutex_lock(&lock->cs);
#endif
    lock->owner = mprGetCurrentOsThread();
}

PUBLIC int mprTryLock(MprMutex *lock)
{
    int rc;
    if (lock == NULL)
        return 0;
    
#if PLATFORM_UNIX
    rc = (pthread_mutex_trylock(&lock->cs) != 0);
#endif
    
    lock->owner = mprGetCurrentOsThread();
    
    return (rc) ? 0 : 1;
}

PUBLIC void mprUnlock(MprMutex *lock)
{
    if (lock == NULL)
        return;
#if PLATFORM_UNIX
    pthread_mutex_unlock(&lock->cs);
#endif
}