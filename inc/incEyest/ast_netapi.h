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
	//状态回调消息
#define NET_DEV_CB_CONN_START            0
#define NET_DEV_CB_CONN_OK               1
#define NET_DEV_CB_CONN_FAIL             2
#define NET_DEV_CB_CONN_CLOSED           3
 

//搜索设备回调函数
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
	NET_DEV_IPADDR  IpAddr; // IP地址
	WORD  Port;   // 端口号
	char  UserName[NET_DEV_USERNAME_LEN]; // 用户名
	char  PassWord[NET_DEV_PASSWORD_LEN]; // 密码
	BOOL  AutoReconnect;   // 是否自动连接 
	BOOL  EventDesired;    // 是否报警上报
	int   TimeOut;   // 超时时间
	void* UserParam;
	HWND hWnd;
	UINT Message;
	NET_EVENTCALLBACK EventCallback;
	NET_CONSTAUSCALLBACK StatusCallback;
	NET_SMARTRECVCALLBACK     spaceresultcallback;
	NET_SMARTRECVCALLBACKV1 spaceresultcallbackv1;
	NET_SMARTRECVCALLBACK_EX     spaceresultcallbackex;
	NET_MISC_CALLBACK                     misccallback ;
	NET_gate_callback			gatestatuscallback; // 新增道闸状态改变回调函数 2018.09.25

}NET_CONPARAM;


typedef  LONG  NET_CONECTION;

//视频预览

// 视频数据回调 
typedef void ( EYEST_CALL   * NET_PREVIEWDATACALLBACK)(unsigned char * Frame,  int  framelength ,  int width ,int height ,int  frametype ,void* UserParam);


typedef void ( EYEST_CALL   * NET_DECODEDATACALLBACK)(unsigned char * Frame,  int  width ,int height  ,void* UserParam);

// 预览状态回调
typedef void (  EYEST_CALL   * NET_PREVIEWSTAUSCALLBACK)(WORD Code, HWND hWnd, UINT Msg, void* UserParam);

//调试回调
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
	UINT Channel;       // 通道号 0,1,2,3...
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
	UINT  TimeOut;     //超时时间 s
}NET_DEV_QueryDeviceStateParam;

//参数配置
 
typedef struct _NET_GET_PARAM
{
	UINT Channel; // 通道号
	UINT ParamID;   //NET_DEV_PARAM_ID
	BYTE  OutBuffer[1024*128];  // 获取到的数据
	UINT  ReturnedSize;  // 获取到的数据大小
	UINT  TimeOut;     //超时时间 s
}NET_GET_PARAM;
 
 
typedef struct _NET_SET_PARAM 
{
	UINT Channel;
	UINT ParamID;   //NET_DEV_PARAM_ID
	BYTE InBuffer[1024*128];
	UINT  InBufferSize;
	UINT  TimeOut;      //超时时间 s
}NET_SET_PARAM;

// CU 代表 客户端   PU 代表 设备端
//初始化
EYEST_API  BOOL    EYEST_CALL  EYEST_NET_INIT();
// 反初始化
EYEST_API  void    EYEST_CALL  EYEST_NET_RELEASE();



EYEST_API  BOOL  EYEST_CALL   EYEST_NET_INITSERVER(UINT port );


// 注册事件回调
EYEST_API  BOOL   EYEST_CALL  EYEST_REGISTER_EVENTCALLBACK(NET_EVENTCALLBACK  pFun,void *userparam) ;

// 注册智能检测结果回调
EYEST_API  BOOL  EYEST_CALL  EYEST_REGISTER_SMARTCALLBACK(NET_SMARTRECVCALLBACK pFun,void *userparam) ;

//注册回调 （精简的注识别结果注册回调）
EYEST_API  BOOL EYEST_CALL  EYEST_REGISTER_SMARTCALLBACK_EX(NET_SMARTRECVCALLBACK_EX pFun,void *userparam) ;

// 注册状态回调
EYEST_API  BOOL EYEST_CALL  EYEST_REGISTER_STATECALBACK(NET_CONSTAUSCALLBACK  pFun,void *userparam) ;


EYEST_API  BOOL  EYEST_CALL EYEST_REGISTER_IODATACALLBACK(NET_CONECTION Conn,NET_IO_DATACALLBACK  pFun,void *userparam); 


//获取错误码
EYEST_API  UINT   EYEST_CALL  EYEST_NET_GET_LEYEST_ERROR();
//搜索设备
EYEST_API  void  EYEST_CALL   EYEST_NET_SEARCH_DEV(const NET_SEARCHPARAM* Param);

