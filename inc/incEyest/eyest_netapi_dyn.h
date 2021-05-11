//��̬���ú�����

#ifndef EYEST_NETAPI_DYN_H
#define EYEST_NETAPI_DYN_H
#endif


#include "eyest_public.h"
	////////////////////////////////////////////////////////////////////////
//	״̬�ص���Ϣ
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
			strcpy (UserName ,"admin") ;
			strcpy (PassWord ,"12345") ;
			AutoReconnect = 0;
			TimeOut = 10*1000;
			EventCallback =NULL;
			StatusCallback = NULL;
			spaceresultcallback = NULL;
			spaceresultcallbackex = NULL;
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
		NET_SMARTRECVCALLBACK_EX     spaceresultcallbackex;
	}NET_CONPARAM;



	typedef  LONG  NET_CONECTION;

//	��ƵԤ��

	// ��Ƶ���ݻص� 
	typedef void (__stdcall   * NET__PREVIEWDATACALLBACK)(unsigned char * Frame,  int  framelength ,  int width ,int height ,int  frametype ,void* UserParam);


	typedef void (__stdcall   * NET_DECODEDATACALLBACK)(unsigned char * Frame,  int  width ,int height  ,void* UserParam);

	// Ԥ��״̬�ص�
	typedef void  (__stdcall   * NET_PREVIEWSTAUSCALLBACK)(WORD Code, HWND hWnd, UINT Msg, void* UserParam);

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
		}
		UINT Channel;       // ͨ���� 0,1,2,3...
		BYTE StreamType;     // NET_DEV_STREAM_TYPE
		BYTE Content;       // NET_DEV_STREAM_MIX_TYPE
		UINT Protol;         // NET_DEV_TRANSPROTOL
		int      VideoPort ;
		BOOL AutoReconnect;
		void* UserParam;
		HWND hWnd;
		UINT Message;
		NET__PREVIEWDATACALLBACK DataCallback;
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
	typedef  BOOL    (WINAPI*  NET_INIT_DYN)();
	// ����ʼ��
	typedef  void    (WINAPI*  NET_RELEASE_DYN)();



	typedef  BOOL  (WINAPI*   NET_INITSERVER_DYN)(UINT port );


	// ע���¼��ص�
	typedef  BOOL   (WINAPI*  REGISTER_EVENTCALLBACK_DYN) (NET_EVENTCALLBACK  pFun,void *userparam) ;

	// ע�����ܼ�����ص�
	typedef  BOOL  (WINAPI*  REGISTER_SMARTCALLBACK_DYN) (NET_SMARTRECVCALLBACK pFun,void *userparam) ;

	//ע��ص� �������עʶ����ע��ص���
	typedef  BOOL (WINAPI*  REGISTER_SMARTCALLBACK_EX_DYN) (NET_SMARTRECVCALLBACK_EX pFun,void *userparam) ;

	// ע��״̬�ص�
	typedef  BOOL (WINAPI*  REGISTER_STATECALBACK_DYN) (NET_CONSTAUSCALLBACK  pFun,void *userparam) ;
	//��ȡ������
	typedef  UINT   (WINAPI*  NET_GET_LAST_ERROR_DYN) ();
	//�����豸
	typedef  void  (WINAPI*   NET_SEARCH_DEV_DYN) (const NET_SEARCHPARAM* Param);

	//���������豸IP��Ϣ
	typedef  BOOL   (WINAPI*  NET_SET_DEV_INFO_DYN) (const NET_DEV_MODIFY_NET* Param);

	//�豸����
	typedef  NET_CONECTION   (WINAPI*   NET_LOGIN_DYN) (const NET_CONPARAM* Param );

	//�˳�����
	typedef  void  (WINAPI*   NET_LOGOUT_DYN) (NET_CONECTION Conn);

	//���ĸ澯,���ĺ�NET_EVENTCALLBACK�вŻ��и澯����
	typedef  void  (WINAPI*    NET_ALARM_SUBSCRIBE_DYN) (NET_CONECTION Conn, BOOL Desired);


	//��ƵԤ��
	typedef  NET_DEV_Preview  (WINAPI*   NET_START_PREVIEW_DYN) (NET_CONECTION Conn
		, const NET_PREVIEWPARAM* Param);
	//ֹͣ��ƵԤ��
	typedef  void   (WINAPI*   NET_STOP_PREVIEW_DYN) (NET_CONECTION Conn,NET_DEV_Preview Preview);


	// ��ȡһ֡������RGB���ݣ������û���������ʾʹ�� ��������ƵԤ���򿪺���Ի�ȡ������
	//��Ҫ �Լ����� һ���ڴ潨�� 1920*1080*3 
	typedef  void   (WINAPI*  NET_GET_PREVIEW_RGB_DYN) ( NET_DEV_Preview Preview,char *rgb ,int *width ,int *height );


	//��������
	typedef  BOOL  (WINAPI*   NET_GET_PARAM_DYN) (NET_CONECTION Conn, const NET_GET_PARAM* Param);
	typedef  BOOL   (WINAPI*  NET_SET_PARAM_DYN) (NET_CONECTION Conn, const NET_SET_PARAM* Param);

	//���������ȡ����ֵ
	typedef  BOOL (WINAPI*  NET_GET_NET_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_CFG_NET *net_cfg) ;
	typedef  BOOL  (WINAPI*  NET_SET_NET_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_CFG_NET *net_cfg ) ;


	// �豸����������ȡ

	typedef  BOOL (WINAPI*  NET_GET_BASE_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_CAMBASEINFO *base_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_BASE_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_CAMBASEINFO *base_cfg ) ;


	//CMS ƽ̨����
	typedef  BOOL  (WINAPI*  NET_GET_CMS_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_CMS_CFG *cms_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_CMS_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_CMS_CFG *cms_cfg ) ;


	// ͼ�����

	typedef  BOOL (WINAPI*  NET_GET_IMG_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_VIDEO_INPUT_EFFECT *img_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_IMG_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_VIDEO_INPUT_EFFECT *img_cfg ) ;


	// �߼�ͼ����� ��3A

	typedef  BOOL (WINAPI*  NET_GET_3A_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_CAMERACFG *img3a_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_3A_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_CAMERACFG *img3a_cfg ) ;


	//ͼ��������
	typedef  BOOL (WINAPI*  NET_GET_ENCODE_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_ENCODECFG *encode_cfg) ;
	typedef  BOOL (WINAPI*   NET_SET_ENCODE_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_ENCODECFG *encode_cfg ) ;


	// ʶ�����
	typedef  BOOL (WINAPI*  NET_GET_PLATEREC_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_PLATERECPARAM *rec_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_PLATEREC_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_PLATERECPARAM *rec_cfg ) ;


	// ����ģʽ
	typedef  BOOL (WINAPI*  NET_GET_WORKMODE_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_WORKMODE *work_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_WORKMODE_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_WORKMODE *work_cfg ) ;




	// ��λ����
	typedef  BOOL (WINAPI*  NET_GET_PARKSPACE_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_PARK_SPACELIST *parkspace_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_PARKSPACE_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_PARK_SPACELIST *parkspace_cfg ) ;


	//  �ڰ���������
	//  
	typedef  BOOL (WINAPI*  NET_GET_PARK_VIP_PARAM_DYN) (NET_CONECTION Conn, NET_VIPINFOLIST *vip_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_PARK_VIP_PARAM_DYN) (NET_CONECTION Conn,NET_VIPINFOLIST *vip_cfg ) ;

	//�ѻ������������ȡ

	typedef  BOOL (WINAPI*  NET_GET_OFFLINE_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_OFFLINE_INFO *offline_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_OFFLINE_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_OFFLINE_INFO *offline_cfg ) ;






	//��ӻ����޸İ�������������ݺͰ��������в�һ�����޸ģ�
	//����1  ��ӳɹ� ����0 �Ѵ��ڣ�-1 ʧ�ܣ� 
	typedef  int  (WINAPI*  NET_ADD_PARK_VIP_DYN) (NET_CONECTION Conn,NET_VIPINFO   *m_netvipinfo ) ;

	// ���ݳ��ƺ�ɾ���ڰ�����
	typedef  BOOL (WINAPI*  NET_DEL_PARK_VIP_DYN) (NET_CONECTION Conn, char *platenum  ) ;

	// ʱ�����
	typedef  BOOL (WINAPI*  NET_GET_TIME_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_TIME_EX *time_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_TIME_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_TIME_EX *time_cfg ) ;

	//���ڲ������� ��������1 
	typedef  BOOL (WINAPI*  NET_GET_SERIAL_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_SERIAL_CFG *serial_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_SERIAL_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_SERIAL_CFG *serial_cfg ) ;

	//�ƹ����
	typedef  BOOL (WINAPI*  NET_GET_LIGHT_PARAM_DYN) (NET_CONECTION Conn, NET_DEV_LIGHT_CFG *light_cfg) ;
	typedef  BOOL (WINAPI*  NET_SET_LIGHT_PARAM_DYN) (NET_CONECTION Conn,NET_DEV_LIGHT_CFG *light_cfg ) ;




	//�ֶ�ץ��
	typedef   BOOL   (WINAPI*  NET_HAND_SNAP_DYN) (NET_CONECTION Conn,char *userdata ) ;
	typedef   BOOL  (WINAPI*   NET_HAND_SNAP_EX_DYN) (char *ipaddr ,int port,char *userdata  ) ;

	// ץ�ĵ��ڴ�
	typedef   BOOL   (WINAPI*  NET_HAND_SNAP_MEM_DYN) (NET_CONECTION Conn,unsigned char *pjpeg ,int bufsize ,int *nlength  ) ;

	// ���������FLASH
	typedef   BOOL (WINAPI*    NET_SAVE_PARAM_DYN) (NET_CONECTION Conn) ;

	//�����豸
	typedef   BOOL  (WINAPI*   NET_RESTART_DYN) (NET_CONECTION Conn) ;



	//���ڿ���  ��͸���������ݣ�
	typedef  BOOL   (WINAPI*  NET_SERIAL_CONTROL_DYN) (NET_CONECTION Conn, int  Serialno, char *controldata ,int datalen );
	typedef  BOOL (WINAPI*    NET_SERIAL_CONTROL_EX_DYN) (  char *ipaddr ,int port , int  Serialno, char *controldata ,int datalen );




	// ���� ��բ
	typedef  BOOL (WINAPI*    NET_IO_CONTROL_DYN) (NET_CONECTION Conn, int  iono ,int state  );

	typedef  BOOL   (WINAPI*  NET_IO_CONTROL_EX_DYN) (char *ipaddr ,int port , int  iono ,int state  );

	//���� ��բ
	typedef  BOOL  (WINAPI*   NET_IO_CLOSE_DOOR_DYN) (char *ipaddr ,int port , int  iono ,int state  );

	//���Ƶ�բ����
	typedef  BOOL   (WINAPI*  NET_IO_CONTROL_UP_DYN) (char *ipaddr ,int port , int  iono ,int state  );
	//�ָ�������բ����
	typedef  BOOL  (WINAPI*   NET_IO_CONTROL_NORMAL_DYN) (char *ipaddr ,int port , int  iono ,int state  );



	//�������� ��TTS�������ƣ������ַ����� ��� �����TTS ģ���ת������������
	typedef  BOOL  (WINAPI*   NET_AUDIO_CONTROL_DYN) (char *ipaddr ,int port , char *text ,int textlength  );
	//��������
	//volume  ������С  �� 0-9  
	typedef  BOOL   (WINAPI*  NET_VOLUME_CONTROL_DYN) (char *ipaddr ,int port ,int volume  );
	//type = 3 ��ͨ�� //type =2 ͯ��//type =1 ����//type = 0 Ů��
	typedef  BOOL  (WINAPI*   NET_AUDIOTYPE_CONTROL_DYN) (char *ipaddr ,int port ,int type  );

	//���ٿ���  �� 0-9  
	typedef  BOOL   (WINAPI*  NET_VOICESPEED_CONTROL_DYN) (char *ipaddr ,int port ,int volume  );

	typedef  BOOL    (WINAPI* NET_GET_POLYGON_PARAM)   (NET_CONECTION Conn,NET_POLYGON_PARAM *rec_cfg );

	typedef  BOOL    (WINAPI* NET_SET_POLYGON_PARAM)   (NET_CONECTION Conn,NET_POLYGON_PARAM *rec_cfg );



