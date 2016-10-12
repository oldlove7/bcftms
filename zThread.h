
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class zThread
{
	
protected:
    pthread_t  handle;
    bool autofree;
    bool running;
    int  signaled;

    friend void _threadepilog(zThread* thr);
    friend void* _threadproc(void* arg);
    virtual void run(){};

public:

    zThread(bool iautofree);
    virtual ~zThread();
   
    void start();
    virtual void stop();
    
    pthread_t get_id();

    void waitfor();
};

#endif // __THREAD_H__
