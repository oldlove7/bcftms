//---------------------------------------------------------------------------
// dbstruct.h
// Author       : Park Dong Ro
// LastModify   : 2004.1
// Comment      :
//---------------------------------------------------------------------------

//-----------------------------------------------------------------
#ifndef _DBSTRUCT_H
#define _DBSTRUCT_H
//-----------------------------------------------------------------

//---------------------------------------------------------
#define MAX_WAYPOINT 			5120
#define MAX_ROUTE	   			256
#define MAX_ROUTE_WAYPOINT  	256	// �뼱�� WayPoint�� �ִ��.

#define MAX_WAYPOINT_NAME_SIZE	18	// WAYPOINT�̸��� �ִ����.
#define MAX_WAYPOINT_INFO_SIZE  48  // WAYPOINT �ֺ����� �ִ����.
#define MAX_ROUTE_NAME_SIZE   	8	// ROUTE�̸��� �ִ����.
#define MAX_ROUTE_ADDNAME_SIZE  20	// ROUTE �߰��̸��� �ִ����.

//---------------------------------------------------------
// FILE TYPE DEFINE
//---------------------------------------------------------
#define DBF_SYSTEM 			0		// 0
#define DBF_STAT 			1		// 1
#define DBF_WAYPOINT		2		// 2
#define FS_WAYPOINT_TMP		3		// 3
#define FR_WAYPOINT_TMP		4		// 4
#define DBF_ROUTE			5		// 5
#define FS_ROUTE_TMP		6		// 6
#define FR_ROUTE_TMP		7		// 7
#define PF_TBT				8		// 8
#define FR_TBT_TMP			9		// 9
#define FS_EVENT_IMAGE		10		// 1O


//---------------------------------------------------------
// WAYPOINT TYPE DEFINE
//---------------------------------------------------------
#define WP_STATION			1
#define WP_INTERSECTION		2
#define WP_END				3

//---------------------------------------------------------
// ROUTE TYPE DEFINE
//---------------------------------------------------------
#define WP_UNROUTED			0x01	// �뼱�� WAYPOINT
#define WP_SUBURB			0x02	// �ÿ� WAYPOINT

//---------------------------------------------------------
// FILE_TRANSFER_STAT
//---------------------------------------------------------
#define TF_STAT_NONE			0
#define TF_STAT_SEND			1
#define TF_STAT_RECV			2
#define TF_STAT_COMPLETE		3


#define MAX_FILE_TRANSFER_STAT 11

//---------------------------------------------------------
// TimeStamp
typedef struct {
	int year;
	int mon;
	int day;
	int hour;
	int min;
	int sec;
} DATETIME, *LP_DATETIME;

//---------------------------------------------------------
// CONFIG 
// size : 20 Bytes
//---------------------------------------------------------
typedef struct {
	unsigned short int term_id;
	unsigned short int bus_id;
	unsigned short int route_id;
	unsigned short int version1;			// ���α׷� ����
	unsigned short int version2;			// WAYPOINT DB ����
	unsigned short int version3;			// ROUTE DB ����
	unsigned char STATION_RADIUS;
	unsigned char INTSEC_RADIUS;
	unsigned char STOP_SPEED_LIMIT;			// �����ð� ���� ���� �ӵ�
	unsigned char DOOROPENRUN_SPEED_LIMIT;	// �������� ���� �ӵ�
	unsigned char OVER_SPEED_LIMIT;	
	unsigned char eventReplyConfirm;		// �̺�Ʈ ���� Ȯ�� 		0:���� 1:���
	unsigned char commMode;
	unsigned char dummy;					// dummy size match
} SYS_INFO, *LP_SYS_INFO;


//---------------------------------------------------------
// Version ����
//---------------------------------------------------------
typedef struct {
	unsigned short int version;		// Version
	unsigned short int checksum;	// checksum
} DB_INFO, *LP_DB_INFO;

