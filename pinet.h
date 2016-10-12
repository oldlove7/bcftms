/****************************************************************************
 *  Socket Library 
 *
 *  Author       : Park Dong Ro
 *  LastModify   : 2002.6
 *  Comment      : C++ Portable Types Library Port 
 *
 ****************************************************************************/

#ifndef __PINET_H__
#define __PINET_H__

#ifndef __PPORT_H__
#include "pport.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#   include <winsock2.h>
#else
#	include <errno.h>
#   include <netdb.h>       // for socklen_t
#   include <sys/types.h>
#   include <sys/socket.h>
#endif


PTYPES_BEGIN

#ifdef _MSC_VER
#pragma pack(push, 4)
#endif

const int invhandle = -1;

//
// BSD-compatible socket error codes for Win32
//

#if defined(WSAENOTSOCK) && !defined(ENOTSOCK)

#define EWOULDBLOCK             WSAEWOULDBLOCK
#define EINPROGRESS             WSAEINPROGRESS
#define EALREADY                WSAEALREADY
#define ENOTSOCK                WSAENOTSOCK
#define EDESTADDRREQ            WSAEDESTADDRREQ
#define EMSGSIZE                WSAEMSGSIZE
#define EPROTOTYPE              WSAEPROTOTYPE
#define ENOPROTOOPT             WSAENOPROTOOPT
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT
#define ESOCKTNOSUPPORT         WSAESOCKTNOSUPPORT
#define EOPNOTSUPP              WSAEOPNOTSUPP
#define EPFNOSUPPORT            WSAEPFNOSUPPORT
#define EAFNOSUPPORT            WSAEAFNOSUPPORT
#define EADDRINUSE              WSAEADDRINUSE
#define EADDRNOTAVAIL           WSAEADDRNOTAVAIL
#define ENETDOWN                WSAENETDOWN
#define ENETUNREACH             WSAENETUNREACH
#define ENETRESET               WSAENETRESET
#define ECONNABORTED            WSAECONNABORTED
#define ECONNRESET              WSAECONNRESET
#define ENOBUFS                 WSAENOBUFS
#define EISCONN                 WSAEISCONN
#define ENOTCONN                WSAENOTCONN
#define ESHUTDOWN               WSAESHUTDOWN
#define ETOOMANYREFS            WSAETOOMANYREFS
#define ETIMEDOUT               WSAETIMEDOUT
#define ECONNREFUSED            WSAECONNREFUSED
#define ELOOP                   WSAELOOP
// #define ENAMETOOLONG            WSAENAMETOOLONG
#define EHOSTDOWN               WSAEHOSTDOWN
#define EHOSTUNREACH            WSAEHOSTUNREACH
// #define ENOTEMPTY               WSAENOTEMPTY
#define EPROCLIM                WSAEPROCLIM
#define EUSERS                  WSAEUSERS
#define EDQUOT                  WSAEDQUOT
#define ESTALE                  WSAESTALE
#define EREMOTE                 WSAEREMOTE

// NOTE: these are not errno constants in UNIX!
#define HOST_NOT_FOUND          WSAHOST_NOT_FOUND
#define TRY_AGAIN               WSATRY_AGAIN
#define NO_RECOVERY             WSANO_RECOVERY
#define NO_DATA                 WSANO_DATA

#endif


// shutdown() constants

#if defined(SD_RECEIVE) && !defined(SHUT_RD)
#  define SHUT_RD       SD_RECEIVE
#  define SHUT_WR       SD_SEND
#  define SHUT_RDWR     SD_BOTH
#endif


// max backlog value for listen()

#ifndef SOMAXCONN
#  define SOMAXCONN -1
#endif

typedef char* sockval_t;

#ifndef WIN32
#  define closesocket close
#endif


#if defined(__DARWIN__) || defined(WIN32)
  typedef int psocklen;
#else
  typedef socklen_t psocklen;
#endif


/**********************************************************************
 * critical error processing
 **********************************************************************/
#define CRIT_FIRST 0xC0000

