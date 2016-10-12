//---------------------------------------------------------------------------
// rwLock.h
// Author       : Park Dong Ro
// LastModify   : 2004.1
// Comment      :
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef RwLockH
#define RwLockH
//----------------------------------------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------
class zLock
{
private:	
	pthread_mutex_t *mut;
	char name[20];
	
public:
	int writers;
	int readers;
	int waiting;
	pthread_cond_t *writeOK, *readOK;
	
	zLock(char* lockname);
    zLock();
    pthread_t getOwner();
    
    void lock();
    void unlock();
    
    /*
    void readLock();
    void writeLock();
    void readUnlock();
    void writeUnlock();
    */
    void deleteLock();
};

#endif


