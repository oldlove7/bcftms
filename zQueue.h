//---------------------------------------------------------------------------
// zQueue.h
// Author       : Park Dong Ro
// LastModify   : 2004.2
// Comment      :
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef zQueueH
#define zQueueH
//---------------------------------------------------------------------------

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "zLock.h"

//----------------------------------------------------------------------------
class Queue 
{
	
private:
	int Q_SIZE;
	int Q_ELEMENT_SIZE;
	
	zLock *lock;
	pthread_t lockOwner;
	
	int head;
	int tail;
	int elements;
	char *q;
	bool isGlobalLock();
	
public:
	Queue(int qSize, int typeSize);
	void globalLock();
	void globalUnLock();

	void clear();
	int size();
	bool isEmpty();
					   
	void push( const void* e );		   
    bool popFirst(void* e);
    bool popLast(void* e);
    bool get( int idx, void* e);
    void* get( int idx );
    int remove(int idx);
};

//----------------------------------------------------------------------------
template<class type> class zQueue : public Queue
{

private:

public:
	
    zQueue( int size ) : Queue( size, sizeof(type)) {}
	void globalLock(){ Queue::globalLock(); }
	void globalUnLock(){ Queue::globalUnLock(); }

	void clear(){ Queue::clear(); }
	int size(){ return Queue::size(); }
	bool isEmpty(){ return Queue::isEmpty(); }
					   
	void push( const type *e ){ Queue::push((void *)e); }	   
    bool popFirst( type * e){ return Queue::popFirst((void *)e); }
    bool popLast( type * e){ return Queue::popLast((void *)e); }
    bool get( int idx, type * e){ return Queue::get(idx, (void *)e); }
    type * get( int idx ){ return (type *) Queue::get(idx); }
    int remove(int idx){ return Queue::remove(idx); }
					
};

//----------------------------------------------------------------------------
#endif