typedef void (*_pcrithandler)(int code, const char* msg);

ptpublic _pcrithandler getcrithandler();
ptpublic _pcrithandler setcrithandler(_pcrithandler newh);

ptpublic void fatal(int code, const char* msg);


/**********************************************************************
 * NetException
 **********************************************************************/
class ptpublic NetException
{
public:
    int code;
    const char* msg;
    NetException(int icode, const char* imsg) { code=icode; msg=imsg; }
    ~NetException(){};
    int getCode()          { return code; }
    const char* getMessage()    { return msg; }
};


// -------------------------------------------------------------------- //
// ---  IP address class and DNS utilities ---------------------------- //
// -------------------------------------------------------------------- //
//
// IP address
//
struct ptpublic ipaddress
{
    union
    {
        uchar   data[4];
        ulong   ldata;
    };
    ipaddress()                             {}
    ipaddress(ulong a)                      { ldata = a; }
    ipaddress(int a, int b, int c, int d);
    ipaddress& operator= (ulong a)          { ldata = a; return *this; }
    uchar& operator [] (int i)              { return data[i]; }
    operator ulong() const                  { return ldata; }
};

/**********************************************************************
 * ippeerinfo
 * IP peer info: host name, IP and the port name
 * used internally in ipstream and ipmessage
 **********************************************************************/
class ptpublic ippeerinfo
{
protected:
    ipaddress ip;         // target IP
    const char* host;     // target host name; either IP or hostname must be specified
    int       port;       // target port number
    void      notfound(); // throws a (estream*) exception

    friend ptpublic bool psockname(int, ippeerinfo&);
public:
    ippeerinfo();
    ippeerinfo(ipaddress iip, int iport);
    ippeerinfo(const char* ihost, int iport);
    ippeerinfo(ipaddress iip, const char* ihost, int iport);

    ipaddress getAddress();  // resolves the host name if necessary (only once)
    const char* get_host();  // performs reverse-lookup if necessary (only once)
    int       getPort();

    void      clear();
    char* asString(bool showport) const;
};

/**********************************************************************
 * ipbindinfo
 * common internal interfaces for ipstmserver and ipmsgserver
 **********************************************************************/
class ipbindinfo: public ippeerinfo
{
public:
    int handle;

    ipbindinfo(ipaddress iip, const char* ihost, int iport);
    virtual ~ipbindinfo();
};

ptpublic extern ipaddress ipnone;
ptpublic extern ipaddress ipany;
ptpublic extern ipaddress ipbcast;


ptpublic char* iptoString(ipaddress ip);
ptpublic ipaddress  phostbyname(const char* name);
ptpublic const char* phostbyaddr(ipaddress ip);
ptpublic const char* phostcname(const char* name);


// internal utilities
ptpublic int usockerrno();
ptpublic const char* usockerrmsg(int code);
ptpublic bool psockwait(int handle, int timeout);
ptpublic bool psockname(int handle, ippeerinfo&);


// -------------------------------------------------------------------- //
// ---  TCP socket classes -------------------------------------------- //
// -------------------------------------------------------------------- //

// status codes: compatible with WinInet API
// additional status codes are defined in pinet.h for ipsocket
const int IO_CREATED    = 1;
const int IO_OPENING    = 5;
const int IO_OPENED     = 35;
const int IO_READING    = 37;
const int IO_WRITING    = 38;
const int IO_EOF        = 45;
const int IO_CLOSING    = 250;
const int IO_CLOSED     = 253;

// additional IO status codes
const int IO_RESOLVING  = 10;
const int IO_RESOLVED   = 11;
const int IO_CONNECTING = 20;
const int IO_CONNECTED  = 21;


/**********************************************************************
 * ipstream
 **********************************************************************/
class ptpublic ipstream: public ippeerinfo
{
    friend class ipstmserver;

protected:
    int svsocket;   // server socket descriptor, used internally by ipstmserver
    void closehandle();

public:
    //------------------------------
    // 추가 코드.
    int     handle;
    bool    active;
    bool    cancelled;
    int     stmerrno;       // UNIX-compatible error numbers, see comments in piobase.cxx
    int     status;         // stream status code, see IO_xxx constants above

