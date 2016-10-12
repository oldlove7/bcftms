//---------------------------------------------------------------------------
// zByte.h
// Author       : Park Dong Ro
// LastModify   : 2003.11
// Comment      :
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef ByteH
#define ByteH
//---------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#ifndef __WIN32__
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#endif
/*
//----------------------------------------------------------------------------
class Byte
{
	
private:
public:
    Byte();
*/    
	short int getInt2( unsigned char* b, int off);
	void setInt2( unsigned char* b, int off, short int v);
	unsigned short int getUInt2( unsigned char* b, int off);
	void setUInt2( unsigned char* b, int off, unsigned short int v);
	unsigned int getUInt4( unsigned char* b, int off);
	void setUInt4( unsigned char* b, int off, unsigned int v);
	
	float getFloat( unsigned char* b, int off);
	void setFloat( unsigned char* b, int off, float v);
	double getDouble( unsigned char* b, int off);
	void setDouble( unsigned char* b, int off, double v);
	
	#ifdef TARGET_ARM
	double ENDIAN_SWAP64(double v);
	#endif
	
	void strToHexStr(const unsigned char *str, int len, char *strHex);
	void dump(const unsigned char *buf, int len);

#ifndef __WIN32__
	int subtractTime (struct timeval *result, struct timeval *x, struct timeval *y);
	void rt_check_start();
	void rt_check_end();
	void out_sysmsg(const char *buf, bool result);
	
//};

//----------------------------------------------------------------------------
extern struct timeval rt_stime;
#endif //__WIN32__ 

#endif