//搜索设置设备IP信息
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SET_DEV_INFO(const NET_DEV_MODIFY_NET* Param);

//设备连接
EYEST_API  NET_CONECTION   EYEST_CALL   EYEST_NET_LOGIN(const NET_CONPARAM* Param );


// new 
EYEST_API  NET_CONECTION   EYEST_CALL   EYEST_NET_GET_DEVICETYYPE(NET_CONECTION Conn );



//退出连接
EYEST_API  void  EYEST_CALL   EYEST_NET_LOGOUT(NET_CONECTION Conn);

//订阅告警,订阅后NET_EVENTCALLBACK中才会有告警数据
EYEST_API  void  EYEST_CALL    EYEST_NET_ALARM_SUBSCRIBE(NET_CONECTION Conn, BOOL Desired);


//视频预览
EYEST_API  NET_DEV_Preview  EYEST_CALL   EYEST_NET_START_PREVIEW(NET_CONECTION Conn
												 , const NET_PREVIEWPARAM* Param);

//停止视频预览
EYEST_API  void   EYEST_CALL   EYEST_NET_STOP_PREVIEW(NET_CONECTION Conn,NET_DEV_Preview Preview);


// 获取一帧解码后的RGB数据，方便用户做配置显示使用 ，仅当视频预览打开后可以获取到数据
//需要 自己传入 一段内存建议 1920*1080*3 
EYEST_API  void   EYEST_CALL  EYEST_NET_GET_PREVIEW_RGB( NET_DEV_Preview Preview,char *rgb ,int *width ,int *height );
 

//参数配置
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_GET_PARAM(NET_CONECTION Conn, const NET_GET_PARAM* Param);
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SET_PARAM(NET_CONECTION Conn, const NET_SET_PARAM* Param);

//网络参数获取设置值
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_NET_PARAM(NET_CONECTION Conn, NET_DEV_CFG_NET *net_cfg) ;
EYEST_API  BOOL  EYEST_CALL  EYEST_NET_SET_NET_PARAM(NET_CONECTION Conn,NET_DEV_CFG_NET *net_cfg ) ;


