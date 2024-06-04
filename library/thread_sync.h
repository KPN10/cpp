#ifndef THREAD_SYNC_H
#define THREAD_SYNC_H

#include <pthread.h>

class Mutex
{
public:
    Mutex()
    {
        pthread_mutexattr_init(&mta);
        pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&mutex, &mta);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&mutex);
    }

    void Acquire()
    {
        pthread_mutex_lock(&mutex);
    }

    void Release()
    {
        pthread_mutex_unlock(&mutex);
    }

private:
    pthread_mutex_t mutex;
    pthread_mutexattr_t mta;
};

// struct Mutex
// {
// public:
//     Mutex(pthread_mutex_t &lock) : mutex(lock){}

//     void Acquire()
//     {
//         pthread_mutex_lock(&mutex);
//     }

//     void Release()
//     {
//         pthread_mutex_unlock(&mutex);
//     }

// private:
//     pthread_mutex_t mutex;
// };

// class LockGuard
// {
//     // LockGuard(Mutex& mutex) : _ref(mutex)
//     // {
//     //     _ref.Acquire();
//     // }
// };


#endif

