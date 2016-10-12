
//----------------------------------------------------------------------------
#ifndef Z_BTMP_H
#define Z_BTMP_H
//----------------------------------------------------------------------------

#define Version = "1.0";

#define BTMP_IP 		    		"192.168.0.173"
#define BTMP_PORT 		    		6001
#define FT_DATASIZE 	    		1400		// IP+UDP Header Size =32
#define FT_PACKETSIZE       		FT_DATASIZE+4
                            		
#define FT_OP_RRQ 		    		0x01
#define FT_OP_WRQ 		    		0x02
#define FT_OP_DATA 		    		0x03
#define FT_OP_ACK 		    		0x04
#define FT_OP_ERROR 	    		0x05
#define FT_OP_EXISTS	    		0x06
#define FT_OP_BRRQ		    		0x07
#define FT_OP_BWRQ		    		0x08
                            		
#define OP_REQ_STAT         		0x10
#define OP_RES_STAT         		0x11
                            		
#define OP_CMD_TASK_STOP    		0x20
#define OP_CMD_TASK_START   		0x21
                            		
#define OP_ACK              		0xA0
#define OP_NACK             		0xA2
                            		
#define FT_MODE_OCTET				0
#define FT_MODE_NETASCII			1
                            		
#define FT_TYPE_DATA				0
#define FT_TYPE_PROGRAM				1
#define FT_TYPE_DB					2

#define ERR_NOT_DEFINED 			0
#define ERR_FILE_NOT_FOUND 			1
#define ERR_ACCESS_VIOLATION 		2
#define ERR_DISK_FULL 				3
#define ERR_ILLEGAL_TFTP_OPERATION 	4
#define ERR_UNKNOWN_TRANSFER_ID 	5
#define ERR_FILE_ALREADY_EXISTS 	6
#define ERR_NO_SUCH_USER 			7

/*
char * modeStrings[] = {
    "octet",
    "netascii"
};

char * errCodeStrings[] = {
    "not defined",
    "file not found",
    "access violation",
    "disk full",
    "illegal TFTP operation",
    "unknown transfer id",
    "file already exists",
    "no such user"
};
*/

#endif
