#ifndef EYEST_NETAPI_H
#define EYEST_NETAPI_H
#ifdef __cplusplus
extern "C" {
#endif


// #############################################################################
// *****************************************************************************
//            Copyright (c) 2008-2016,   smart ipc tech
//             This is the struct defination of  smartcam   struct 
// *****************************************************************************
// #############################################################################
//
// File:    eyest_netapi.h
// Author:  wang.fei
// First Created: 2015/03/20

// Description: Common definations.
// Change log:
//    <#> <date> <reason> <what are changed>
//          2015.3.25                 first create 
// -----------------------------------------------------------------------------

#pragma pack(push, 4)

#ifdef WIN32
#define EYEST_API 	  /* __declspec(dllexport)*/
#else
#define EYEST_API 
#endif

#define  EYEST_CALL   __stdcall
#include "ast_public.h"
//////////////////////////////////////////////////////////////////////////
	//״̬�ص���Ϣ
#define NET_DEV_CB_CONN_START            0
#define NET_DEV_CB_CONN_OK               1
#define NET_DEV_CB_CONN_FAIL             2
#define NET_DEV_CB_CONN_CLOSED           3
 

//�����豸�ص�����
typedef BOOL ( CALLBACK * NET_SEARCHCALLBACK)(  NET_DEV_BROARDSEARCHINFO* dev_info, void* UserParam);

typedef	struct _NET_SEARCHPARAM
{
		UINT  ProtolType; //NET_DEV_PROTOL_TYPE
		void* UserParam;
		NET_SEARCHCALLBACK Callback;
}NET_SEARCHPARAM;


typedef  struct _NET_CONPARAM
{

	 _NET_CONPARAM()
	{
		Port = 8088;
		strcpy_s((char*)UserName, sizeof(UserName), "admin");
		strcpy_s(PassWord, sizeof(PassWord), "12345");
		AutoReconnect = 0;
		TimeOut = 10*1000;
		EventCallback =NULL;
		StatusCallback = NULL;
		spaceresultcallback = NULL;
		spaceresultcallbackex = NULL;
		spaceresultcallbackv1 = NULL;
	};
	NET_DEV_IPADDR  IpAddr; // IP��ַ
	WORD  Port;   // �˿ں�
	char  UserName[NET_DEV_USERNAME_LEN]; // �û���
	char  PassWord[NET_DEV_PASSWORD_LEN]; // ����
	BOOL  AutoReconnect;   // �Ƿ��Զ����� 
	BOOL  EventDesired;    // �Ƿ񱨾��ϱ�
	int   TimeOut;   // ��ʱʱ��
	void* UserParam;
	HWND hWnd;
	UINT Message;
	NET_EVENTCALLBACK EventCallback;
	NET_CONSTAUSCALLBACK StatusCallback;
	NET_SMARTRECVCALLBACK     spaceresultcallback;
	NET_SMARTRECVCALLBACKV1 spaceresultcallbackv1;
	NET_SMARTRECVCALLBACK_EX     spaceresultcallbackex;
	NET_MISC_CALLBACK                     misccallback ;
	NET_gate_callback			gatestatuscallback; // ������բ״̬�ı�ص����� 2018.09.25

}NET_CONPARAM;


typedef  LONG  NET_CONECTION;

//��ƵԤ��

// ��Ƶ���ݻص� 
typedef void ( EYEST_CALL   * NET_PREVIEWDATACALLBACK)(unsigned char * Frame,  int  framelength ,  int width ,int height ,int  frametype ,void* UserParam);


typedef void ( EYEST_CALL   * NET_DECODEDATACALLBACK)(unsigned char * Frame,  int  width ,int height  ,void* UserParam);

// Ԥ��״̬�ص�
typedef void (  EYEST_CALL   * NET_PREVIEWSTAUSCALLBACK)(WORD Code, HWND hWnd, UINT Msg, void* UserParam);

//���Իص�
typedef void (  EYEST_CALL   * NET_DEBUGVIEWCALLBACK)( char *ipaddr ,char *szInfo ,void *pUser );


typedef struct _NET_PREVIEWPARAM
{
	_NET_PREVIEWPARAM()
	{
			Channel=0;
			StreamType= 1;
			AutoReconnect =1;
			DataCallback = NULL;
			StatusCallback = NULL;
			DecodeCallback = NULL;
			VideoPort = 554 ;
			nNeedFocus = 0;
	}
	UINT Channel;       // ͨ���� 0,1,2,3...
	int      nNeedFocus;
	BYTE StreamType;     // NET_DEV_STREAM_TYPE
	BYTE Content;       // NET_DEV_STREAM_MIX_TYPE
	UINT Protol;         // NET_DEV_TRANSPROTOL
	int      VideoPort ;
	BOOL AutoReconnect;
	void* UserParam;
	HWND hWnd;
	UINT Message;
	NET_PREVIEWDATACALLBACK DataCallback;
	NET_PREVIEWSTAUSCALLBACK StatusCallback;
	NET_DECODEDATACALLBACK     DecodeCallback;

}NET_PREVIEWPARAM;

typedef  LONG  NET_DEV_Preview;

 
typedef struct _NET_DEV_QueryDeviceStateParam
{
	void* UserParam;
	NET_DEV_STATE_QUERY_REQ Req;
	NET_DEV_STATE_QUERY_RSP* Rsp;
	UINT  OutBufferSize;
	UINT  TimeOut;     //��ʱʱ�� s
}NET_DEV_QueryDeviceStateParam;

//��������
 
typedef struct _NET_GET_PARAM
{
	UINT Channel; // ͨ����
	UINT ParamID;   //NET_DEV_PARAM_ID
	BYTE  OutBuffer[1024*128];  // ��ȡ��������
	UINT  ReturnedSize;  // ��ȡ�������ݴ�С
	UINT  TimeOut;     //��ʱʱ�� s
}NET_GET_PARAM;
 
 
typedef struct _NET_SET_PARAM 
{
	UINT Channel;
	UINT ParamID;   //NET_DEV_PARAM_ID
	BYTE InBuffer[1024*128];
	UINT  InBufferSize;
	UINT  TimeOut;      //��ʱʱ�� s
}NET_SET_PARAM;

// CU ���� �ͻ���   PU ���� �豸��
//��ʼ��
EYEST_API  BOOL    EYEST_CALL  EYEST_NET_INIT();
// ����ʼ��
EYEST_API  void    EYEST_CALL  EYEST_NET_RELEASE();



EYEST_API  BOOL  EYEST_CALL   EYEST_NET_INITSERVER(UINT port );


// ע���¼��ص�
EYEST_API  BOOL   EYEST_CALL  EYEST_REGISTER_EVENTCALLBACK(NET_EVENTCALLBACK  pFun,void *userparam) ;

// ע�����ܼ�����ص�
EYEST_API  BOOL  EYEST_CALL  EYEST_REGISTER_SMARTCALLBACK(NET_SMARTRECVCALLBACK pFun,void *userparam) ;

//ע��ص� �������עʶ����ע��ص���
EYEST_API  BOOL EYEST_CALL  EYEST_REGISTER_SMARTCALLBACK_EX(NET_SMARTRECVCALLBACK_EX pFun,void *userparam) ;

// ע��״̬�ص�
EYEST_API  BOOL EYEST_CALL  EYEST_REGISTER_STATECALBACK(NET_CONSTAUSCALLBACK  pFun,void *userparam) ;


EYEST_API  BOOL  EYEST_CALL EYEST_REGISTER_IODATACALLBACK(NET_CONECTION Conn,NET_IO_DATACALLBACK  pFun,void *userparam); 


//��ȡ������
EYEST_API  UINT   EYEST_CALL  EYEST_NET_GET_LEYEST_ERROR();
//�����豸
EYEST_API  void  EYEST_CALL   EYEST_NET_SEARCH_DEV(const NET_SEARCHPARAM* Param);

//���������豸IP��Ϣ
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SET_DEV_INFO(const NET_DEV_MODIFY_NET* Param);

//�豸����
EYEST_API  NET_CONECTION   EYEST_CALL   EYEST_NET_LOGIN(const NET_CONPARAM* Param );


// new 
EYEST_API  NET_CONECTION   EYEST_CALL   EYEST_NET_GET_DEVICETYYPE(NET_CONECTION Conn );



//�˳�����
EYEST_API  void  EYEST_CALL   EYEST_NET_LOGOUT(NET_CONECTION Conn);

//���ĸ澯,���ĺ�NET_EVENTCALLBACK�вŻ��и澯����
EYEST_API  void  EYEST_CALL    EYEST_NET_ALARM_SUBSCRIBE(NET_CONECTION Conn, BOOL Desired);


//��ƵԤ��
EYEST_API  NET_DEV_Preview  EYEST_CALL   EYEST_NET_START_PREVIEW(NET_CONECTION Conn
												 , const NET_PREVIEWPARAM* Param);

//ֹͣ��ƵԤ��
EYEST_API  void   EYEST_CALL   EYEST_NET_STOP_PREVIEW(NET_CONECTION Conn,NET_DEV_Preview Preview);


// ��ȡһ֡������RGB���ݣ������û���������ʾʹ�� ��������ƵԤ���򿪺���Ի�ȡ������
//��Ҫ �Լ����� һ���ڴ潨�� 1920*1080*3 
EYEST_API  void   EYEST_CALL  EYEST_NET_GET_PREVIEW_RGB( NET_DEV_Preview Preview,char *rgb ,int *width ,int *height );
 

//��������
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_GET_PARAM(NET_CONECTION Conn, const NET_GET_PARAM* Param);
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SET_PARAM(NET_CONECTION Conn, const NET_SET_PARAM* Param);

//���������ȡ����ֵ
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_NET_PARAM(NET_CONECTION Conn, NET_DEV_CFG_NET *net_cfg) ;
EYEST_API  BOOL  EYEST_CALL  EYEST_NET_SET_NET_PARAM(NET_CONECTION Conn,NET_DEV_CFG_NET *net_cfg ) ;


// �豸����������ȡ

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_BASE_PARAM(NET_CONECTION Conn, NET_DEV_CAMBASEINFO *base_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_BASE_PARAM(NET_CONECTION Conn,NET_DEV_CAMBASEINFO *base_cfg ) ;

// for old version  
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_BASE_PARAM_V1(NET_CONECTION Conn, NET_DEV_CAMBASEINFO_V1 *base_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_BASE_PARAM_V1(NET_CONECTION Conn,NET_DEV_CAMBASEINFO_V1 *base_cfg ) ;



//CMS ƽ̨����
EYEST_API  BOOL  EYEST_CALL  EYEST_NET_GET_CMS_PARAM(NET_CONECTION Conn, NET_DEV_CMS_CFG *cms_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_CMS_PARAM(NET_CONECTION Conn,NET_DEV_CMS_CFG *cms_cfg ) ;


// ͼ�����

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_IMG_PARAM(NET_CONECTION Conn, NET_DEV_VIDEO_INPUT_EFFECT *img_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_IMG_PARAM(NET_CONECTION Conn,NET_DEV_VIDEO_INPUT_EFFECT *img_cfg ) ;




// �߼�ͼ����� ��3A
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_3A_PARAM(NET_CONECTION Conn, NET_DEV_CAMERACFG *img3a_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_3A_PARAM(NET_CONECTION Conn,NET_DEV_CAMERACFG *img3a_cfg ) ;

// for old versions
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_3A_PARAM_V1(NET_CONECTION Conn, NET_DEV_CAMERACFG_V1 *img3a_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_3A_PARAM_V1(NET_CONECTION Conn,NET_DEV_CAMERACFG_V1 *img3a_cfg ) ;


//ͼ��������
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ENCODE_PARAM(NET_CONECTION Conn, NET_DEV_ENCODECFG *encode_cfg) ;
EYEST_API  BOOL EYEST_CALL   EYEST_NET_SET_ENCODE_PARAM(NET_CONECTION Conn,NET_DEV_ENCODECFG *encode_cfg ) ;

 
// ʶ�����  <old >
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PLATEREC_PARAM(NET_CONECTION Conn, NET_DEV_PLATERECPARAM *rec_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PLATEREC_PARAM(NET_CONECTION Conn,NET_DEV_PLATERECPARAM *rec_cfg ) ;

// �����ʶ������ 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ROIS_PARAM(NET_CONECTION Conn, NET_DEV_ROISPARAM *rois_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ROIS_PARAM(NET_CONECTION Conn, NET_DEV_ROISPARAM *rois_cfg) ;

// old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ROIS_PARAM_V1(NET_CONECTION Conn, NET_DEV_POLYGON *rois_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ROIS_PARAM_V1(NET_CONECTION Conn, NET_DEV_POLYGON *rois_cfg) ;



// ����ģʽ
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_WORKMODE_PARAM(NET_CONECTION Conn, NET_DEV_WORKMODE *work_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_WORKMODE_PARAM(NET_CONECTION Conn,NET_DEV_WORKMODE *work_cfg ) ;


// ��λ����
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARKSPACE_PARAM(NET_CONECTION Conn, NET_DEV_PARK_SPACELIST *parkspace_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARKSPACE_PARAM(NET_CONECTION Conn,NET_DEV_PARK_SPACELIST *parkspace_cfg ) ;


//  �ڰ���������
//  
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARK_VIP_PARAM(NET_CONECTION Conn, WhiteListMember *vip_cfg,int *vipCount) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARK_VIP_PARAM(NET_CONECTION Conn,WhiteListMember *vip_cfg,int vipCount ) ;

//old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARK_VIP_PARAM_V1(NET_CONECTION Conn, NET_VIPINFOLIST_V1 *vip_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARK_VIP_PARAM_V1(NET_CONECTION Conn,NET_VIPINFOLIST_V1 *vip_cfg ) ;


//�ѻ������������ȡ
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_OFFLINE_PARAM(NET_CONECTION Conn, NET_DEV_OFFLINE_INFO *offline_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_OFFLINE_PARAM(NET_CONECTION Conn,NET_DEV_OFFLINE_INFO *offline_cfg ) ;

//old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_OFFLINE_PARAM_V1(NET_CONECTION Conn, NET_DEV_OFFLINE_V1 *offline_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_OFFLINE_PARAM_V1(NET_CONECTION Conn,NET_DEV_OFFLINE_V1 *offline_cfg ) ;


// ����Ա����

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ADMINCARD_PARAM(NET_CONECTION Conn, NET_ADMIN_MEMBERLIST *admin_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ADMINCARD_PARAM(NET_CONECTION Conn,NET_ADMIN_MEMBERLIST *admin_cfg ) ;





// ʱ�����
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_TIME_PARAM(NET_CONECTION Conn, NET_DEV_TIME_EX *time_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_TIME_PARAM(NET_CONECTION Conn,NET_DEV_TIME_EX *time_cfg ) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_TIME_PARAM_V1(NET_CONECTION Conn, NET_DEV_TIME_EX_V1 *time_cfg);
//���ڲ������� ��������1 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_SERIAL_PARAM(NET_CONECTION Conn, NET_DEV_SERIAL_CFG *serial_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_SERIAL_PARAM(NET_CONECTION Conn,NET_DEV_SERIAL_CFG *serial_cfg ) ;

//�ƹ����
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_LIGHT_PARAM(NET_CONECTION Conn, NET_DEV_LIGHT_CFG *light_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_LIGHT_PARAM(NET_CONECTION Conn,NET_DEV_LIGHT_CFG *light_cfg ) ;


//ISP hight 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ISP_PARAM(NET_CONECTION Conn, NET_ISP_INFO *isp_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ISP_PARAM(NET_CONECTION Conn,NET_ISP_INFO *isp_cfg ) ;


//�ֶ�ץ��
EYEST_API   BOOL   EYEST_CALL  EYEST_NET_HAND_SNAP(NET_CONECTION Conn,char *userdata= NULL ) ;
EYEST_API   BOOL  EYEST_CALL   EYEST_NET_HAND_SNAP_EX(char *ipaddr ,int port,char *userdata=NULL  ) ;

// ץ�ĵ��ڴ�
EYEST_API   BOOL   EYEST_CALL  EYEST_NET_HAND_SNAP_MEM(NET_CONECTION Conn,unsigned char *pjpeg ,int bufsize ,int *nlength  ) ;

// ���������FLASH
EYEST_API   BOOL EYEST_CALL    EYEST_NET_SAVE_PARAM(NET_CONECTION Conn) ;

//�����豸
EYEST_API   BOOL  EYEST_CALL   EYEST_NET_RESTART(NET_CONECTION Conn) ;

//���ڿ���  ��͸���������ݣ�
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SERIAL_CONTROL(NET_CONECTION Conn, int  Serialno, char *controldata ,int datalen );
EYEST_API  BOOL EYEST_CALL    EYEST_NET_SERIAL_CONTROL_EX(  char *ipaddr ,int port , int  Serialno, char *controldata ,int datalen );

// ���� ��բ
EYEST_API  BOOL EYEST_CALL    EYEST_NET_IO_CONTROL(NET_CONECTION Conn, int  iono ,int state  );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_IO_CONTROL_EX(char *ipaddr ,int port , int  iono ,int state  );

//���� ��բ
EYEST_API  BOOL EYEST_CALL    EYEST_NET_IO_CLOSE_DOOR(NET_CONECTION Conn, int  iono ,int state  );
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_IO_CLOSE_DOOR_EX(char *ipaddr ,int port , int  iono ,int state  );

//���Ƶ�բ����
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_IO_CONTROL_UP(char *ipaddr ,int port , int  iono ,int state  );
//�ָ�������բ����
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_IO_CONTROL_NORMAL(char *ipaddr ,int port , int  iono ,int state  );



//�������� ��TTS�������ƣ������ַ����� ��� �����TTS ģ���ת������������
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIO_CONTROL(char *ipaddr ,int port , char *text ,int textlength  );

//��ʹ�ÿƴ�Ѷ������оƬʱ����
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIO_CONTROL_EX(NET_CONECTION Conn, char *text ,int textlength );
 

//��������
//volume  ������С  �� 0-9  
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_VOLUME_CONTROL(char *ipaddr ,int port ,int volume  );


//type = 3 ��ͨ�� //type =2 ͯ��//type =1 ����//type = 0 Ů��
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIOTYPE_CONTROL(char *ipaddr ,int port ,int type  );

//���ٿ���  �� 0-9  
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_VOICESPEED_CONTROL(char *ipaddr ,int port ,int volume  );
 
// ��ͷ���� TCP ,type = 0 ��ʼ ; type=1 ֹͣ
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_IN(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_OUT(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_IN(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_OUT(NET_CONECTION Conn,int type );

//  pos ��ʾԤ��λ�� ��1-255
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_SET(NET_CONECTION Conn,int pos );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_CALL(NET_CONECTION Conn,int pos );



// ��ͷ���� UDP
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_IN_EX(char *ipaddr ,int port,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_OUT_EX(char *ipaddr ,int port,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_IN_EX(char *ipaddr ,int port,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_OUT_EX(char *ipaddr ,int port,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_SET_EX(char *ipaddr ,int port,int pos );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_CALL_EX(char *ipaddr ,int port,int pos );

EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_AUTO_EX(char *ipaddr ,int port    );


// debug open
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_OPEN_DEBUG(char *ipaddr , NET_DEBUGVIEWCALLBACK   pFun ,void *pUser    );



 EYEST_API  BOOL   EYEST_CALL  EYEST_NET_CLOSE_DEBUG( );

//update 
 EYEST_API  BOOL   EYEST_CALL  EYEST_NET_UPDATE(char *ipaddr,char *FilePath );

 //assist focus 
 EYEST_API  int    EYEST_CALL  EYEST_GET_FOCUS_VALUE( NET_DEV_Preview Preview );

 //restore
 EYEST_API  BOOL  EYEST_CALL   EYEST_NET_RESTORE(NET_CONECTION Conn);


 EYEST_API  BOOL  EYEST_CALL   EYEST_NET_DRAW_ROI( NET_CONECTION Conn ,NET_DEV_Preview Preview ,int nEnable);

 //test

 EYEST_API  BOOL  EYEST_CALL   EYEST_NET_GET_SUPORT(int winid ,int *nHard ,int *nD3d);

 //���ó�ͷ���   CheckMode 1: ���� 0���ر�
 EYEST_API  BOOL  EYEST_CALL   EYEST_NET_SET_CARHEADCHECK(NET_CONECTION Conn ,int CheckMode);


 //��ȡ��բ��Ϣ
 // mode 1���ٶ�ȡģʽֱ�Ӵӻ����ж�ȡ��Ϣ��0����ģʽÿ�����»�ȡ��Ϣ
 // Conn ���Ӿ��
 // dest Ŀ��д�뻺��
 // destlength �������ֽ���
 // 0�ɹ����ؽ����-1 ���Ӿ������-2���ݷ���ʧ�ܣ�-3�޷����ս��(����̼���֧�ִ˹���)
/* dest��������ԭʼ��ʽ
{"addr":2,"carcnt":0,"carstatus":1,"gatestatus":3,"open":0,"ready":1,"ver":328}
{
    "addr":2,        // ��բ��ַ 0~255
    "carcnt":0,      // δ����������
    "carstatus":1,   // ��բ�·�����״̬ 1�޳� 2�г�
    "gatestatus":3,  // ��բ״̬ 1����λ 2�ص�λ 3ֹͣ״̬ 4���ڿ�բ 5���ڹ�բ
	"ip":"192.168.1.88" // ��բIP��ַ
    "open":-1,       // ��բԴ  1������2ң�أ� ������Ч
    "ready":1,       // ��բ������ָʾ  1��ʾ�����ӣ�������բ����(��֧�ִ˹��ܵ����)
    "ver":328        // ��բ�汾��
}
*/
EYEST_API  int EYEST_CALL  EYEST_NET_GATEINFO(int mode,NET_CONECTION Conn,char* dest, int destlength);



// ��բ״̬�ص�ԭ��
// jsongateΪjson�ַ�������ͬ��
typedef void ( __stdcall * NET_gate_callback)(const char* jsongate);


#ifdef __cplusplus
}
#endif


#endif 