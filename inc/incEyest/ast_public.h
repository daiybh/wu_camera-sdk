#ifndef EYEST_STRUCT_H
#define EYEST_STRUCT_H

 
#ifdef __cplusplus
extern "C" {
#endif
// #############################################################################
// *****************************************************************************
//            Copyright (c) 2008-2014,    dtlink  Technology Co. Ltd.
//             This is the struct defination of  smartcam   struct 
// *****************************************************************************
// #############################################################################
//
// File:    dt_struct.h
// Author:  wang.fei
// First Created: 2015/03/20

// Description: Common definations.
// Change log:
//    <#> <date> <reason> <what are changed>
//          2015.3.25                 first create 
// -----------------------------------------------------------------------------

#pragma pack(push, 4)

#include "windows.h"
	//ȫ�ֺ궨��
	//-------------------------------------------------------------------
#define NET_DEV_DEVICE_NAME_LEN   32  //�豸���ֳ���
#define NET_DEV_IPV4_ADDR_LEN     16  //IPV4��ַ����
#define NET_DEV_IPV6_ADDR_LEN     48  //IPV6��ַ����
#define NET_DEV_MAC_ADDR_LEN      20  //MAC��ַ����

#define NET_DEV_MAX_USER_NUM      16  //����û�����
#define NET_DEV_USERNAME_LEN      32  //�û�������
#define NET_DEV_PASSWORD_LEN      16  //���볤��

#define NET_DEV_MAX_STREAM_NUM    3   //�����������
#define  NET_DEV_MAX_ALARM_IN_NUM   1 // ��������
#define NET_DEV_MAX_ALARM_OUT_NUM  1  //�������


#define  NET_DEV_MAX_ETH_NICS        1 
#define NET_DEV_SADP_ID_LEN  24 
#define NET_DEV_VERSION_LEN    24
#define NET_DEV_SERIAL_NO_LEN  24 
#define NET_DEV_DATE_LEN  24 
#define  NET_DEV_ID_LEN   24
#define NET_DEV_AUTHORIZECODE_LEN  24
#define NET_DEV_ALARM_DATA_SIZE   128
#define NET_DEV_MAX_LOG_PAGE_SIZE  1024
#define  NET_DEV_OSD_TEXT_LEN     128
#define  NET_DEV_OSD_TEXT_NUM    8
	//ȫ�ִ����붨��
	//-------------------------------------------------------------------


#define NET_DEV_ERROR_SUCCESS              0   //û�д���
#define NET_DEV_ERROR_TIMEOUT              1   //������ʱ
#define NET_DEV_ERROR_FAILED               2   //����ʧ��
#define NET_DEV_ERROR_PASSWORD             3   //�û����������
#define NET_DEV_ERROR_MAX_USERNUM          4  //�豸���û����ﵽ���
#define NET_DEV_ERROR_NOENOUGHPRI          5  //Ȩ�޲���


	//ȫ��ö�ٶ���

	// �豸����
	typedef enum _NET_DEV_TYPE
	{
		NET_DEV_TYPE_IPC  = 0x00,
		NET_DEV_TYPE_SMARTIPC  = 0x01,
		NET_DEV_TYPE_NVR  = 0x02,
		NET_DEV_TYPE_SMARTNVR  = 0x03,
		NET_DEV_TYPE_BUTT
	}NET_DEV_TYPE;

	//����Э��
	typedef enum _NET_DEV_TRANSPROTOL
	{
		NET_DEV_TRANS_TCP=0,
		NET_DEV_TRANS_UDP
	}NET_DEV_TRANSPROTOL;

 
typedef struct _NET_DEV_IPADDR
{
		char IpV4[NET_DEV_IPV4_ADDR_LEN];
		char IpV6[NET_DEV_IPV6_ADDR_LEN];
}NET_DEV_IPADDR;



//����
//------------------------------------------------------------


typedef enum _EYEST_PARAM_CMD_E_
{
	EYEST_STABLE_PARAM = 0x00,	// 0�豸������Ϣ
	EYEST_BASEPARAM    	 = 0x01,	// 1�豸������Ϣ
	EYEST_NET_PARAM,          	// 2�豸��������
	EYEST_VIDEO_PARAM,			// 3�豸��Ƶ���� 
	EYEST_VMAIN_PARAM,			// 4 �豸��Ƶ����������
	EYEST_VSUB_PARAM,		    	// 5 �豸��Ƶ����������
	EYEST_VTHREE_PARAM,       	// 6�豸������������
	EYEST_VCAP_PARAM,		    	// 7 �豸��Ƶץ�Ĳ���
	EYEST_IMA_PARAM,		    	// 8 �豸ͼ�����
	EYEST_3A_PARAM,		    	// 9 �豸3A����
	EYEST_USR_PARAM,		    	// 10 �û���������
	EYEST_PF_PARAM,           	// 11 ƽ̨��Ϣ
	EYEST_NTP_PARAM,		    	// 12ntp��������
	EYEST_PLATE_PARAM  ,               //13 plate 
	EYEST_CAR_PARAM  ,               //14 CAR
	EYEST_VD_PARAM  ,               //15 detect
	EYEST_WORKMODE_PARAM, //16  ������ʽ

	  EYEST_VIP_PARAM  ,             // 17 VIP INFO

	  EYEST_PARKSPACE_PARAM,
	  EYEST_SERIAL_CONTROL,//���ڿ���
	  EYEST_CHECK_TIME,  //����ʱ��
	  EYEST_SERIAL_INFO,//��������

     EYEST_LIGHT_PARAM ,

	 EYEST_OFFLINE_PIARAM,//23
	EYEST_ROIS_PARAM,
	EYEST_ADMIN_CARD_PARAM,

	EYEST_ISP_PARAM ,

}EYEST_PARAM_CMD_E;


// �豸������� 
typedef struct _NET_DEV_CFGNET
{
	NET_DEV_IPADDR IPAddr;		//�豸IP
	NET_DEV_IPADDR Netmask;		//��������
	NET_DEV_IPADDR Gateway;		//����
	char MACAddr[NET_DEV_MAC_ADDR_LEN];		//MAC��ַ
	unsigned char  EnableDHCP;		//�Ƿ�����DHCP
	unsigned char  EnableAutoDNS;		//�Ƿ������Զ���ȡDNS
	unsigned char  Mtu;				//MTU��СĬ�� 1500
	unsigned char  Interface;		//����ӿ� 1-10MBase-T 2-10MBase-Tȫ˫�� 3-100MBase-TX 4-100Mȫ˫�� 5-10M/100M/1000M����Ӧ
	NET_DEV_IPADDR DNS1;		//��DNS��������ַ
	NET_DEV_IPADDR DNS2;		//��DNS��������ַ
}NET_DEV_CFG_NET;



 
typedef struct _NET_DEV_ETHCFG
{
	unsigned char  NICCount;		//�豸֧�ֵ���̫��������(ֻ��)
	unsigned char  Res[3];		//����
	NET_DEV_CFG_NET EthNICs[NET_DEV_MAX_ETH_NICS];
}NET_DEV_ETHCFG;

typedef  struct _NET_DEV_SERVICECFG
{
	int  MsgPort;		//�豸����˿�
	int RtspPort;		//�豸RTSP�˿�
	int HttpPort;		//�豸HTTP�˿�
	int RtmpPort;		//�豸RTMP�˿�
}NET_DEV_SERVICECFG;



//===================================================================

//�����豸��Ϣ
//-------------------------------------------------------------------


typedef struct _NET_DEV_BROARDSEARCHINFO
{
	long    timeflag ;
	char  SoftwareVer[NET_DEV_VERSION_LEN];
	char  HardwareVer[NET_DEV_VERSION_LEN];
	char  SerialNo[NET_DEV_SERIAL_NO_LEN];		// ���к�
	unsigned char  DevType;		// NET_DEV_TYPE
	char  ProductName[NET_DEV_DEVICE_NAME_LEN];		//��Ʒ�ͺ�
	char  DeviceName[NET_DEV_DEVICE_NAME_LEN] ;
	char  DeviceID[NET_DEV_DEVICE_NAME_LEN] ;
	NET_DEV_ETHCFG EthCfg;
	NET_DEV_SERVICECFG ServiceCfg;
}NET_DEV_BROARDSEARCHINFO;




//�����޸���������
//-------------------------------------------------------------------
 
typedef struct _NET_DEV_MODIFY_NET
{
	long    timeflag ;
	char  UserName[NET_DEV_USERNAME_LEN];
	char  Passwd[NET_DEV_PASSWORD_LEN];

	NET_DEV_ETHCFG EthCfg;
	NET_DEV_SERVICECFG ServiceCfg;
}NET_DEV_MODIFY_NET;




//===================================================================
//�豸��������Ϣ
//-------------------------------------------------------------------

typedef enum _NET_DEV_SYS_CAP
{
	DEV_SYS_CAP_PTZ      = 0,   // ��̨
	DEV_SYS_CAP_WIFI     = 1,   // WIFI
	DEV_SYS_CAP_3G       = 2,   // 3G
	DEV_SYS_CAP_IVS      = 3,  // ���ܷ���
	DEV_SYS_CAP_IR       = 4   // ����
}NET_DEV_SYS_CAP;


// ���ܷ�������
typedef enum _NET_DEV_IVS_CAP
{
	NET_DEV_IVS_BRIGHT_ABMNL_CAP        = 1,  // �����쳣
	NET_DEV_IVS_CLARITY_ABMNL_CAP       = 2,  // �������쳣
	NET_DEV_IVS_NOISE_ABMNL_CAP         = 3,  // �����쳣
	NET_DEV_IVS_COLOR_ABMNL_CAP         = 4,  // ��ɫ�쳣
	NET_DEV_IVS_SCENE_CHANGE_CAP        = 5,  // �����任,��Ϊ����
	NET_DEV_IVS_TRIP_WIRE_CAP           = 6,  // ������
	NET_DEV_IVS_DOUBLE_TRIP_WIRE_CAP    = 7,  // ˫����
	NET_DEV_IVS_PERI_METER_CAP          = 8,  // ������
	NET_DEV_IVS_LOITER_CAP              = 9,  // �ǻ����
	NET_DEV_IVS_LEFT_CAP                = 10, // ��Ʒ����
	NET_DEV_IVS_TAKE_CAP                = 11, // ��Ʒ��ʧ
	NET_DEV_IVS_TAKE_PLATEREC         = 12, // ����ʶ��
	NET_DEV_IVS_CARREC         = 13, // ����ʶ��
	NET_DEV_IVS_CARTRACK         = 14, // ��������
}NET_DEV_IVS_CAP;





 //ͨ������
typedef struct _NET_DEV_CH_CAPABILITIES
{
	unsigned char  VideoEncType;		// ֧�ֵ���Ƶ���뼯 NET_DEV_VENC_TYPE
	unsigned char  AudioEncType;		// ֧�ֵ���Ƶ���뼯 NET_DEV_AENC_TYPE
	unsigned char  OsdCount;		// OSD����
	unsigned char  LostAlarm;		// �Ƿ�֧����Ƶ��ʧ����
	unsigned char  StreamCount;		// ��������
	int   Resolution[NET_DEV_MAX_STREAM_NUM];		//֧�ֵķֱ��ʼ� ���� NET_DEV_IMAGERESOLUTION
	int  FPS[NET_DEV_MAX_STREAM_NUM];		//֧�ֵ����֡�ʼ� ��ֵ��ʾ֧�ֵ����֡��ֵ
	
}NET_DEV_CH_CAPABILITIES;


typedef struct _NET_DEV_CAPABILITIES
{
	/*------- system -----*/
	char ProductName[NET_DEV_DEVICE_NAME_LEN];//��Ʒ�ͺ�
	unsigned char  DevType;		// �豸���� NET_DEV_TYPE
	unsigned char  EncChnCount;		// ����ͨ������
	unsigned char  DecChnCount;		// ����ͨ������
	unsigned char  AudioInCount;		// �����������
	unsigned char  AudioOutCount;		// �����������
	unsigned char  AlarmInCount;		// �����������
	unsigned char  AlarmOutCount;		// �����������
	unsigned char  Rs232Count;		// RS232���ڸ���
	unsigned char  Rs485Count;		// RS485���ڸ���
	unsigned char  EthCount;		// ����ڸ���
	unsigned char  DiskCount;		// Ӳ�̿ڸ���
	unsigned char  VoutCount;		// ��Ƶ����ڵĸ���
	unsigned char  UsbCount;		// USB�ڵĸ���
	int   IvsCap;		// ���ܷ������� NET_DEV_IVS_CAP
	int Res1[2];		// ����
	/*--------------------*/
	NET_DEV_CH_CAPABILITIES ChannelCap;		//ͨ������
}NET_DEV_CAPABILITIES;


//===================================================================
//�豸�汾��Ϣ
//===================================================================


typedef struct _NET_DEV_VERSION
{
	int DevType;		// �豸���ͣ� NET_DEV_TYPE
	char ProductName[NET_DEV_DEVICE_NAME_LEN];		//��Ʒ�ͺ�
	char SerialNo[NET_DEV_SERIAL_NO_LEN];		// ���к�
	char SoftwareVer[NET_DEV_VERSION_LEN];		// ����汾��
	char SoftwareDate[NET_DEV_DATE_LEN];		// �����������
	char DspSoftwareVer[NET_DEV_VERSION_LEN];		// DSP����汾
	char DspSoftwareDate[NET_DEV_DATE_LEN];		// DSP�����������
	char HardwareVer[NET_DEV_VERSION_LEN];		// Ӳ���汾

}NET_DEV_VERSION;





typedef struct _NET_DEV_CMS_CFG
{
	int   Enable;		//�Ƿ���
	char  PuId[NET_DEV_ID_LEN];		//�豸ID
	char  PuAC[NET_DEV_AUTHORIZECODE_LEN];		//�豸��Ȩ��
	NET_DEV_IPADDR CmsIP;		//������IP
	NET_DEV_IPADDR MdsIP;		//��ý��IP
	unsigned short  CmsPort;		//�������˿�
	unsigned short  MdsPort;		//��ý��˿�
	unsigned short  State;		//����״̬��1-CMS������  0-δ����
}NET_DEV_CMS_CFG;



//===================================================================
//�豸ʱ������
//===================================================================


typedef struct _NET_DEV_TIME_EX
{
	int   Zone;		//ʱ��
	int  Year;		//��
	unsigned char  Month;		//��
	unsigned char  Day;		//��
	 unsigned char  Week;		//����
	unsigned char  Hour;		//ʱ
	unsigned char  Minute;		//��
	unsigned char  Second;		//��
	int   MilliSec;		//����
}NET_DEV_TIME_EX;


////// old version 
typedef struct
{
	unsigned long  Zone;		//ʱ��
	unsigned short  Year;		//��
	unsigned char  Month;		//��
	unsigned char  Day;		//��
	unsigned char Week ;
	unsigned char  Hour;		//ʱ
	unsigned char  Minute;		//��
	unsigned char  Second;		//��
	unsigned long  MilliSec;		//����
}NET_DEV_TIME_EX_V1;


 

 
typedef struct _NET_DEV_NTPCFG
{
	int   EnableNTP;		//�Ƿ���: 0����������1��NTP��ʱ��2��CMS��ʱ
	int  EnableDST;		//����ʱʹ�ܣ�1�����ã�0��������
	NET_DEV_IPADDR NTPServer;		//NTP������
	int  TimeZone;		//ʱ��
	int UpdateInterval;		//��ʱ���
}NET_DEV_NTPCFG;



//===================================================================
//�������
//===================================================================
//��������
typedef enum _NET_DEV_STREAM_TYPE
{
	NET_DEV_STREAM_MAIN = 0,
	NET_DEV_STREAM_SECOND,
	NET_DEV_STREAM_THIRD
}NET_DEV_STREAM_TYPE;

//��Ƶ��������
typedef enum _NET_DEV_VENC_TYPE
{
	NET_DEV_VENC_H264   = 0x00,
	NET_DEV_VENC_MJPEG  = 0x01,
	NET_DEV_VENC_JPEG   = 0x02,
	NET_DEV_VENC_MPEG4  = 0x03,
	NET_DEV_VENC_H265   = 0x04,
	NET_DEV_VENC_BUTT
}NET_DEV_VENC_TYPE;

//��Ƶ��������
typedef enum _NET_DEV_AENC_TYPE
{
	NET_DEV_AENC_G711A = 0x00,
	NET_DEV_AENC_G711U = 0x01,
	NET_DEV_AENC_G726  = 0x02,
	NET_DEV_AENC_BUTT
}NET_DEV_AENC_TYPE;


//��������
typedef enum _NET_DEV_VENC_BITRATE_TYPE
{
	NET_DEV_BT_ABR = 0,
	NET_DEV_BT_CBR,
	NET_DEV_BT_VBR,
	NET_DEV_BT_FIXQP,
	NET_DEV_BT_BUTT
}NET_DEV_VENC_BITRATE_TYPE;

// 264 ����ȼ�
typedef enum _NET_DEV_ENCODELEVEL
{
	NET_DEV_EL_BASELINE = 0,
	NET_DEV_EL_MAIN,
	NET_DEV_EL_HIGH
}NET_DEV_ENCODELEVEL;


//�ֱ�������
typedef enum _NET_DEV_IMAGERESOLUTION
{
	NET_DEV_IMG_1080P       = 0,   // 1920*1080
	NET_DEV_IMG_720P       = 1,   // 1920*1080
	NET_DEV_IMG_960       = 2,   // 1920*1080
	NET_DEV_IMG_3Mega       = 15,   // 2048*1536
	NET_DEV_IMG_4Mega       = 16,   // 2560x1440
	NET_DEV_IMG_5Mega       = 17,   // 2592*1944
	NET_DEV_IMG_UltraHD     = 18,   // 3840*2160 4k ultra hd
	NET_DEV_IMG_BUTT
}NET_DEV_IMAGERESOLUTION;




 //������� 
typedef  struct _NET_DEV_ENCODEPARAM
{
	int  Resolution;
	int  EncodeLevel;		//����ȼ� 'NET_DEV_ENCODELEVEL'
	int  StreamMixType;		//����ģʽNET_DEV_STREAM_MIX_TYPE
	int  FrameRate;		//֡�� ��ֵ�� ����ֵ��5��10, 15, 20, 25, 30
	int IsFrameRatePreferred;		//�Ƿ�֡������ 1: ��, 0: ����
	int  IframeInterval;		//I֡��� ��ֵ�� ����ֵ: 25��50��75��100
	int  VideoEncodeType;		//��Ƶ��������, NET_DEV_VENC_TYPE
	int  ImageResolution;		//ͼ��ֱ��� 'NET_DEV_IMAGERESOLUTION'
	int  QPValue;		//����  ��ֵ�� ����ֵ��25��50
	int BitRateType;		//λ������ 'NET_DEV_VENC_BITRATE_TYPE'
	int  BitRate;		//λ�� 128k ~ 8000k
	int  AudioInputMode;		//��Ƶ�������� 'NET_DEV_AUDIOINPUTMODE'
	int  AudioEncodeType;		//��Ƶ�������� 'NET_DEV_AENC_TYPE'
}NET_DEV_ENCODEPARAM;


typedef struct _EYEST_CAPTURE_CFG_S_
{
	unsigned char 		u8VideoEncType;		//��Ƶ�����ʽ 2--JPEG �̶�ֵ
	unsigned char 		u8Quilty;			//ץ������ 
	unsigned char 		u8Res[30];	
}NET_CAPTURE_CFG_S, *LPNET_CAPTURE_CFG_S;



typedef  struct _NET_DEV_ENCODECFG
{
	NET_DEV_ENCODEPARAM Main;		//������    �������
	NET_DEV_ENCODEPARAM Second;		//������    �������
	NET_DEV_ENCODEPARAM Third;		//��������  �������
	NET_CAPTURE_CFG_S    jpegcfg;
}NET_DEV_ENCODECFG;

//===================================================================
//ͼ��Ч������
//===================================================================
typedef struct _NET_DEV_VIDEO_EFFECT
{
	int  Contrast;		//�Աȶ�
	int  Bright;		//����
	int  Hue;		//�Ҷ�
	int  Saturation;		//���Ͷ�
	int  Sharpness;		//���
}NET_DEV_VIDEO_EFFECT;

 
typedef  struct _NET_DEV_VIDEO_INPUT_EFFECT
{
	 int   EffectMode;		//ģʽ,0:�û�����, 1: Ĭ��ֵ
	NET_DEV_VIDEO_EFFECT CustomizeMode;		//�Զ���ģʽ����
}NET_DEV_VIDEO_INPUT_EFFECT;

//===================================================================
//����
//================================================

//���ڲ���
typedef struct _NET_DEV_SERIAL_CFG
{

	unsigned char  WorkMode;		//����ģʽ: 0 ��͸��ͨ��, 1 - PTZ ģʽ(ʹ��PTZ�еĴ��ڲ���), 
	unsigned char  BaudRate;		//���ڲ�����  (0-8) 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 600
	unsigned char  DataBit;		//����λ 5, 6, 7, 8
	unsigned char  StopBit;		//ֹͣλ 1, 2
	unsigned char  Verify;		//У��λ 0:�ޣ�1:��У�� 2:żУ��
	unsigned char  FlowControl;		//���� 0���ޣ�1��������, 2-Ӳ����
	unsigned char   unused[22]; //   

}NET_DEV_SERIAL_CFG;


typedef struct _NET_LIGHT_CFG
{
	int  light ;
}NET_DEV_LIGHT_CFG;


#define  MAX_CARD_LEN   32
#define  MAX_LEN        64
#define  MAX_OUT_CAM   16
#define  MAX_LINE       4 
#define  MAX_ADMIN      64
#define  MAX_TIME_STATE_COUNT 24 //ʱ���


typedef struct
{
	int     freetime ;
	float  PerMinuteFee;    //ÿ���ӷ���
	int    nStartTime[3] ; // H M S
	int    nEndTime[3] ;  //
	float  feerate ; //�ۿ�  Ĭ��1 
	char  unused[32] ;
}FeeRate;



//�ѻ� 
typedef struct
{
	int 	park_id;

	//�����������
	int  		nbasefreetimeDay ; //�������ʱ��  
	float	 	nBasePerMinuteFeeDay; //ƽ��ÿ���ӷ���
	int		extendTimeDay ;  //����ʱ��  ��
	//ҹ��������ʼ����ʱ�� ��ʱ��ʹ��
	int  	nbasefreetimeNight ;
	float	 	nBasePerMinuteFeeNight ;
	int     extendTimeNight ;
	//����ʱ���
	int 	nFeeCount ;
	FeeRate  struFeeRate[MAX_TIME_STATE_COUNT] ;
	unsigned char  unused[128] ;//����


}TFeeRateRecord;

typedef struct 
{
	int    nSize ; //�ṹ���С ==sizeof (OFFLINE_PARAM) 
	int 	enable; //ʹ���ѻ�
	int    nCamType ; //������� 0 ��� 1���� 2��λ 3δ֪
		

	int       ipcount  ;  //�����������
	char    leaveipaddr [MAX_OUT_CAM][16] ;
	int  	   openMode; //  0 ֱ�ӷ��� 1 ���� 2 id��

	//��Ļ���
	int     LedRow;   // ���������Ļ������
	char szscreen_static [MAX_LINE][MAX_LEN] ;   //ÿһ��Ĭ����ʾ in ���

	unsigned char  unusedscreen[256] ;  //����

	//�������
	char  szvoice_static[MAX_LEN];
	int     nvoicespeed ;
	int     nvoicevolume_normal ;
	int     nvoicevolume_night ;
	unsigned char  unusedvoice[252]; 

/////////////////////////////////////////////////////////

	TFeeRateRecord  gFreeRate ; //����
	int                   nJunFree ;
	unsigned char  unusedFee[252] ;//����

}OFFLINE_PARAM;
#define  NET_DEV_OFFLINE_INFO  OFFLINE_PARAM


typedef struct   
{
	// ��������  �̶�
	int   voicetype ;   
	int   voicespeed ;
	int   voicevolume ;
	char  szvoice_in[64] ; 
	char  szvoice_out[64] ;
	char  szvoice_none[64] ;
	// �̶�
	int    screenshowtype ;
	char szscreen_adv[64] ; // ���
	char szscreen_in[64] ;
	char szscreen_out[64] ;
	char szscreen_none[64] ;

	int     useip[6] ;
	char  leaveipaddr [6][16] ;

	int         freetime; // minite 
	float      moneyfee ; //every 30 minite fee

	int          autoopendoor ;
	char       unused[32] ;

}NET_DEV_OFFLINE_V1;

//==============================================
//�澯����
//==============================================
 
typedef struct _NET_DEV_ALARM_ITEM
{
	int   Channel;         //�澯ͼ��ͨ��
	int   AlarmType;		//�澯����
	int   Action;		//0����ʼ�澯��1�������澯
	int  Time;
	unsigned char  Data[NET_DEV_ALARM_DATA_SIZE];	  //�澯����
}NET_DEV_ALARM_ITEM;


//�û���Ϣ
//---------------------------------------
//�û�Ȩ��
 

typedef enum _NET_DEV_USER_REMOTERIGHT
{
	NET_DEV_USER_RR_PTZ_CTL = 0,/*Զ�̿�����̨*/
	NET_DEV_USER_RR_REC_MANUL,  /*Զ���ֶ�¼��*/
	NET_DEV_USER_RR_REC_PLAY,   /*Զ�̻ط� */
	NET_DEV_USER_RR_PARAM_SET,  /*Զ�����ò���*/
	NET_DEV_USER_RR_PARAM_GET,  /*Զ�̲鿴���� */
	NET_DEV_USER_RR_ADVANCED,   /*Զ�̸߼�����(��������ʽ��)*/
	NET_DEV_USER_RR_LOG_STATE,  /*Զ�̲鿴״̬����־*/
	NET_DEV_USER_RR_REAL_TALK,  /*Զ�̷��������Խ�*/
	NET_DEV_USER_RR_REAL_PLAY,  /*Զ��Ԥ��*/
	NET_DEV_USER_RR_ALARMOUT,   /*Զ�����󱨾��ϴ����������*/
	NET_DEV_USER_RR_VIDEOOUT,   /*Զ�̿��ƣ��������*/
	NET_DEV_USER_RR_RS232_TRNS, /*Զ�̿��ƴ���*/
	NET_DEV_USER_RR_CHANNEL,    /*Զ�̹���ģ���IP camera */
	NET_DEV_USER_RR_POWEROFF,   /*Զ�̹ػ�/���� */
}NET_DEV_USER_REMOTERIGHT;


 
typedef struct _NET_DEV_USER_INFO
{
	char  UserName[NET_DEV_USERNAME_LEN];		//�û���
	char  PassWord[NET_DEV_PASSWORD_LEN];		//����
//	 int LocalRight;	
	 unsigned long    RemoteRight;		//Զ�̲���Ȩ������ NET_DEV_USER_REMOTERIGHT
	 unsigned long    Reserve;		//���� 
}NET_DEV_USER_INFO;
 
 
typedef struct _NET_DEV_USER_MODIFY
{
	char  OldUserName[NET_DEV_USERNAME_LEN];		// ���û���
	char  OldPassWord[NET_DEV_PASSWORD_LEN];		// ���û���
	char  NewUserName[NET_DEV_USERNAME_LEN];		// ���û���
	char  NewPassWord[NET_DEV_PASSWORD_LEN];		// ������
	int   RemoteRight;		// Զ�̲���Ȩ������
	int  Reserve;
}NET_DEV_USER_MODIFY;


typedef struct _NET_DEV_CAMERAPARAM
{
	int   Mirror;		//����(ͼ�����ҵ���) 1 ���� 0 ������
	int  Flip;		//��ת(ͼ�����µ���) 1 ��ת 0 ����ת
	int  WdrMode;		//��̬ģʽ 0�Զ�   1 �� 2 �ر�
	int WdrStreng;		//0-255Ϊ��̬ǿ��

	int  DeNoiseLevel;		//����ȼ� 0--�ر� 1--�� 2--�� 3--��

	int  Rotate;		//��ת��0 ��    1 ��ת90��    2 ��ת270��
	int Shutter;		//���ӿ��� 0-9  0���Զ����� 1��1/25S�� 2��1/50S�� 3��1/100S�� 4: 1/200S 5��1/500S�� 6��1/1000S�� 7��1/2000S�� 8��1/5000S�� 9��1/10000S

	int  AwbMode;		//��ƽ��ģʽ 0 �Զ�1 ���� 2���� 3�Զ����� 4 �ֶ�
	int  AwbRed;		//��ƽ���ɫ
	int  AwbBlue;		//��ƽ����ɫ
	int  Blc;		//���ⲹ��0 �ر� 1 ��
	int  AEMinTime;		//�Զ��ع���С�ع�ʱ��,�Զ�����ʱ��Ч��0������,1��1/25S��2��1/50S��3��1/100S��4: 1/200S��5��1/500S��6��1/1000S��7��1/2000S��8��1/5000S��9��1/10000S
	int  AEMaxTime;		//�Զ��ع�����ع�ʱ��,ͬAEMinTime,��Ӧ>=AEMinTime
	int  AGain;		//�Զ�����(0-255)
	int   DGain;
	int   AVGLight;  // ��������

	int    Brightness;//����
	int    Contrast ;//�Աȶ�
	int    Sturation ;//���Ͷ�
	int     Hue ;//ɫ��
	int      Sharpness;	
	int       PowerSync;	
	int      LdcStreng ;


}NET_DEV_CAMERAPARAM;

typedef struct  
{
	unsigned long  Mirror;		//����(ͼ�����ҵ���) 1 ���� 0 ������
	unsigned long  Flip;		//��ת(ͼ�����µ���) 1 ��ת 0 ����ת
	unsigned long  WdrMode;		//��̬ģʽ 0�Զ�   1 �� 2 �ر�
	unsigned long  WdrStreng;		//0-255Ϊ��̬ǿ��

	unsigned long  DeNoiseLevel;		//����ȼ� 0--�ر� 1--�� 2--�� 3--��

	unsigned long  Rotate;		//��ת��0 ��    1 ��ת90��    2 ��ת270��
	unsigned long  Shutter;		//���ӿ��� 0-9  0���Զ����� 1��1/25S�� 2��1/50S�� 3��1/100S�� 4: 1/200S 5��1/500S�� 6��1/1000S�� 7��1/2000S�� 8��1/5000S�� 9��1/10000S
	unsigned long  AwbMode;		//��ƽ��ģʽ 0 �Զ�1 ���� 2���� 3�Զ����� 4 �ֶ�
	unsigned long  AwbRed;		//��ƽ���ɫ
	unsigned long  AwbBlue;		//��ƽ����ɫ
	unsigned long  Blc;		//���ⲹ��0 �ر� 1 ��

	unsigned long  AEMinTime;		//�Զ��ع���С�ع�ʱ��,�Զ�����ʱ��Ч��0������,1��1/25S��2��1/50S��3��1/100S��4: 1/200S��5��1/500S��6��1/1000S��7��1/2000S��8��1/5000S��9��1/10000S
	unsigned long  AEMaxTime;		//�Զ��ع�����ع�ʱ��,ͬAEMinTime,��Ӧ>=AEMinTime
	
	
	unsigned long  AGain;		//�Զ�����(0-255)
	
	unsigned long   DGain;
	unsigned long   AVGLight;  // ��������

	unsigned long    Brightness;//����
	unsigned long    Contrast ;//�Աȶ�
	unsigned long    Sturation ;//���Ͷ�
	unsigned long      Hue ;//ɫ��
	unsigned long       Sharpness;	

}NET_DEV_CAMERAPARAM_V1;




typedef struct _NET_DEV_CAMERACFG
{
	int   CameraMode;		// 0: �û��Զ��壬 1��Ĭ��ֵ
	NET_DEV_CAMERAPARAM CameraParam;		//�û��Զ���
}NET_DEV_CAMERACFG;


typedef struct  
{
	unsigned long  CameraMode;		// 0: �û��Զ��壬 1��Ĭ��ֵ
	NET_DEV_CAMERAPARAM_V1 CameraParam;		//�û��Զ���
}NET_DEV_CAMERACFG_V1;



typedef struct _NET_DEV_CAMERABASEINFO
{
	char     DevName[NET_DEV_DEVICE_NAME_LEN] ; // �豸����
	char     DevId[NET_DEV_DEVICE_NAME_LEN] ;      // �豸ID��
	char      DevType ;
	char      unused[7];
}NET_DEV_CAMBASEINFO;


// old version
typedef struct  
{
	char     DevName[NET_DEV_DEVICE_NAME_LEN] ; // �豸����
	char     DevId[NET_DEV_DEVICE_NAME_LEN-1] ;      // �豸ID��
	char      DevType ;
}NET_DEV_CAMBASEINFO_V1;


typedef  struct _NET_DEV_OSD_TEXT
{
	int    TextType ;// OSD����
	int TextEnable;		//�Ƿ���ʾ�ı���1����ʾ��0������
	int  TextX;		//�ı�����X
	int  TextY;		//�ı�����Y
	int  TextW;		//�ı����(��ȡ��Ч)
	int  TextH;		//�ı��߶�(��ȡ��Ч)
	char  TextData[NET_DEV_OSD_TEXT_LEN];
}NET_DEV_OSD_TEXT;


 
typedef struct _NET_SNAP_OSD
{
	int  DisplayAttr;		//osd ��ɫ��1��������0���ر�
	int  DisplayColor;		//osd��ʾ��ɫ
	int  MaxWidth;		//�����
	int  MaxHeight;		//���߶�
	NET_DEV_OSD_TEXT Texts[NET_DEV_OSD_TEXT_NUM];
}NET_DEV_SNAP_OSD;




//״̬��Ϣ
//------------------------------------------------------------
typedef enum _NET_DEV_STATE_IDX
{
	NET_DEV_STATE_NETWORK   = 0,    //NET_DEV_NETSTATES 
	NET_DEV_STATE_WORKS     = 1,    //NET_DEV_WORKSTATE
	NET_DEV_STATE_IVS     = 2,    // ���ܷ���״̬
}NET_DEV_STATE_IDX;


//------------------- IVS �ṹ���� -------------------
#define NET_DEV_MAX_POLYGON_POINT_NUM         8   //�������󶥵����
#define NET_DEV_MAX_OBJECT_NUM              16   //���Ŀ����
#define NET_DEV_MAX_TRACK_NUM              16   //������Ŀ����
#define NET_DEV_MAX_REC_PLATE_NUM         4   //�����ʶ����
#define      NET_DEV_MAX_RECT_NUM            4  //�����θ���

#define  MAX_SPACE                   3  //���λ��

// ��
 
typedef struct _NET_DEV_POINT
{
	int   x;
	int   y;
}NET_DEV_POINT;

 



// ��
 
typedef struct _NET_DEV_LINE
{
	NET_DEV_POINT Start;
	NET_DEV_POINT End;
}NET_DEV_LINE;


// �����
 
typedef struct _NET_DEV_POLYGON
{
	int   Count;		//����ζ�����
	NET_DEV_POINT Points[NET_DEV_MAX_POLYGON_POINT_NUM];		//����ε�����
}NET_DEV_POLYGON;

// ����
typedef struct _NET_DEV_RECT
{
	int  left ;
	int  top ;
	int  right  ;
	int  bottom  ; 
}NET_DEV_RECT;

typedef struct _NET_DEV_RECTLIST
{
	int  rectnum ;
	NET_DEV_RECT  rects[NET_DEV_MAX_RECT_NUM] ;
}NET_DEV_RECT_LIST;


// ����ʶ������ṹ

typedef struct _NET_DEV_PLATERECPARAM
{
		NET_DEV_RECT  recrect;//ʶ������
		int   samefilter ; 
		int   platesize ;
		int   recidx;
		int   platekind;		//��Ҫʶ��ĳ�������
		int   province;	 //Ĭ��ʡ�ݱ���

}NET_DEV_PLATERECPARAM;


typedef struct  _EYEST_RECROI
{
	NET_DEV_POLYGON  stPolyList ;
	NET_DEV_LINE  stSnapLine; //ץ���� 
	int       nPlateExistTime ; //���ƴ���ʱ��
	int        nDistance ;
	int        nDefaultHanzi ;
	int        nLens  ;
	int       nDetectNoPlate ;
	int        nFiterDirection; //���˳���
	int        nRecPlateType ; //����λ���� 
	int        nCarHeadCheck ;
	int        nCarModelCheck ;
	char       unused[40] ;
}EYEST_REC_ROIS ;

#define  NET_DEV_ROISPARAM  EYEST_REC_ROIS



// ����ģʽ
typedef struct _NET_DEV_WORKMODE
{
	int   workmode ; // 0 �ظ���Ȧ���� 1 ������Ȧ���� 2 ��Ƶʶ��
	// ˵��:������Ȧ��ʽ�Ǽ�⵽���˶���ץ��һ��ʶ��
	//��Ƶʶ�� �Ƕ�ʶ�����������֡����ʶ��ץ�����Ž��
	int    filterplate ; //1 �������Ƴ���  0,������ Ĭ�ϲ�����
 	int     filterdirection;
	unsigned char  useinside;  //ʹ���ڲ�����
	unsigned char  camtype  ;// ���1 ����2
	unsigned char  unuesd[6] ;
}NET_DEV_WORKMODE;


//�ڰ�����  
#define  MAX_PLATELEN  16 
typedef struct
{
	int type ;  // 0 ������  1 ������
	char  szplate[MAX_PLATELEN];
	int   nStartTime[6] ; // yy mm dd hh mm ss
	int   nEndTime[6] ;
}WhiteListMember;
 

typedef struct 
{
	 char szadmincard[32] ;
	 char  szadminname[32];
}NET_ADMIN_MEMBER  ;


//#define  MAXVIPCOUNT        81920
// ��� 1024 ��VIP    32 *80960   = 2.5M 
typedef  struct _NET_VIPINFOLIST
{
	int    m_vipcount ;
	WhiteListMember  *m_netvipinfo  ;
}NET_VIPINFOLIST;



#define  MAXVIPCOUNT        20000

typedef  struct _NET_VIPINFO  // 20 byte 
{
	char  szplatenum[13] ;
	unsigned char     startyear ;
	unsigned char      startmonth ;
	unsigned char      startday ;
	unsigned char       endyear ;
	unsigned char      endmonth ;
	unsigned char      endday ;
	unsigned char      viptype;
}NET_VIPINFO_V1;

// ��� 1024 ��VIP    20 *40960   =  800K 
typedef  struct  
{
	int    m_vipcount ;
	NET_VIPINFO_V1   m_netvipinfo[MAXVIPCOUNT] ;
}NET_VIPINFOLIST_V1;




typedef struct  
{
	int    m_admincount  ;
	NET_ADMIN_MEMBER *m_adminmember ;

}NET_ADMIN_MEMBERLIST;



// ����ʶ����
typedef struct _NET_DEV_PLATERESUT
{
	char   platenum[16]; //���ƺ���
	char   platecolor[8]; //������ɫ
	float   platereal ;  //�������Ŷ�
	NET_DEV_RECT platerect ; // ��������λ��
}NET_DEV_PLATERESULT;


// ����ʶ������ṹ

typedef struct _NET_DEV_CARRECPARAM
{
		int  maxsize ; //����������ؿ��
		int  minsize  ; //������С���ؿ��
}NET_DEV_CARRECPARAM;


 

typedef struct _NET_DEV_CARRECRESULT
{
	NET_DEV_RECT carrect ; // ��������λ��
	char                  carcolor[8];//������ɫ
	//char                  carmodel[128] ;//������Ϣ
	//float                  carfeature[1024]; //����������
}NET_DEV_CARRECRESULT;


//��λ����
typedef struct _NET_DEV_PARK_SPACEINFO
{
	char    spaceinfo[32];  // ��λ��Ϣ ��Ψһ��ʶ
	NET_DEV_RECT   spacerect;//��λ��ͼ���о���λ��
}NET_DEV_PARK_SPACEINFO;

// �����Ӧ��λ�����б�
typedef struct _NET_DEV_PARK_SPACELIST
{
		int        spacecount ; // ��Ӧ��λ��Ŀ
	    NET_DEV_PARK_SPACEINFO   spacerectinfo[MAX_SPACE];//��λ��ͼ���о���λ��
}NET_DEV_PARK_SPACELIST;



#define   EYEST_PLATELEN   16
#define   EYEST_COLORLEN   8
#define   EYEST_VTYPELEN    256

  

#define   EYEST_MAXLETTER    12

// ����ʶ��ṹ��
typedef struct _tagRv_AnprRsult
{
	char 	platenum[EYEST_PLATELEN];//## plate num   GB2312
	char platecolor[EYEST_COLORLEN] ;//## plate color GB2312
	char carcolor[EYEST_COLORLEN] ;//## plate color GB2312
	int   platecolorindex ;  //##  plate color index 
	int     platetype; //##  plate type 
	float  	platereliability ;  // ## plate realbility 
	float        plateletterreal[EYEST_MAXLETTER] ; // letter realbility 
	RECT  	platerect ;    // ## plate position  left  top right bottom  
	char        cartype[EYEST_VTYPELEN]; 	//## car type  (if rec this ,just support BGR mode,only support x86 now )
	float    cartypereliability ;  //## car type   realbility 
	float     vertangle;//##  plate vert angle 
	float      horzangle ;//##plate  horz angle 
}EYEST_ANPRRESULT, *PEYEST_ANPRRESULT;


typedef struct
{
	char 	platenum[EYEST_PLATELEN];//## plate num   GB2312
	char platecolor[EYEST_COLORLEN];//## plate color GB2312
	char carcolor[EYEST_COLORLEN];//## plate color GB2312
	int   platecolorindex;  //##  plate color index 
	float  	platereliability;  // ## plate realbility 
	float        plateletterreal[EYEST_MAXLETTER]; // letter realbility 
	RECT  	platerect;    // ## plate position  left  top right bottom  
	char     cartype[EYEST_VTYPELEN]; 	//## car type  (if rec this ,just support BGR mode,only support x86 now )
	float    cartypereliability;  //## car type   realbility 
	float     vertangle;//##  plate vert angle 
	float      horzangle;//##plate  horz angle 

}RV_ANPRRESULT_V1, *PRV_ANPRRESULT_V1;


typedef struct _NET_DEV_REC_RESUT
{
	unsigned char    spacestatus ; //��λ״̬		
	NET_DEV_CARRECRESULT carrecresult; //������Ϣ
	char                   spaceid[32] ;
	EYEST_ANPRRESULT   plateresult; //������Ϣ
}NET_DEV_REC_RESUT;

typedef struct 
{
	unsigned char    spacestatus ; //��λ״̬		
	NET_DEV_CARRECRESULT carrecresult; //������Ϣ
	char                   spaceid[32] ;
	RV_ANPRRESULT_V1   plateresult; //������Ϣ
}NET_DEV_REC_RESUT_V1;


//ͼƬ�������ֵ
#define NET_DEV_MAX_PIC_SIZE (1024*1024)

//�����λʶ�����б�
typedef struct _NET_DEV_SMARTRESUTLIST 
{
	int   smartmode ;// ����  0 ��������ץ�ģ�1 ��λ���
	int    spacecount ; // ��λ���� 
	NET_DEV_TIME_EX      checktime;  //���ơ�����ʶ���ʱ��
	NET_DEV_CAMBASEINFO    cambase;  //  ���Ψһ��Ϣ
	 NET_DEV_IPADDR  DevIP;    //�豸IP      
	NET_DEV_REC_RESUT  parkspaceresult[MAX_SPACE];
	int    imgwidth ;  //����ͼƬ�߶�  ��� ���������ǰ�ڴ����
	int    imgheight ;
	int     piclength;   //ͼƬ����
	int     platepiclength ; //��������ͼ�񳤶� ����� 0 û�г���
}NET_DEV_SMARTRECRESUTLIST;



typedef struct
{
	int   smartmode;// ����  0 ��������ץ�ģ�1 ��λ���
	int    spacecount; // ��λ���� 
	NET_DEV_TIME_EX_V1      checktime;  //���ơ�����ʶ���ʱ��
	NET_DEV_CAMBASEINFO_V1    cambase;  //  ���Ψһ��Ϣ
	NET_DEV_IPADDR  DevIP;    //�豸IP      
	NET_DEV_REC_RESUT_V1  parkspaceresult[MAX_SPACE];
	int    imgwidth;  //����ͼƬ�߶�  ��� ���������ǰ�ڴ����
	int    imgheight;
	int     piclength;   //ͼƬ����
}NET_DEV_SMARTRECRESUTLIST_V1;


typedef struct  
{
	RECT     ExcludeRoi;
	int           ExpType ;
	int          Strength ;
	int          Sensitivity ;

	unsigned int  weighttable[32] ;
	int   FlickerType ;
	int   nLight ;
	int   nBrightNess;
	int   nContrast ;
	int   nStaturation;
	unsigned char  unused[1024] ;

}NET_ISP_INFO;

//����ṹ��
typedef struct  
{
	char     camerIp[16];//���IP��ַ  16�ֽ��ַ���
	char     DevName[32] ; // �豸����  32�ֽ��ַ���
	char     DevId[32] ;      // �豸ID��  32�ֽ��ַ���
  	char   	platenum[16];//������ɫ    16�ֽ��ַ���   GB2312���뷽ʽ
	char     platecolor[8] ;//���ƺ���   8�ֽ��ַ���   GB2312���뷽ʽ


	int        nyear ;
	int        nmonth ;
	int       nday ;
	int       nhour ;
	int       nminite ;
	int       nsecond ;
	int       nmillisec ;


	int         plateleft ;
	int         platetop ;
	int         plateright ;
	int         platebottom ;
	float      realbility ; 
	int         snapmode ;
	char      szcarmodel[256] ;
	int         carstatus ;
	char      unuesd[256] ;
	
}NET_DEV_SMARTRECRESUT_EX;


 // �豸״̬
typedef struct _NET_DEV_WORKSTATE
{
	int  DeviceState;		// �豸��״̬��0��������1��CPUռ����̫�ߣ�����85%��
	unsigned char  AlarmInState[NET_DEV_MAX_ALARM_IN_NUM];		//��������ڵ�״̬��0-û�б�����1-�б���
	unsigned char  AlarmOutState[NET_DEV_MAX_ALARM_OUT_NUM];		//��������ڵ�״̬��0-û�������1-�б������
	int  LocalDisplayState;		//������ʾ״̬��0-������1-������
}NET_DEV_WORKSTATE;


typedef struct _NET_DEV_STATUS
{
	NET_DEV_IPADDR deviceipaddr; //�豸IP��Ϣ
	NET_DEV_CAMBASEINFO deviceinfo; // �豸������Ϣ(����ID�����Ƶ�)
	UINT   status; //״̬�֣����ߣ�����
}NET_DEV_STATUS;



typedef struct  
{
	char  ipaddr[16] ;//16�ֽ� �ַ��� ���IP��ַ
	int   status ;   //4�ֽ� ����    0��ʾ ����  1 ��ʾ����
}NET_DEV_STATUS_EX;



////����ID����
//----------------------------------------------------

typedef enum _NET_DEV_PARAM_ID
{
	NET_DEV_PARAM_VERSION             = 1,  // NET_DEV_VERSION            �豸������Ϣ v1
	NET_DEV_PARAM_BASECFG             = 2,  // NET_DEV_BASECFG            �豸������Ϣ v1
	NET_DEV_PARAM_TIME                = 3,  // NET_DEV_TIME_EX            ϵͳʱ����Ϣ v1
	NET_DEV_PARAM_NET                 = 4,  // NET_DEV_ETHCFG             ������Ϣ     v1
	NET_DEV_PARAM_SERVICECFG          = 5,  // NET_DEV_SERVICECFG         �������˿� v1
	NET_DEV_PARAM_USER_QUERY          = 6,  // NET_DEV_USERSET            �û���Ϣ��ѯ v1
	NET_DEV_PARAM_MODIFY_USER_CFG     = 7,  // NET_DEV_USER_MODIFY        �޸��û���Ϣ v1
	NET_DEV_PARAM_USER_ADD            = 8,  // NET_DEV_USER_INFO          �����û�(��Ȩ��)   v1
	NET_DEV_PARAM_USER_DEL            = 9,  // NET_DEV_USER               ɾ���û�(�û�����) v1
	NET_DEV_PARAM_VIDEOIN_EFFECT      = 10, // NET_DEV_VIDEO_INPUT_EFFECT ��Ƶ������� v1           CHN
	NET_DEV_PARAM_CAMERA_CFG          = 11, // NET_DEV_CAMERACFG          ͼ�����     v1           CHN
	NET_DEV_PARAM_ENCODECFG           = 12, // NET_DEV_ENCODECFG          �������     v1           CHN                  CHN
	NET_DEV_PARAM_PLATEREC            =13,//_NET_DEV_CARRECPARAM����ʶ�����
	NET_DEV_PARAM_CARREC            =14,//_NET_DEV_CARRECPARAM����ʶ�����
	NET_DEV_PARAM_OSDCFG          =15, //NET_DEV_SNAP_OSD  OSD ��Ϣ
	NET_DEV_PARAM_DEVICEINFO          =16,    // �豸��Ϣ����NET_DEV_CAMBASEINFO 
	NET_DEV_PARAM_OFFLINEINFO      = 17, //OFFLINE info
	NET_DEV_PARAM_CMS_CFG             = 100, // NET_DEV_CMS_CFG            ƽ̨��Ϣ
	NET_DEV_PARAM_MAX
}NET_DEV_PARAM_ID;


//��Ϣ����
//----------------------------------------------------



 //�û���¼����
typedef struct _NET_DEV_LOGIN_REQ
{
	NET_DEV_USER_INFO User;		// �û���������
	unsigned long    KeepAliveTime;		// �������� ��λ s
}NET_DEV_LOGIN_REQ;

  //������ص�¼��Ϣ
typedef struct _NET_DEV_LOGIN_RSP
{
	NET_DEV_USER_INFO UserInfo;		// �û���Ϣ(����Ȩ��)
	int            status ;   //��¼״̬
}NET_DEV_LOGIN_RSP;



// ������ ���﷢��һ��ʱ����Ϣ
typedef struct _NET_DEV_KEEPALIVE_RSP
{
	NET_DEV_TIME_EX TimeEx;		// ϵͳʱ��
}NET_DEV_KEEPALIVE_RSP;


typedef struct _NET_DEV_STATE_QUERY_REQ
{
	 int   StateType;		//NET_DEV_STATE_IDX
}NET_DEV_STATE_QUERY_REQ;


 
typedef  struct _NET_DEV_STATE_QUERY_RSP
{
	unsigned long  StateType;		//NET_DEV_STATE_IDX
	NET_DEV_WORKSTATE WorkState;
}NET_DEV_STATE_QUERY_RSP;


 
//  �ⴥ�������ò���
typedef struct _NET_DEV_TRIGER
{
		int   trigertype ;  //���������� 0 ����IO  1 �����豸,2�����豸
		char  ipaddr ;
		int    port  ;
}NET_DEV_TRIGER;

 

//////////////////////////////////////////////////////////////////////////

//�豸����

// �����ص�
typedef void ( __stdcall * NET_EVENTCALLBACK)(const NET_DEV_ALARM_ITEM *Report, void* UserParam);

//״̬�ص�����
typedef void ( __stdcall* NET_CONSTAUSCALLBACK)(NET_DEV_STATUS *status, void* UserParam);

// �����״̬�ص� 
typedef void ( __stdcall* NET_CONSTAUSCALLBACK_EX)(char  *ipaddr ,int status);

typedef void ( __stdcall* NET_IO_DATACALLBACK)(char* pData ,int *nLength, int address);



//���ܼ��״̬�ص����� 
// ����Ϊ�˼������ݿ������޸Ļص�������
//������Ϊ 0 ͼ��ͷ�����ݣ�1 ͼ��jpeg���ݣ�2 ͼ��jpeg���ȣ�3 �û�����
typedef void ( __stdcall * NET_SMARTRECVCALLBACK)( NET_DEV_SMARTRECRESUTLIST *SmartResult, char *pJpeg ,int *nLength , char *userdata ,void* UserParam);

typedef void(__stdcall * NET_SMARTRECVCALLBACKV1)(NET_DEV_SMARTRECRESUTLIST_V1 *SmartResult, char *pJpeg, int *nLength, char *userdata, void* UserParam);

// �����ʶ�����ص����� 
typedef void ( __stdcall * NET_SMARTRECVCALLBACK_EX)( NET_DEV_SMARTRECRESUT_EX *SmartResultEx, char *pJpeg ,int *nLength , char *userdata ,void* UserParam);


//�������ݻص� 
//�����ѻ�����  �����ݵ�
typedef void ( __stdcall * NET_MISC_CALLBACK)(char *pData ,int len ,void* UserParam);

// ��բ״̬�ص�ԭ��
typedef void ( __stdcall * NET_gate_callback)(const char* jsongate);
/*
�ص���������ԭʼ��ʽ
{"addr":2,"carcnt":0,"carstatus":1,"gatestatus":3,"open":0,"ready":1,"ver":328}


{
    "addr":2,        // ��բ��ַ 0~255
    "carcnt":0,      // δ����������
    "carstatus":1,   // ��բ�·�����״̬ 1�޳� 2�г�
    "gatestatus":3,  // ��բ״̬ 1����λ 2�ص�λ 3ֹͣ״̬ 4���ڿ�բ 5���ڹ�բ
    "open":-1,       // ��բԴ  1������2ң�أ� ������Ч
    "ready":1,       // ��բ������ָʾ  1��ʾ�����ӣ�����δ����
    "ver":328        // ��բ�汾��
}

*/


//DLL��������¼�ṹ�壬�˴������������Ӿ����ȡIP��ַ��
typedef struct  _net_dev_instance
{
	char ipaddr[16];
	int    port;
	int    clientsock;
	int   clientsockpic; //  ͼƬ����
	int      autoconnecttimes; // �Զ�����ʱ����

	BYTE  UserName[NET_DEV_USERNAME_LEN]; // �û���
	BYTE  PassWord[NET_DEV_PASSWORD_LEN]; // ����


	BOOL  AutoReconnect;   // �Ƿ��Զ����� 
	BOOL  beautothread;        // �Զ������߳��Ƿ�����
	BOOL  beautopicthread;         // �Զ������߳��Ƿ� pic  

	BOOL   beconnected;  // �����Ƿ�ɹ�
	BOOL   bepicconnected;  // �����Ƿ�ɹ� ͼƬ����

	HANDLE   hAutoconHandle; // �Զ������߳̾��
	HANDLE   hAutoExit;    // �Զ������߳��˳�EVENT

	HANDLE   hAutoconPicHandle; // �Զ������߳̾��
	HANDLE   hAutoPicExit;    // �Զ������߳��˳�EVENT

	HANDLE   hRecvHandle;
	HANDLE   hRecvExit;
	BOOL       berecvthread;// �����߳��Ƿ񴴽�

	HANDLE  hKeepAliveHandle;
	HANDLE   hAliveExit;

	HANDLE  hKeepAlivePicHandle;
	HANDLE   hAlivePicExit;


	BOOL     bekeepalive;

	BOOL   bekeepalivepic;


	BOOL  EventDesired;    // �Ƿ񱨾��ϱ�
	UINT  TimeOut;   // ��ʱʱ��
	void* UserParam;   // �û���Ϣ
	void * UserParamVZ;
	void  *VZLogInInfo;
	unsigned char *pjpegmem;

	NET_EVENTCALLBACK EventCallback; // �¼��ص�
	HWND hWnd;              // ���ھ��
	UINT Message;
	NET_CONSTAUSCALLBACK StatusCallback; //״̬�ص�
	NET_SMARTRECVCALLBACK     spaceresultcallback; // ����ص�
	NET_SMARTRECVCALLBACK_EX  spaceresultcallbackex;//
	//VZ_CAPCALLFUN                               m_vzcallback ;
	//NET_MISC_CALLBACK                       m_misccallback ;
	_net_dev_instance()
	{
		port = 8088;
		clientsock = -1;
		autoconnecttimes = 5;
		AutoReconnect = 0;
		beconnected = FALSE;
		EventDesired = 0;    // �Ƿ��ı����ϱ�
		TimeOut = 20;   // ��ʱʱ��
		strcpy_s((char*)UserName,sizeof(UserName), "admin");
		strcpy_s((char*)PassWord,sizeof(PassWord), "admin");
		EventCallback = NULL;
		StatusCallback = NULL;
		spaceresultcallback = NULL;
		spaceresultcallbackex = NULL;
		beautothread = FALSE;
		berecvthread = FALSE;
		//m_vzcallback  = NULL ;
		UserParamVZ = NULL;
		pjpegmem = NULL;
		//m_misccallback = NULL;
	}
}net_dev_instance;

#pragma pack(pop)

#ifdef __cplusplus
	}
#endif


#endif