//---------------------------------------------------------
// WayPoint ����
// size : 88 Bytes ���� �ٲ�� �ȵ�.
//---------------------------------------------------------
typedef struct {
	unsigned short int id;				// WayPoint ID
	unsigned short int type;			// ������ 1, ������ 2, ��.���� 3
    unsigned short int radius;
    char name[MAX_WAYPOINT_NAME_SIZE];	// WayPoint �̸�	18
    double latitude;					// ����				8
	double longitude;					// �浵				8
    char info[MAX_WAYPOINT_INFO_SIZE];	// �ֺ� ����		48
} WAYPOINT_INFO, *LP_WAYPOINT_INFO;

//---------------------------------------------------------
// �뼱 ����
// size: 1576 Bytes
//---------------------------------------------------------
typedef struct {
	unsigned short int id;			 				// �뼱 ID
	char name[MAX_ROUTE_NAME_SIZE];					// �̸�  ( 1, 10, 10-1 ... )	
	char addname[MAX_ROUTE_ADDNAME_SIZE];			// �߰� �̸�  ( ȿ���� ���, ��,û��)
	unsigned char type;
	unsigned char firstTimeHour;                    // ù�� ����ð�
	unsigned char firstTimeMin;
	unsigned char lastTimeHour;                     // ���� ����ð�
	unsigned char lastTimeMin;
	unsigned char runTimeGap;                       // ���� ����
	unsigned short int wpnum[2];	 				// ����
	unsigned short int wpid[2][MAX_ROUTE_WAYPOINT]; // �뼱 Waypoint ID ����Ʈ
    unsigned char unroute[2][MAX_ROUTE_WAYPOINT];   // �뼱�� Waypoint ǥ�� ( 0:�뼱 1:�뼱��)
} ROUTE_INFO, *LP_ROUTE_INFO;

//---------------------------------------------------------
// DB �ۼ��� ���� Header
// 12byte
//---------------------------------------------------------
typedef struct {
	unsigned short version;
	unsigned short blockNum;
	char type;				// 1 : WAYPOINT.DB  2 : ROUTE.DB
	char year;				// ���� �Ͻ�
	char mon;
	char day;
	char hour;
	char min;
	char sec;
    char reserved;
} DT_HEADER, *LP_DT_HEADER;


//---------------------------------------------------------
// �ܸ��� ���� 
//---------------------------------------------------------
typedef struct {
	unsigned short int term_id;
	unsigned short int bus_id;
	unsigned short int route_id;
	unsigned int wcomm_id;
} TERM_STAT, *LP_TERM_STAT;


//---------------------------------------------------------
// ���� ���� 
//---------------------------------------------------------
typedef struct {
	unsigned int fsize;
	unsigned int offset;
	char cl;
	char stat;
	
	// ���߿��� ���۽� Frame Number
	unsigned short int term_id;
	unsigned short int bus_id;
	unsigned short int route_id;
	unsigned char direction;
	DATETIME timestamp;
	unsigned char frameNo;
} FILE_TRANSFER_STAT, *LP_FILE_TRANSFER_STAT;

//---------------------------------------------------------
// ���� ���� 
//---------------------------------------------------------
typedef struct {
	TERM_STAT termStat;
	
	unsigned short int seqNo;
	int direction;
	int curWaypointID;				// ���� Waypoint ID
	int curStationIdx;				// ���� Station Waypoint Index
	int curWaypointIdx;				// ���� Waypoint Index

	int run_status;
	int run_time;
	double run_speed;
	double run_distance;		

	DATETIME routeStartTime;		// �뼱 ��� �ð� 
	DATETIME routeEndTime;			// �뼱 ���� �ð�
	
	// ���� BIS RSE ���� ����
	unsigned short RSE_ROUTE_ID;
	unsigned char  RSE_DIRECTION;
	unsigned short RSE_ID;
	unsigned short RSE_STATION_IDX;
	
	DATETIME routeTime_Plan;			// �뼱 ���� �ð�
	unsigned short int routeID_Plan;
	
	FILE_TRANSFER_STAT ftStat[MAX_FILE_TRANSFER_STAT];

} STAT_INFO, *LP_STAT_INFO;

//-----------------------------------------------------------------
#endif

