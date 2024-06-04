#ifndef THREAD_H
#define THREAD_H

#include <iostream>
#include <pthread.h>
#include <cassert>
#include <error.h>
#include "print.h"

using namespace std;

class Thread
{
public:
    Thread()
    {

    }

    ~Thread()
    {

    }
    
    void Start()
    {
        if (pthread_create(&m_tid, nullptr, Runner, this) == 0) {}
    }

    void Start(std::string xArg)
    {
        threadName = xArg;
        if (pthread_create(&m_tid, nullptr, Runner, this) == 0) {}
    }

    void Join()
    {
        printTrace("Thread %s ID: 0x%llx is join", threadName.c_str(), m_tid)
        pthread_join(m_tid, nullptr);
    }

    void Exit()
    {
        Join();
    }

    void SetCancelable()
    {
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }

    void ResetCancelable()
    {
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    }

    uint64_t GetThreadIdCalling()
    {
        return pthread_self();
    }

    uint64_t GetThreadId()
    {
        return m_tid;
    }

    std::string GetThreadName() { return threadName; }

    virtual void DoSomething() {}

private:
    pthread_t m_tid;
    std::string threadName;

    static void* Runner(void* arg)
    {
        Thread* mt = reinterpret_cast<Thread*>(arg);
        std::stringstream stream;
        stream << std::hex << pthread_self();
        printTrace("Thread %s ID: 0x%llx is running", mt->threadName.c_str(), mt->m_tid);
        mt->DoSomething();
        printTrace("Thread %s ID: 0x%llx is finished", mt->threadName.c_str(), mt->m_tid);
        pthread_exit(NULL);
    }

};

class ThreadLoop : public Thread
{
public:
    ThreadLoop() {}
    ~ThreadLoop() {}

    virtual void BeforeLoop() {}
    virtual void AfterLoop() {}
    virtual void Loop() {}
    void Stop()
    {
        state = false;
        pthread_cancel(GetThreadId());
    }

    void DoSomething() final 
    {
        BeforeLoop();
        while (state) 
        {
            Loop();
        }
        AfterLoop();
    }

private:
    bool state = true;
};

#endif

