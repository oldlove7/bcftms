//---------------------------------------------------------------------------
// zManager.h
// Author       : Park Dong Ro
// LastModify   : 2002.6
// Comment      :
//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
#ifndef zManagerH
#define zManagerH
//----------------------------------------------------------------------------
#include "zThread.h"

class zWorker : public zThread
{
private:

protected:
	virtual void run(){};
	
public:
	zWorker();
	virtual void stop(){};
};

class zManager
{
private:

protected:
public:
	zManager();
    virtual void endWorker(zWorker* worker){};
};

#endif