// 设备基本参数获取

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_BASE_PARAM(NET_CONECTION Conn, NET_DEV_CAMBASEINFO *base_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_BASE_PARAM(NET_CONECTION Conn,NET_DEV_CAMBASEINFO *base_cfg ) ;

// for old version  
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_BASE_PARAM_V1(NET_CONECTION Conn, NET_DEV_CAMBASEINFO_V1 *base_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_BASE_PARAM_V1(NET_CONECTION Conn,NET_DEV_CAMBASEINFO_V1 *base_cfg ) ;



//CMS 平台参数
EYEST_API  BOOL  EYEST_CALL  EYEST_NET_GET_CMS_PARAM(NET_CONECTION Conn, NET_DEV_CMS_CFG *cms_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_CMS_PARAM(NET_CONECTION Conn,NET_DEV_CMS_CFG *cms_cfg ) ;


// 图像参数

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_IMG_PARAM(NET_CONECTION Conn, NET_DEV_VIDEO_INPUT_EFFECT *img_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_IMG_PARAM(NET_CONECTION Conn,NET_DEV_VIDEO_INPUT_EFFECT *img_cfg ) ;




// 高级图像参数 ，3A
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_3A_PARAM(NET_CONECTION Conn, NET_DEV_CAMERACFG *img3a_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_3A_PARAM(NET_CONECTION Conn,NET_DEV_CAMERACFG *img3a_cfg ) ;

// for old versions
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_3A_PARAM_V1(NET_CONECTION Conn, NET_DEV_CAMERACFG_V1 *img3a_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_3A_PARAM_V1(NET_CONECTION Conn,NET_DEV_CAMERACFG_V1 *img3a_cfg ) ;


//图像编码参数
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ENCODE_PARAM(NET_CONECTION Conn, NET_DEV_ENCODECFG *encode_cfg) ;
EYEST_API  BOOL EYEST_CALL   EYEST_NET_SET_ENCODE_PARAM(NET_CONECTION Conn,NET_DEV_ENCODECFG *encode_cfg ) ;

 
// 识别参数  <old >
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PLATEREC_PARAM(NET_CONECTION Conn, NET_DEV_PLATERECPARAM *rec_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PLATEREC_PARAM(NET_CONECTION Conn,NET_DEV_PLATERECPARAM *rec_cfg ) ;

// 多边形识别区域 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ROIS_PARAM(NET_CONECTION Conn, NET_DEV_ROISPARAM *rois_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ROIS_PARAM(NET_CONECTION Conn, NET_DEV_ROISPARAM *rois_cfg) ;

// old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ROIS_PARAM_V1(NET_CONECTION Conn, NET_DEV_POLYGON *rois_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ROIS_PARAM_V1(NET_CONECTION Conn, NET_DEV_POLYGON *rois_cfg) ;



// 工作模式
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_WORKMODE_PARAM(NET_CONECTION Conn, NET_DEV_WORKMODE *work_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_WORKMODE_PARAM(NET_CONECTION Conn,NET_DEV_WORKMODE *work_cfg ) ;


// 车位参数
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARKSPACE_PARAM(NET_CONECTION Conn, NET_DEV_PARK_SPACELIST *parkspace_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARKSPACE_PARAM(NET_CONECTION Conn,NET_DEV_PARK_SPACELIST *parkspace_cfg ) ;


//  黑白名单参数
//  
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARK_VIP_PARAM(NET_CONECTION Conn, WhiteListMember *vip_cfg,int *vipCount) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARK_VIP_PARAM(NET_CONECTION Conn,WhiteListMember *vip_cfg,int vipCount ) ;

//old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_PARK_VIP_PARAM_V1(NET_CONECTION Conn, NET_VIPINFOLIST_V1 *vip_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_PARK_VIP_PARAM_V1(NET_CONECTION Conn,NET_VIPINFOLIST_V1 *vip_cfg ) ;


//脱机参数设置与获取
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_OFFLINE_PARAM(NET_CONECTION Conn, NET_DEV_OFFLINE_INFO *offline_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_OFFLINE_PARAM(NET_CONECTION Conn,NET_DEV_OFFLINE_INFO *offline_cfg ) ;

//old version
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_OFFLINE_PARAM_V1(NET_CONECTION Conn, NET_DEV_OFFLINE_V1 *offline_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_OFFLINE_PARAM_V1(NET_CONECTION Conn,NET_DEV_OFFLINE_V1 *offline_cfg ) ;


// 管理员卡号

EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ADMINCARD_PARAM(NET_CONECTION Conn, NET_ADMIN_MEMBERLIST *admin_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ADMINCARD_PARAM(NET_CONECTION Conn,NET_ADMIN_MEMBERLIST *admin_cfg ) ;





// 时间参数
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_TIME_PARAM(NET_CONECTION Conn, NET_DEV_TIME_EX *time_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_TIME_PARAM(NET_CONECTION Conn,NET_DEV_TIME_EX *time_cfg ) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_TIME_PARAM_V1(NET_CONECTION Conn, NET_DEV_TIME_EX_V1 *time_cfg);
//串口参数设置 ，仅串口1 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_SERIAL_PARAM(NET_CONECTION Conn, NET_DEV_SERIAL_CFG *serial_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_SERIAL_PARAM(NET_CONECTION Conn,NET_DEV_SERIAL_CFG *serial_cfg ) ;

//灯光控制
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_LIGHT_PARAM(NET_CONECTION Conn, NET_DEV_LIGHT_CFG *light_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_LIGHT_PARAM(NET_CONECTION Conn,NET_DEV_LIGHT_CFG *light_cfg ) ;


//ISP hight 
EYEST_API  BOOL EYEST_CALL  EYEST_NET_GET_ISP_PARAM(NET_CONECTION Conn, NET_ISP_INFO *isp_cfg) ;
EYEST_API  BOOL EYEST_CALL  EYEST_NET_SET_ISP_PARAM(NET_CONECTION Conn,NET_ISP_INFO *isp_cfg ) ;


//手动抓拍
EYEST_API   BOOL   EYEST_CALL  EYEST_NET_HAND_SNAP(NET_CONECTION Conn,char *userdata= NULL ) ;
EYEST_API   BOOL  EYEST_CALL   EYEST_NET_HAND_SNAP_EX(char *ipaddr ,int port,char *userdata=NULL  ) ;

// 抓拍到内存
EYEST_API   BOOL   EYEST_CALL  EYEST_NET_HAND_SNAP_MEM(NET_CONECTION Conn,unsigned char *pjpeg ,int bufsize ,int *nlength  ) ;

// 保存参数到FLASH
EYEST_API   BOOL EYEST_CALL    EYEST_NET_SAVE_PARAM(NET_CONECTION Conn) ;

//重启设备
EYEST_API   BOOL  EYEST_CALL   EYEST_NET_RESTART(NET_CONECTION Conn) ;

//串口控制  （透明串口数据）
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_SERIAL_CONTROL(NET_CONECTION Conn, int  Serialno, char *controldata ,int datalen );
EYEST_API  BOOL EYEST_CALL    EYEST_NET_SERIAL_CONTROL_EX(  char *ipaddr ,int port , int  Serialno, char *controldata ,int datalen );

// 控制 开闸
EYEST_API  BOOL EYEST_CALL    EYEST_NET_IO_CONTROL(NET_CONECTION Conn, int  iono ,int state  );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_IO_CONTROL_EX(char *ipaddr ,int port , int  iono ,int state  );

//控制 关闸
EYEST_API  BOOL EYEST_CALL    EYEST_NET_IO_CLOSE_DOOR(NET_CONECTION Conn, int  iono ,int state  );
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_IO_CLOSE_DOOR_EX(char *ipaddr ,int port , int  iono ,int state  );

//控制道闸长开
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_IO_CONTROL_UP(char *ipaddr ,int port , int  iono ,int state  );
//恢复正常道闸控制
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_IO_CONTROL_NORMAL(char *ipaddr ,int port , int  iono ,int state  );



//语音控制 ，TTS语音控制，发送字符串到 相机 ，相机TTS 模块会转换成语音播放
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIO_CONTROL(char *ipaddr ,int port , char *text ,int textlength  );

//不使用科大讯飞语音芯片时调用
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIO_CONTROL_EX(NET_CONECTION Conn, char *text ,int textlength );
 

//音量控制
//volume  音量大小  从 0-9  
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_VOLUME_CONTROL(char *ipaddr ,int port ,int volume  );


//type = 3 卡通声 //type =2 童声//type =1 男声//type = 0 女声
EYEST_API  BOOL  EYEST_CALL   EYEST_NET_AUDIOTYPE_CONTROL(char *ipaddr ,int port ,int type  );

//语速控制  从 0-9  
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_VOICESPEED_CONTROL(char *ipaddr ,int port ,int volume  );
 
// 镜头控制 TCP ,type = 0 开始 ; type=1 停止
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_IN(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_ZOOM_OUT(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_IN(NET_CONECTION Conn,int type );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_FOCUS_OUT(NET_CONECTION Conn,int type );

//  pos 表示预置位号 从1-255
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_SET(NET_CONECTION Conn,int pos );
EYEST_API  BOOL   EYEST_CALL  EYEST_NET_LENS_PRESET_CALL(NET_CONECTION Conn,int pos );



// 镜头控制 UDP
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

 //设置车头检测   CheckMode 1: 开启 0：关闭
 EYEST_API  BOOL  EYEST_CALL   EYEST_NET_SET_CARHEADCHECK(NET_CONECTION Conn ,int CheckMode);


 //获取道闸信息
 // mode 1快速读取模式直接从缓存中读取信息，0慢速模式每次重新获取信息
 // Conn 连接句柄
 // dest 目标写入缓存
 // destlength 缓存中字节数
 // 0成功返回结果，-1 连接句柄错误，-2数据发送失败，-3无法接收结果(相机固件不支持此功能)
/* dest返回数据原始样式
{"addr":2,"carcnt":0,"carstatus":1,"gatestatus":3,"open":0,"ready":1,"ver":328}
{
    "addr":2,        // 道闸地址 0~255
    "carcnt":0,      // 未过车辆计数
    "carstatus":1,   // 道闸下发车辆状态 1无车 2有车
    "gatestatus":3,  // 道闸状态 1开到位 2关到位 3停止状态 4正在开闸 5正在关闸
	"ip":"192.168.1.88" // 道闸IP地址
    "open":-1,       // 开闸源  1按键，2遥控， 其他无效
    "ready":1,       // 道闸已连接指示  1表示已连接，其他道闸离线(或不支持此功能的相机)
    "ver":328        // 道闸版本号
}
*/
EYEST_API  int EYEST_CALL  EYEST_NET_GATEINFO(int mode,NET_CONECTION Conn,char* dest, int destlength);



// 道闸状态回调原型
// jsongate为json字符串定义同上
typedef void ( __stdcall * NET_gate_callback)(const char* jsongate);


#ifdef __cplusplus
}
#endif


#endif 