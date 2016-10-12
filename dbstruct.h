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
#define MAX_ROUTE_WAYPOINT  	256	// 노선당 WayPoint의 최대수.

#define MAX_WAYPOINT_NAME_SIZE	18	// WAYPOINT이름의 최대길이.
#define MAX_WAYPOINT_INFO_SIZE  48  // WAYPOINT 주변정보 최대길이.
#define MAX_ROUTE_NAME_SIZE   	8	// ROUTE이름의 최대길이.
#define MAX_ROUTE_ADDNAME_SIZE  20	// ROUTE 추가이름의 최대길이.

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
#define WP_UNROUTED			0x01	// 노선외 WAYPOINT
#define WP_SUBURB			0x02	// 시외 WAYPOINT

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
	unsigned short int version1;			// 프로그램 버전
	unsigned short int version2;			// WAYPOINT DB 버전
	unsigned short int version3;			// ROUTE DB 버전
	unsigned char STATION_RADIUS;
	unsigned char INTSEC_RADIUS;
	unsigned char STOP_SPEED_LIMIT;			// 정지시간 산출 기준 속도
	unsigned char DOOROPENRUN_SPEED_LIMIT;	// 개문주행 기준 속도
	unsigned char OVER_SPEED_LIMIT;	
	unsigned char eventReplyConfirm;		// 이벤트 응답 확인 		0:안함 1:사용
	unsigned char commMode;
	unsigned char dummy;					// dummy size match
} SYS_INFO, *LP_SYS_INFO;


//---------------------------------------------------------
// Version 정보
//---------------------------------------------------------
typedef struct {
	unsigned short int version;		// Version
	unsigned short int checksum;	// checksum
} DB_INFO, *LP_DB_INFO;

//---------------------------------------------------------
// WayPoint 정보
// size : 88 Bytes 순서 바뀌면 안됨.
//---------------------------------------------------------
typedef struct {
	unsigned short int id;				// WayPoint ID
	unsigned short int type;			// 정류장 1, 교차로 2, 기.종점 3
    unsigned short int radius;
    char name[MAX_WAYPOINT_NAME_SIZE];	// WayPoint 이름	18
    double latitude;					// 위도				8
	double longitude;					// 경도				8
    char info[MAX_WAYPOINT_INFO_SIZE];	// 주변 정보		48
} WAYPOINT_INFO, *LP_WAYPOINT_INFO;

//---------------------------------------------------------
// 노선 정보
// size: 1576 Bytes
//---------------------------------------------------------
typedef struct {
	unsigned short int id;			 				// 노선 ID
	char name[MAX_ROUTE_NAME_SIZE];					// 이름  ( 1, 10, 10-1 ... )	
	char addname[MAX_ROUTE_ADDNAME_SIZE];			// 추가 이름  ( 효성동 방면, 적,청등)
	unsigned char type;
	unsigned char firstTimeHour;                    // 첫차 운행시간
	unsigned char firstTimeMin;
	unsigned char lastTimeHour;                     // 막차 운행시간
	unsigned char lastTimeMin;
	unsigned char runTimeGap;                       // 배차 간격
	unsigned short int wpnum[2];	 				// 갯수
	unsigned short int wpid[2][MAX_ROUTE_WAYPOINT]; // 노선 Waypoint ID 리스트
    unsigned char unroute[2][MAX_ROUTE_WAYPOINT];   // 노선외 Waypoint 표시 ( 0:노선 1:노선외)
} ROUTE_INFO, *LP_ROUTE_INFO;

//---------------------------------------------------------
// DB 송수신 파일 Header
// 12byte
//---------------------------------------------------------
typedef struct {
	unsigned short version;
	unsigned short blockNum;
	char type;				// 1 : WAYPOINT.DB  2 : ROUTE.DB
	char year;				// 적용 일시
	char mon;
	char day;
	char hour;
	char min;
	char sec;
    char reserved;
} DT_HEADER, *LP_DT_HEADER;


//---------------------------------------------------------
// 단말기 상태 
//---------------------------------------------------------
typedef struct {
	unsigned short int term_id;
	unsigned short int bus_id;
	unsigned short int route_id;
	unsigned int wcomm_id;
} TERM_STAT, *LP_TERM_STAT;


//---------------------------------------------------------
// 파일 상태 
//---------------------------------------------------------
typedef struct {
	unsigned int fsize;
	unsigned int offset;
	char cl;
	char stat;
	
	// 돌발영상 전송시 Frame Number
	unsigned short int term_id;
	unsigned short int bus_id;
	unsigned short int route_id;
	unsigned char direction;
	DATETIME timestamp;
	unsigned char frameNo;
} FILE_TRANSFER_STAT, *LP_FILE_TRANSFER_STAT;

//---------------------------------------------------------
// 상태 정보 
//---------------------------------------------------------
typedef struct {
	TERM_STAT termStat;
	
	unsigned short int seqNo;
	int direction;
	int curWaypointID;				// 현재 Waypoint ID
	int curStationIdx;				// 현재 Station Waypoint Index
	int curWaypointIdx;				// 현재 Waypoint Index

	int run_status;
	int run_time;
	double run_speed;
	double run_distance;		

	DATETIME routeStartTime;		// 노선 출발 시간 
	DATETIME routeEndTime;			// 노선 도착 시간
	
	// 전주 BIS RSE 진입 정보
	unsigned short RSE_ROUTE_ID;
	unsigned char  RSE_DIRECTION;
	unsigned short RSE_ID;
	unsigned short RSE_STATION_IDX;
	
	DATETIME routeTime_Plan;			// 노선 도착 시간
	unsigned short int routeID_Plan;
	
	FILE_TRANSFER_STAT ftStat[MAX_FILE_TRANSFER_STAT];

} STAT_INFO, *LP_STAT_INFO;

//-----------------------------------------------------------------
#endif