//����������

extern NET_INIT_DYN   EYEST_NET_INIT;
extern NET_RELEASE_DYN   EYEST_NET_RELEASE; 
extern NET_INITSERVER_DYN    EYEST_NET_INITSERVER;
extern REGISTER_EVENTCALLBACK_DYN    EYEST_REGISTER_EVENTCALLBACK;
extern REGISTER_SMARTCALLBACK_DYN    EYEST_REGISTER_SMARTCALLBACK;
extern REGISTER_SMARTCALLBACK_EX_DYN    EYEST_REGISTER_SMARTCALLBACK_EX;
extern REGISTER_STATECALBACK_DYN    EYEST_REGISTER_STATECALBACK;
extern NET_GET_LAST_ERROR_DYN    EYEST_NET_GET_LAST_ERROR;
extern NET_SEARCH_DEV_DYN    EYEST_NET_SEARCH_DEV;
extern NET_SET_DEV_INFO_DYN    EYEST_NET_SET_DEV_INFO;
extern NET_LOGIN_DYN    EYEST_NET_LOGIN;
extern NET_LOGOUT_DYN    EYEST_NET_LOGOUT;
extern NET_ALARM_SUBSCRIBE_DYN    EYEST_NET_ALARM_SUBSCRIBE;
extern NET_START_PREVIEW_DYN    EYEST_NET_START_PREVIEW;
extern NET_STOP_PREVIEW_DYN    EYEST_NET_STOP_PREVIEW;
extern NET_GET_PREVIEW_RGB_DYN    EYEST_NET_GET_PREVIEW_RGB;
extern NET_GET_PARAM_DYN    EYEST_NET_GET_PARAM;
extern NET_SET_PARAM_DYN    EYEST_NET_SET_PARAM;
extern NET_GET_NET_PARAM_DYN    EYEST_NET_GET_NET_PARAM;
extern NET_SET_NET_PARAM_DYN    EYEST_NET_SET_NET_PARAM;
extern NET_GET_BASE_PARAM_DYN    EYEST_NET_GET_BASE_PARAM;
extern NET_SET_BASE_PARAM_DYN    EYEST_NET_SET_BASE_PARAM;
extern NET_GET_CMS_PARAM_DYN    EYEST_NET_GET_CMS_PARAM;
extern NET_SET_CMS_PARAM_DYN  EYEST_NET_SET_CMS_PARAM;
extern NET_GET_IMG_PARAM_DYN    EYEST_NET_GET_IMG_PARAM;
extern NET_SET_IMG_PARAM_DYN    EYEST_NET_SET_IMG_PARAM;
extern NET_GET_3A_PARAM_DYN    EYEST_NET_GET_3A_PARAM;
extern NET_SET_3A_PARAM_DYN      EYEST_NET_SET_3A_PARAM;
extern NET_GET_ENCODE_PARAM_DYN      EYEST_NET_GET_ENCODE_PARAM;
extern NET_SET_ENCODE_PARAM_DYN      EYEST_NET_SET_ENCODE_PARAM;
extern NET_GET_PLATEREC_PARAM_DYN      EYEST_NET_GET_PLATEREC_PARAM;
extern NET_SET_PLATEREC_PARAM_DYN      EYEST_NET_SET_PLATEREC_PARAM;
extern NET_GET_WORKMODE_PARAM_DYN      EYEST_NET_GET_WORKMODE_PARAM;
extern NET_SET_WORKMODE_PARAM_DYN      EYEST_NET_SET_WORKMODE_PARAM;
extern NET_GET_PARKSPACE_PARAM_DYN      EYEST_NET_GET_PARKSPACE_PARAM;
extern NET_SET_PARKSPACE_PARAM_DYN      EYEST_NET_SET_PARKSPACE_PARAM;
extern NET_GET_PARK_VIP_PARAM_DYN       EYEST_NET_GET_PARK_VIP_PARAM;
extern NET_SET_PARK_VIP_PARAM_DYN       EYEST_NET_SET_PARK_VIP_PARAM;
extern NET_GET_OFFLINE_PARAM_DYN       EYEST_NET_GET_OFFLINE_PARAM;
extern NET_SET_OFFLINE_PARAM_DYN       EYEST_NET_SET_OFFLINE_PARAM;
extern NET_ADD_PARK_VIP_DYN   EYEST_NET_ADD_PARK_VIP;
extern  NET_DEL_PARK_VIP_DYN  EYEST_NET_DEL_PARK_VIP;
extern  NET_GET_TIME_PARAM_DYN  EYEST_NET_GET_TIME_PARAM;
extern  NET_SET_TIME_PARAM_DYN   EYEST_NET_SET_TIME_PARAM;
extern  NET_GET_SERIAL_PARAM_DYN  EYEST_NET_GET_SERIAL_PARAM;
extern  NET_SET_SERIAL_PARAM_DYN  EYEST_NET_SET_SERIAL_PARAM;
extern  NET_GET_LIGHT_PARAM_DYN   EYEST_NET_GET_LIGHT_PARAM;
extern  NET_SET_LIGHT_PARAM_DYN   EYEST_NET_SET_LIGHT_PARAM;
extern  NET_HAND_SNAP_DYN  EYEST_NET_HAND_SNAP;
extern  NET_HAND_SNAP_EX_DYN  EYEST_NET_HAND_SNAP_EX;
extern  NET_HAND_SNAP_MEM_DYN   EYEST_NET_HAND_SNAP_MEM;
extern  NET_SAVE_PARAM_DYN   EYEST_NET_SAVE_PARAM;
extern  NET_RESTART_DYN   EYEST_NET_RESTART;
extern  NET_SERIAL_CONTROL_DYN   EYEST_NET_SERIAL_CONTROL;
extern  NET_SERIAL_CONTROL_EX_DYN   EYEST_NET_SERIAL_CONTROL_EX;
extern  NET_IO_CONTROL_DYN   EYEST_NET_IO_CONTROL;
extern  NET_IO_CONTROL_EX_DYN   EYEST_NET_IO_CONTROL_EX;
extern  NET_IO_CLOSE_DOOR_DYN  EYEST_NET_IO_CLOSE_DOOR;
extern  NET_IO_CONTROL_UP_DYN  EYEST_NET_IO_CONTROL_UP;
extern  NET_IO_CONTROL_NORMAL_DYN  EYEST_NET_IO_CONTROL_NORMAL;
extern  NET_AUDIO_CONTROL_DYN  EYEST_NET_AUDIO_CONTROL;
extern  NET_VOLUME_CONTROL_DYN  EYEST_NET_VOLUME_CONTROL;
extern  NET_AUDIOTYPE_CONTROL_DYN  EYEST_NET_AUDIOTYPE_CONTROL;
extern  NET_VOICESPEED_CONTROL_DYN  EYEST_NET_VOICESPEED_CONTROL;
extern NET_GET_POLYGON_PARAM EYEST_NET_GET_POLYGON_PARAM;
extern NET_SET_POLYGON_PARAM EYEST_NET_SET_POLYGON_PARAM;

extern HMODULE gle_hDll;  //����DLLģ����

extern void IniDllFun();//��ʼ��DLL����

extern void FreeDll();//�ͷ�DLL