    void    open();
    void    open(int port);
    void    open(const char *localAddr, int localPort);
    void    close();
    //------------------------------

    ipstream();
    ipstream(ipaddress ip, int port);
    ipstream(const char* host, int port);
    virtual ~ipstream();

    bool      waitfor(int timeout);
    ipaddress getLocalAddress();
    int       getLocalPort();
    void      set_ip(ipaddress);
    void      set_host(const char*);
    void      set_port(int);
    
    //#ifdef WIN32
    virtual int recv(char* buf, int len);
    virtual int recv(char* buf, int off, int len);
    virtual int send(const char* buf, int len);
    virtual int send(const char* buf, int off, int len);
	//#endif

    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);
};

#define MAX_BINDADDR_SIZE 2
/**********************************************************************
 * ipsvbase
 **********************************************************************/
class ptpublic ipsvbase
{
protected:
    int     socktype;
    bool    active;
    //std::vector<ipbindinfo *> addrlist;
    int addrlistSize;
    ipbindinfo* addrlist[MAX_BINDADDR_SIZE];

    void error(ippeerinfo& peer, int code, const char* defmsg);
    bool dopoll(int* i, int timeout);
    void setupfds(void* set, int i);
    virtual void open();
    virtual void close();
    virtual void dobind(ipbindinfo*) = 0;

public:
    ipsvbase(int isocktype);
    virtual ~ipsvbase();

    void bind(ipaddress ip, int port);
    void bindall(int port);

    //int get_addrcount()                  { return length(addrlist); }
    const ipbindinfo& get_addr(int i)    { return *(ipbindinfo*)addrlist[i]; }
    void clear();
};


/**********************************************************************
 * ipstmserver
 **********************************************************************/
class ptpublic ipstmserver: public ipsvbase
{
protected:
    virtual void dobind(ipbindinfo*);

public:
    ipstmserver();
    virtual ~ipstmserver();

    bool poll(int i = -1, int timeout = 0);
    bool serve(ipstream& client, int i = -1, int timeout = -1);
    ipstream* accept( int addrIndex);
};


// -------------------------------------------------------------------- //
// ---  UDP socket classes -------------------------------------------- //
// -------------------------------------------------------------------- //

/**********************************************************************
 * ipmessage
 **********************************************************************/
class ptpublic ipmessage: public ippeerinfo
{
protected:
    int handle;

    //void error(int code, const char* msg);
 public:
    ipmessage();
    ipmessage(ipaddress ip, int port);
    ipmessage(const char* host, int port);
    virtual ~ipmessage();

	void open();
    void open(int port);
    void open(const char *address, int port);
    void close();
    
    void set_ip(ipaddress iip);
    void set_host(const char*);
    void set_port(int);
    ipaddress getLocalAddress();
    int getLocalPort();

    bool waitfor(int timeout);
    int  receive(char* buf, int len);
    int  receive(char* buf, int len, ipaddress *remoteAddr, int *remotePort);
    void send(const char* buf, int len);
    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);
};


/**********************************************************************
 * ipmsgserver
 **********************************************************************/
class ptpublic ipmsgserver: public ipsvbase, public ippeerinfo
{
protected:
    int handle;

    virtual void close();
    virtual void dobind(ipbindinfo*);

public:
    ipmsgserver();
    virtual ~ipmsgserver();

    bool poll(int i = -1, int timeout = 0);
    int  receive(char* buf, int count);
    void send(const char* buf, int count);
    void sendto(const char* buf, int count, ipaddress ip, int port);
    bool setSoTimeout(int miliseconds);
    bool setReceiveBufferSize(int size);
    bool setSendBufferSize(int size);

};


#ifdef _MSC_VER
#pragma pack(pop)
#endif

PTYPES_END
#endif // __PINET_H__

