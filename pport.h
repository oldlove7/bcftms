/*
 *  Socket Library 
 *
 *  Author       : Park Dong Ro
 *  LastModify   : 2002.6
 *  Comment      : C++ Portable Types Library Port 
 *
 */

#ifndef __PPORT_H__
#define __PPORT_H__


#define PTYPES_NAMESPACE pt

//
// conditional namespace declarations
//

#ifdef PTYPES_NAMESPACE
#  define PTYPES_BEGIN      namespace PTYPES_NAMESPACE {
#  define PTYPES_END        }
#  define USING_PTYPES      using namespace PTYPES_NAMESPACE;
#else
#  define PTYPES_NAMESPACE
#  define PTYPES_BEGIN
#  define PTYPES_END
#  define USING_PTYPES
#endif


#ifndef __cplusplus
#  error "This is a C++ source"
#endif

//
// Windows DLL export/import macros
//

#ifdef WIN32
#  if defined(PTYPES_DLL_EXPORTS)
#    define ptpublic __declspec(dllexport)
#  elif defined(PTYPES_DLL)
#    define ptpublic __declspec(dllimport)
#  else
#    define ptpublic
#  endif
#else
#  define ptpublic
#endif


//
// versioning
//


#define PTYPES_VERSION 0x00010706

extern "C" ptpublic unsigned long __ptypes_version;


PTYPES_BEGIN

//
// windows/msc/bcc specific
//

#ifdef _MSC_VER
// we don't want "unreferenced inline function" warning
#  pragma warning (disable: 4514)
#endif

#if defined(_DEBUG) && !defined(DEBUG)
#  define DEBUG
#endif

#if defined(__WIN32__) && !defined(WIN32)
#  define WIN32
#endif

#if defined(__APPLE__)
#  define __DARWIN__
#endif

// CHECK_BOUNDS affects the way an item is retrieved
// from AnsiString, objlist and strlist.

#ifdef DEBUG
#  define CHECK_BOUNDS
#endif


//
// useful typedefs
//

typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned short  ushort;
typedef unsigned char   uchar;
typedef signed char     schar;
typedef char*           pchar;
typedef const char*     pconst;
typedef void*           ptr;
typedef int*            pint;


//
// portable 64-bit integers:
//

#if defined(_MSC_VER) || defined(__BORLANDC__)
   typedef __int64             large;
   typedef unsigned __int64    ularge;
#else
   typedef long long           large;
   typedef unsigned long long  ularge;
#endif


#if defined(_MSC_VER) || defined(__BORLANDC__)
#  define strcasecmp stricmp
#  define snprintf _snprintf
// atoll() is not portable, use AnsiStringtoi() instead
// #  define atoll _atoi64
#endif


//
// misc.
//
#ifndef NULL
#   define NULL 0
#endif

#define nil 0

inline int   imax(int x, int y)       { return (x > y) ? x : y; }
inline int   imin(int x, int y)       { return (x < y) ? x : y; }
inline large lmax(large x, large y)   { return (x > y) ? x : y; }
inline large lmin(large x, large y)   { return (x < y) ? x : y; }


//
// memory management
//

ptpublic void* memalloc(uint a);
ptpublic void* memrealloc(void* p, uint a);
ptpublic void memfree(void* p);
ptpublic void memerror();


PTYPES_END

#endif // __PPORT_H__
