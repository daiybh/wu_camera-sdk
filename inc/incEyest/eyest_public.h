#ifndef DT_STRUCT_H
#define DT_STRUCT_H


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


	//全局宏定义
	//-------------------------------------------------------------------
#define NET_DEV_DEVICE_NAME_LEN   32  //设备名字长度
#define NET_DEV_IPV4_ADDR_LEN     16  //IPV4地址长度
#define NET_DEV_IPV6_ADDR_LEN     48  //IPV6地址长度
#define NET_DEV_MAC_ADDR_LEN      20  //MAC地址长度

#define NET_DEV_MAX_USER_NUM      16  //最大用户个数
#define NET_DEV_USERNAME_LEN      32  //用户名长度
#define NET_DEV_PASSWORD_LEN      16  //密码长度

#define NET_DEV_MAX_STREAM_NUM    3   //最大码流个数
#define  NET_DEV_MAX_ALARM_IN_NUM   1 // 报警输入
#define NET_DEV_MAX_ALARM_OUT_NUM  1  //报警输出


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
	//全局错误码定义
	//-------------------------------------------------------------------


#define NET_DEV_ERROR_SUCCESS              0   //没有错误
#define NET_DEV_ERROR_TIMEOUT              1   //操作超时
#define NET_DEV_ERROR_FAILED               2   //操作失败
#define NET_DEV_ERROR_PASSWORD             3   //用户名密码错误
#define NET_DEV_ERROR_MAX_USERNUM          4  //设备端用户数达到最大
#define NET_DEV_ERROR_NOENOUGHPRI          5  //权限不足


	//全局枚举定义

	// 设备类型
	typedef enum _NET_DEV_TYPE
	{
		NET_DEV_TYPE_IPC  = 0x00,
		NET_DEV_TYPE_SMARTIPC  = 0x01,
		NET_DEV_TYPE_NVR  = 0x02,
		NET_DEV_TYPE_SMARTNVR  = 0x03,
		NET_DEV_TYPE_BUTT
	}NET_DEV_TYPE;

	//传输协议
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



	//控制
	//------------------------------------------------------------


	typedef enum _DT_PARAM_CMD_E_
	{
		DT_STABLE_PARAM = 0x00,	// 0设备出厂信息
		DT_BASEPARAM    	 = 0x01,	// 1设备基本信息
		DT_NET_PARAM,          	// 2设备网络配置
		DT_VIDEO_PARAM,			// 3设备视频参数 
		DT_VMAIN_PARAM,			// 4 设备视频主码流参数
		DT_VSUB_PARAM,		    	// 5 设备视频次码流参数
		DT_VTHREE_PARAM,       	// 6设备第三码流参数
		DT_VCAP_PARAM,		    	// 7 设备视频抓拍参数
		DT_IMA_PARAM,		    	// 8 设备图像参数
		DT_3A_PARAM,		    	// 9 设备3A参数
		DT_USR_PARAM,		    	// 10 用户参数配置
		DT_PF_PARAM,           	// 11 平台信息
		DT_NTP_PARAM,		    	// 12ntp参数配置
		DT_PLATE_PARAM  ,               //13 plate 
		DT_CAR_PARAM  ,               //14 CAR
		DT_VD_PARAM  ,               //15 detect
		DT_WORKMODE_PARAM, //16  工作方式
		DT_VIP_PARAM  ,             // 17 VIP INFO
		DT_PARKSPACE_PARAM,
		DT_SERIAL_CONTROL,//串口控制
		DT_CHECK_TIME,  //矫正时间
		DT_SERIAL_INFO,//串口配置
		DT_LIGHT_PARAM ,
		DT_OFFLINE_PIARAM,//23
        DT_POLYGON_PARAM

	}DT_PARAM_CMD_E;


	// 设备网络参数 
	typedef struct _NET_DEV_CFGNET
	{
		NET_DEV_IPADDR IPAddr;		//设备IP
		NET_DEV_IPADDR Netmask;		//子网掩码
		NET_DEV_IPADDR Gateway;		//网关
		char MACAddr[NET_DEV_MAC_ADDR_LEN];		//MAC地址
		unsigned char  EnableDHCP;		//是否启用DHCP
		unsigned char  EnableAutoDNS;		//是否允许自动获取DNS
		unsigned char  Mtu;				//MTU大小默认 1500
		unsigned char  Interface;		//网络接口 1-10MBase-T 2-10MBase-T全双工 3-100MBase-TX 4-100M全双工 5-10M/100M/1000M自适应
		NET_DEV_IPADDR DNS1;		//主DNS服务器地址
		NET_DEV_IPADDR DNS2;		//次DNS服务器地址
	}NET_DEV_CFG_NET;




	typedef struct _NET_DEV_ETHCFG
	{
		unsigned char  NICCount;		//设备支持的以太网卡个数(只读)
		unsigned char  Res[3];		//保留
		NET_DEV_CFG_NET EthNICs[NET_DEV_MAX_ETH_NICS];
	}NET_DEV_ETHCFG;

	typedef  struct _NET_DEV_SERVICECFG
	{
		int  MsgPort;		//设备信令端口
		int RtspPort;		//设备RTSP端口
		int HttpPort;		//设备HTTP端口
		int RtmpPort;		//设备RTMP端口
	}NET_DEV_SERVICECFG;



	//===================================================================

	//搜索设备信息
	//-------------------------------------------------------------------


	typedef struct _NET_DEV_BROARDSEARCHINFO
	{
		long    timeflag ;
		char  SoftwareVer[NET_DEV_VERSION_LEN];
		char  HardwareVer[NET_DEV_VERSION_LEN];
		char  SerialNo[NET_DEV_SERIAL_NO_LEN];		// 序列号
		unsigned char  DevType;		// NET_DEV_TYPE
		char  ProductName[NET_DEV_DEVICE_NAME_LEN];		//产品型号
		char  DeviceName[NET_DEV_DEVICE_NAME_LEN] ;
		char  DeviceID[NET_DEV_DEVICE_NAME_LEN] ;
		NET_DEV_ETHCFG EthCfg;
		NET_DEV_SERVICECFG ServiceCfg;
	}NET_DEV_BROARDSEARCHINFO;




	//搜索修改网络配置
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
	//设备能力集信息
	//-------------------------------------------------------------------

	typedef enum _NET_DEV_SYS_CAP
	{
		DEV_SYS_CAP_PTZ      = 0,   // 云台
		DEV_SYS_CAP_WIFI     = 1,   // WIFI
		DEV_SYS_CAP_3G       = 2,   // 3G
		DEV_SYS_CAP_IVS      = 3,  // 智能分析
		DEV_SYS_CAP_IR       = 4   // 红外
	}NET_DEV_SYS_CAP;


	// 智能分析能力
	typedef enum _NET_DEV_IVS_CAP
	{
		NET_DEV_IVS_BRIGHT_ABMNL_CAP        = 1,  // 亮度异常
		NET_DEV_IVS_CLARITY_ABMNL_CAP       = 2,  // 清晰度异常
		NET_DEV_IVS_NOISE_ABMNL_CAP         = 3,  // 噪声异常
		NET_DEV_IVS_COLOR_ABMNL_CAP         = 4,  // 颜色异常
		NET_DEV_IVS_SCENE_CHANGE_CAP        = 5,  // 场景变换,人为干扰
		NET_DEV_IVS_TRIP_WIRE_CAP           = 6,  // 单绊线
		NET_DEV_IVS_DOUBLE_TRIP_WIRE_CAP    = 7,  // 双绊线
		NET_DEV_IVS_PERI_METER_CAP          = 8,  // 警戒区
		NET_DEV_IVS_LOITER_CAP              = 9,  // 徘徊检测
		NET_DEV_IVS_LEFT_CAP                = 10, // 物品遗留
		NET_DEV_IVS_TAKE_CAP                = 11, // 物品丢失
		NET_DEV_IVS_TAKE_PLATEREC         = 12, // 车牌识别
		NET_DEV_IVS_CARREC         = 13, // 车辆识别
		NET_DEV_IVS_CARTRACK         = 14, // 车辆跟踪
	}NET_DEV_IVS_CAP;





	//通道能力
	typedef struct _NET_DEV_CH_CAPABILITIES
	{
		unsigned char  VideoEncType;		// 支持的视频编码集 NET_DEV_VENC_TYPE
		unsigned char  AudioEncType;		// 支持的音频编码集 NET_DEV_AENC_TYPE
		unsigned char  OsdCount;		// OSD个数
		unsigned char  LostAlarm;		// 是否支持视频丢失报警
		unsigned char  StreamCount;		// 码流个数
		unsigned long  Resolution[NET_DEV_MAX_STREAM_NUM];		//支持的分辨率集 掩码 NET_DEV_IMAGERESOLUTION
		unsigned long  FPS[NET_DEV_MAX_STREAM_NUM];		//支持的最大帧率集 数值表示支持的最大帧率值

	}NET_DEV_CH_CAPABILITIES;


	typedef struct _NET_DEV_CAPABILITIES
	{
		/*------- system -----*/
		char ProductName[NET_DEV_DEVICE_NAME_LEN];//产品型号
		unsigned char  DevType;		// 设备类型 NET_DEV_TYPE
		unsigned char  EncChnCount;		// 编码通道个数
		unsigned char  DecChnCount;		// 解码通道个数
		unsigned char  AudioInCount;		// 语音输入个数
		unsigned char  AudioOutCount;		// 语音输出个数
		unsigned char  AlarmInCount;		// 报警输入个数
		unsigned char  AlarmOutCount;		// 报警输出个数
		unsigned char  Rs232Count;		// RS232串口个数
		unsigned char  Rs485Count;		// RS485串口个数
		unsigned char  EthCount;		// 网络口个数
		unsigned char  DiskCount;		// 硬盘口个数
		unsigned char  VoutCount;		// 视频输出口的个数
		unsigned char  UsbCount;		// USB口的个数
		int   IvsCap;		// 智能分析能力 NET_DEV_IVS_CAP
		int Res1[2];		// 保留
		/*--------------------*/
		NET_DEV_CH_CAPABILITIES ChannelCap;		//通道能力
	}NET_DEV_CAPABILITIES;


	//===================================================================
	//设备版本信息
	//===================================================================


	typedef struct _NET_DEV_VERSION
	{
		int DevType;		// 设备类型： NET_DEV_TYPE
		char ProductName[NET_DEV_DEVICE_NAME_LEN];		//产品型号
		char SerialNo[NET_DEV_SERIAL_NO_LEN];		// 序列号
		char SoftwareVer[NET_DEV_VERSION_LEN];		// 软件版本号
		char SoftwareDate[NET_DEV_DATE_LEN];		// 软件生成日期
		char DspSoftwareVer[NET_DEV_VERSION_LEN];		// DSP软件版本
		char DspSoftwareDate[NET_DEV_DATE_LEN];		// DSP软件生成日期
		char HardwareVer[NET_DEV_VERSION_LEN];		// 硬件版本

	}NET_DEV_VERSION;





	typedef struct _NET_DEV_CMS_CFG
	{
		unsigned long  Enable;		//是否开启
		char  PuId[NET_DEV_ID_LEN];		//设备ID
		char  PuAC[NET_DEV_AUTHORIZECODE_LEN];		//设备授权码
		NET_DEV_IPADDR CmsIP;		//服务器IP
		NET_DEV_IPADDR MdsIP;		//流媒体IP
		unsigned short  CmsPort;		//服务器端口
		unsigned short  MdsPort;		//流媒体端口
		unsigned short  State;		//连接状态，1-CMS已连接  0-未连接
	}NET_DEV_CMS_CFG;



	//===================================================================
	//设备时间配置
	//===================================================================



	typedef struct _NET_DEV_TIME_EX
	{
		unsigned long  Zone;		//时区
		unsigned short  Year;		//年
		unsigned char  Month;		//月
		unsigned char  Day;		//日
		unsigned char  Week;		//星期
		unsigned char  Hour;		//时
		unsigned char  Minute;		//分
		unsigned char  Second;		//秒
		unsigned long  MilliSec;		//毫秒
	}NET_DEV_TIME_EX;



	typedef struct _NET_DEV_NTPCFG
	{
		unsigned long  EnableNTP;		//是否开启: 0：不开启，1：NTP对时，2：CMS对时
		unsigned long  EnableDST;		//夏令时使能；1：启用，0：不启用
		NET_DEV_IPADDR NTPServer;		//NTP服务器
		unsigned long  TimeZone;		//时区
		unsigned long  UpdateInterval;		//对时间隔
	}NET_DEV_NTPCFG;



	//===================================================================
	//编码参数
	//===================================================================
	//码流类型
	typedef enum _NET_DEV_STREAM_TYPE
	{
		NET_DEV_STREAM_MAIN = 0,
		NET_DEV_STREAM_SECOND,
		NET_DEV_STREAM_THIRD
	}NET_DEV_STREAM_TYPE;

	//视频编码类型
	typedef enum _NET_DEV_VENC_TYPE
	{
		NET_DEV_VENC_H264   = 0x00,
		NET_DEV_VENC_MJPEG  = 0x01,
		NET_DEV_VENC_JPEG   = 0x02,
		NET_DEV_VENC_MPEG4  = 0x03,
		NET_DEV_VENC_H265   = 0x04,
		NET_DEV_VENC_BUTT
	}NET_DEV_VENC_TYPE;

	//音频编码类型
	typedef enum _NET_DEV_AENC_TYPE
	{
		NET_DEV_AENC_G711A = 0x00,
		NET_DEV_AENC_G711U = 0x01,
		NET_DEV_AENC_G726  = 0x02,
		NET_DEV_AENC_BUTT
	}NET_DEV_AENC_TYPE;


	//码流类型
	typedef enum _NET_DEV_VENC_BITRATE_TYPE
	{
		NET_DEV_BT_ABR = 0,
		NET_DEV_BT_CBR,
		NET_DEV_BT_VBR,
		NET_DEV_BT_FIXQP,
		NET_DEV_BT_BUTT
	}NET_DEV_VENC_BITRATE_TYPE;

	// 264 编码等级
	typedef enum _NET_DEV_ENCODELEVEL
	{
		NET_DEV_EL_BASELINE = 0,
		NET_DEV_EL_MAIN,
		NET_DEV_EL_HIGH
	}NET_DEV_ENCODELEVEL;


	//分辨率类型
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




	//编码参数 
	typedef  struct _NET_DEV_ENCODEPARAM
	{
		unsigned long  Resolution;
		unsigned long  EncodeLevel;		//编码等级 'NET_DEV_ENCODELEVEL'
		unsigned long  StreamMixType;		//码流模式NET_DEV_STREAM_MIX_TYPE
		unsigned long  FrameRate;		//帧率 数值型 常用值：5，10, 15, 20, 25, 30
		unsigned long  IsFrameRatePreferred;		//是否帧率优先 1: 是, 0: 不是
		unsigned long  IframeInterval;		//I帧间隔 数值型 常用值: 25，50，75，100
		unsigned long  VideoEncodeType;		//视频编码类型, NET_DEV_VENC_TYPE
		unsigned long  ImageResolution;		//图像分辨率 'NET_DEV_IMAGERESOLUTION'
		unsigned long  QPValue;		//质量  数值型 常用值：25，50
		unsigned long  BitRateType;		//位率类型 'NET_DEV_VENC_BITRATE_TYPE'
		unsigned long  BitRate;		//位率 128k ~ 8000k
		unsigned long  AudioInputMode;		//音频输入类型 'NET_DEV_AUDIOINPUTMODE'
		unsigned long  AudioEncodeType;		//音频编码类型 'NET_DEV_AENC_TYPE'
	}NET_DEV_ENCODEPARAM;

	typedef  struct _NET_DEV_ENCODECFG
	{
		NET_DEV_ENCODEPARAM Main;		//主码流    编码参数
		NET_DEV_ENCODEPARAM Second;		//子码流    编码参数
		NET_DEV_ENCODEPARAM Third;		//第三码流  编码参数
	}NET_DEV_ENCODECFG;

	//===================================================================
	//图像效果参数
	//===================================================================
	typedef struct _NET_DEV_VIDEO_EFFECT
	{
		unsigned long  Contrast;		//对比度
		unsigned long  Bright;		//亮度
		unsigned long  Hue;		//灰度
		unsigned long  Saturation;		//饱和度
		unsigned long  Sharpness;		//锐度
	}NET_DEV_VIDEO_EFFECT;


	typedef  struct _NET_DEV_VIDEO_INPUT_EFFECT
	{
		unsigned long  EffectMode;		//模式,0:用户定义, 1: 默认值
		NET_DEV_VIDEO_EFFECT CustomizeMode;		//自定义模式参数
	}NET_DEV_VIDEO_INPUT_EFFECT;

	//===================================================================
	//外设
	//================================================

	//串口参数
	typedef struct _NET_DEV_SERIAL_CFG
	{

		unsigned char  WorkMode;		//工作模式: 0 －透明通道, 1 - PTZ 模式(使用PTZ中的串口参数), 
		unsigned char  BaudRate;		//串口波特率  (0-8) 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 600
		unsigned char  DataBit;		//数据位 5, 6, 7, 8
		unsigned char  StopBit;		//停止位 1, 2
		unsigned char  Verify;		//校验位 0:无，1:奇校验 2:偶校验
		unsigned char  FlowControl;		//流控 0－无，1－软流控, 2-硬流控
		unsigned char   unused[22]; //   

	}NET_DEV_SERIAL_CFG;


	typedef struct _NET_LIGHT_CFG
	{
		int  light ;
	}NET_DEV_LIGHT_CFG;



	typedef struct  _NET_DEV_OFFLINE_INFO
	{
		// 声音设置  固定
		int   voicetype ;   
		int   voicespeed ;  //语速
		int   voicevolume ; //音量
		char  szvoice_in[64] ;   // 固定语音入口
		char  szvoice_out[64] ; //固定语音出口
		char  szvoice_none[64] ; // 固定语音 无属性
		// 固定
		int    screenshowtype ;
		char szscreen_adv[64] ; // 广告
		char szscreen_in[64] ; //固定 屏幕输出
		char szscreen_out[64] ; //
		char szscreen_none[64] ;

		int     useip[6] ;
		char  leaveipaddr [6][16] ;

		int         freetime; //  免费时间 单位(分) 
		float      moneyfee ; //every 30 minite fee  费率 ，每30分钟费率

		int          autoopendoor ;
		char       unused[32] ;

	}NET_DEV_OFFLINE_INFO;




	//==============================================
	//告警配置
	//==============================================

	typedef struct _NET_DEV_ALARM_ITEM
	{
		unsigned long  Channel;         //告警图像通道
		unsigned long  AlarmType;		//告警类型
		unsigned long  Action;		//0：开始告警，1：结束告警
		unsigned long  Time;
		unsigned char  Data[NET_DEV_ALARM_DATA_SIZE];	  //告警描述
	}NET_DEV_ALARM_ITEM;


	//用户信息
	//---------------------------------------
	//用户权限


	typedef enum _NET_DEV_USER_REMOTERIGHT
	{
		NET_DEV_USER_RR_PTZ_CTL = 0,/*远程控制云台*/
		NET_DEV_USER_RR_REC_MANUL,  /*远程手动录象*/
		NET_DEV_USER_RR_REC_PLAY,   /*远程回放 */
		NET_DEV_USER_RR_PARAM_SET,  /*远程设置参数*/
		NET_DEV_USER_RR_PARAM_GET,  /*远程查看参数 */
		NET_DEV_USER_RR_ADVANCED,   /*远程高级操作(升级，格式化)*/
		NET_DEV_USER_RR_LOG_STATE,  /*远程查看状态、日志*/
		NET_DEV_USER_RR_REAL_TALK,  /*远程发起语音对讲*/
		NET_DEV_USER_RR_REAL_PLAY,  /*远程预览*/
		NET_DEV_USER_RR_ALARMOUT,   /*远程请求报警上传、报警输出*/
		NET_DEV_USER_RR_VIDEOOUT,   /*远程控制，本地输出*/
		NET_DEV_USER_RR_RS232_TRNS, /*远程控制串口*/
		NET_DEV_USER_RR_CHANNEL,    /*远程管理模拟和IP camera */
		NET_DEV_USER_RR_POWEROFF,   /*远程关机/重启 */
	}NET_DEV_USER_REMOTERIGHT;



	typedef struct _NET_DEV_USER_INFO
	{
		char  UserName[NET_DEV_USERNAME_LEN];		//用户名
		char  PassWord[NET_DEV_PASSWORD_LEN];		//密码
		unsigned long  RemoteRight;		//远程操作权限掩码 NET_DEV_USER_REMOTERIGHT
		unsigned long  Reserve;		//保留 
	}NET_DEV_USER_INFO;


	typedef struct _NET_DEV_USER_MODIFY
	{
		char  OldUserName[NET_DEV_USERNAME_LEN];		// 旧用户名
		char  OldPassWord[NET_DEV_PASSWORD_LEN];		// 旧用户名
		char  NewUserName[NET_DEV_USERNAME_LEN];		// 新用户名
		char  NewPassWord[NET_DEV_PASSWORD_LEN];		// 新密码
		unsigned long  RemoteRight;		// 远程操作权限掩码
		unsigned long  Reserve;
	}NET_DEV_USER_MODIFY;


	typedef struct _NET_DEV_CAMERAPARAM
	{
		unsigned long  Mirror;		//镜像(图像左右调换) 1 镜像 0 不镜像
		unsigned long  Flip;		//翻转(图像上下调换) 1 翻转 0 不翻转
		unsigned long  WdrMode;		//宽动态模式 0自动   1 打开 2 关闭
		unsigned long  WdrStreng;		//0-255为宽动态强度

		unsigned long  DeNoiseLevel;		//降噪等级 0--关闭 1--低 2--中 3--高

		unsigned long  Rotate;		//旋转：0 无    1 旋转90度    2 旋转270度
		unsigned long  Shutter;		//电子快门 0-9  0：自动快门 1：1/25S， 2：1/50S， 3：1/100S， 4: 1/200S 5：1/500S， 6：1/1000S， 7：1/2000S， 8：1/5000S， 9：1/10000S

		unsigned long  AwbMode;		//白平衡模式 0 自动1 室内 2室外 3自动跟踪 4 手动
		unsigned long  AwbRed;		//白平衡红色
		unsigned long  AwbBlue;		//白平衡蓝色
		unsigned long  Blc;		//背光补偿0 关闭 1 打开
		unsigned long  AEMinTime;		//自动曝光最小曝光时间,自动快门时有效：0：不限,1：1/25S，2：1/50S，3：1/100S，4: 1/200S，5：1/500S，6：1/1000S，7：1/2000S，8：1/5000S，9：1/10000S
		unsigned long  AEMaxTime;		//自动曝光最大曝光时间,同AEMinTime,且应>=AEMinTime
		unsigned long  AGain;		//自动增益(0-255)
		unsigned long   DGain;
		unsigned long   AVGLight;  // 期望亮度

		unsigned long    Brightness;//亮度
		unsigned long    Contrast ;//对比度
		unsigned long    Sturation ;//饱和度
		unsigned long      Hue ;//色调
		unsigned long       Sharpness;	



	}NET_DEV_CAMERAPARAM;



	typedef struct _NET_DEV_CAMERACFG
	{
		unsigned long  CameraMode;		// 0: 用户自定义， 1：默认值
		NET_DEV_CAMERAPARAM CameraParam;		//用户自定义
	}NET_DEV_CAMERACFG;



	typedef struct _NET_DEV_CAMERABASEINFO
	{
		char     DevName[NET_DEV_DEVICE_NAME_LEN] ; // 设备名称
		char     DevId[NET_DEV_DEVICE_NAME_LEN-1] ;      // 设备ID号
		char      DevType ;
	}NET_DEV_CAMBASEINFO;




	typedef  struct _NET_DEV_OSD_TEXT
	{
		unsigned long   TextType ;// OSD类型
		unsigned long  TextEnable;		//是否显示文本；1：显示，0：隐藏
		unsigned long  TextX;		//文本坐标X
		unsigned long  TextY;		//文本坐标Y
		unsigned long  TextW;		//文本宽度(获取有效)
		unsigned long  TextH;		//文本高度(获取有效)
		char  TextData[NET_DEV_OSD_TEXT_LEN];
	}NET_DEV_OSD_TEXT;



	typedef struct _NET_SNAP_OSD
	{
		unsigned long  DisplayAttr;		//osd 反色；1：开启，0：关闭
		unsigned long  DisplayColor;		//osd显示颜色
		unsigned long  MaxWidth;		//最大宽度
		unsigned long  MaxHeight;		//最大高度
		NET_DEV_OSD_TEXT Texts[NET_DEV_OSD_TEXT_NUM];
	}NET_DEV_SNAP_OSD;




	//状态信息
	//------------------------------------------------------------
	typedef enum _NET_DEV_STATE_IDX
	{
		NET_DEV_STATE_NETWORK   = 0,    //NET_DEV_NETSTATES 
		NET_DEV_STATE_WORKS     = 1,    //NET_DEV_WORKSTATE
		NET_DEV_STATE_IVS     = 2,    // 智能分析状态
	}NET_DEV_STATE_IDX;


	//------------------- IVS 结构定义 -------------------
#define NET_DEV_MAX_POLYGON_POINT_NUM         8   //多边形最大顶点个数
#define NET_DEV_MAX_OBJECT_NUM              16   //最大目标数
#define NET_DEV_MAX_TRACK_NUM              16   //最大跟踪目标数
#define NET_DEV_MAX_REC_PLATE_NUM         4   //最大车牌识别数
#define NET_DEV_MAX_RECT_NUM            4  //最大矩形个数


#define  MAX_SPACE                   3  //最大车位数

	// 点

	typedef struct _NET_DEV_POINT
	{
		unsigned short  X;
		unsigned short  Y;
	}NET_DEV_POINT;


	// 线

	typedef struct _NET_DEV_LINE
	{
		NET_DEV_POINT Start;
		NET_DEV_POINT End;
	}NET_DEV_LINE;


	// 多边形
	typedef struct _NET_DEV_POLYGON
	{
		unsigned long  Count;		//多边形顶点数
		NET_DEV_POINT Points[NET_DEV_MAX_POLYGON_POINT_NUM];		//多边形点坐标
	}NET_DEV_POLYGON;

	// 矩形
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


	// 车牌识别参数结构

	typedef struct _NET_DEV_PLATERECPARAM
	{
		NET_DEV_RECT  recrect;//识别区域
		int                       samefilter ; 
		int                       platesize ;
		int                       recidx;
        int                       platekind; //需要识别的车牌类型
		int                       province; //默认省份编码

	}NET_DEV_PLATERECPARAM;


#define MAXPOINT    8

	typedef struct _RV_POINT
    {
        int x ;
        int y ;
    
	} RV_POINT ;


    typedef struct
	{
       
        int  pointnum ;
        
		RV_POINT  m_point[MAXPOINT] ;

	}
    NET_POLYGON_PARAM;



	// 工作模式
	typedef struct _NET_DEV_WORKMODE
	{
		int   workmode ; // 0 地感线圈触发 1 虚拟线圈触发 2 视频识别
		// 说明:虚拟线圈方式是检测到有运动后抓拍一张识别，
		//视频识别 是对识别区域进行逐帧策略识别，抓拍最优结果
		int    filterplate ; //1 过滤无牌车辆  0,不过滤 默认不过滤
		int     filterdirection;
		unsigned char  useinside;  //使用内部控制
		unsigned char  camtype  ;// 入口1 出口2
		unsigned char  unuesd[6] ;
	}NET_DEV_WORKMODE;


#define  MAXVIPCOUNT        20000

	typedef  struct _NET_VIPINFO  // 20 byte 
	{
		char  szplatenum[13] ;
		unsigned char     startyear ;
		unsigned char     startmonth ;
		unsigned char     startday ;
		unsigned char     endyear ;
		unsigned char     endmonth ;
		unsigned char     endday ;

		unsigned char      viptype; // 0 表示白名单 ，1 表示黑名单

	}NET_VIPINFO;

	// 最大 1024 个VIP    20 *1024   = 20K 
	typedef  struct _NET_VIPINFOLIST
	{
		int    m_vipcount ;
		NET_VIPINFO   m_netvipinfo[MAXVIPCOUNT] ;
	}NET_VIPINFOLIST;





	// 车牌识别结果
	typedef struct _NET_DEV_PLATERESUT
	{
		char   platenum[16]; //车牌号码
		char   platecolor[8]; //车牌颜色
		float   platereal ;  //车牌置信度
		NET_DEV_RECT platerect ; // 车牌像素位置
	}NET_DEV_PLATERESULT;


	// 车辆识别参数结构

	typedef struct _NET_DEV_CARRECPARAM
	{
		int  maxsize ; //车辆最大像素宽度
		int  minsize  ; //车辆最小像素宽度
	}NET_DEV_CARRECPARAM;




	typedef struct _NET_DEV_CARRECRESULT
	{
		NET_DEV_RECT carrect ; // 车辆像素位置
		char                  carcolor[8];//车身颜色
		//char                  carmodel[128] ;//车型信息
		//float                  carfeature[1024]; //车辆特征码
	}NET_DEV_CARRECRESULT;


	//车位参数
	typedef struct _NET_DEV_PARK_SPACEINFO
	{
		char    spaceinfo[32];  // 车位信息 ，唯一标识
		NET_DEV_RECT   spacerect;//车位在图像中矩形位置
	}NET_DEV_PARK_SPACEINFO;

	// 相机对应车位参数列表
	typedef struct _NET_DEV_PARK_SPACELIST
	{
		int        spacecount ; // 对应车位数目
		NET_DEV_PARK_SPACEINFO   spacerectinfo[MAX_SPACE];//车位在图像中矩形位置
	}NET_DEV_PARK_SPACELIST;



#define   RV_PLATELEN   16
#define   RV_COLORLEN   8
#define   RV_VTYPELEN    256



#define   RV_MAXLETTER    12

	// 车牌识别结构体
	typedef struct _tagRv_AnprRsult
	{
		char 	platenum[RV_PLATELEN];//## plate num   GB2312
		char platecolor[RV_COLORLEN] ;//## plate color GB2312
		char carcolor[RV_COLORLEN] ;//## plate color GB2312
		int   platecolorindex ;  //##  plate color index 
		float  	platereliability ;  // ## plate realbility 
		float        plateletterreal[RV_MAXLETTER] ; // letter realbility 
		RECT  	platerect ;    // ## plate position  left  top right bottom  
		char     cartype[RV_VTYPELEN]; 	//## car type  (if rec this ,just support BGR mode,only support x86 now )
		float    cartypereliability ;  //## car type   realbility 
		float     vertangle;//##  plate vert angle 
		float      horzangle ;//##plate  horz angle 
	}RV_ANPRRESULT, *PRV_ANPRRESULT;


	typedef struct _NET_DEV_REC_RESUT
	{
		unsigned char    spacestatus ; //车位状态		
		NET_DEV_CARRECRESULT carrecresult; //车辆信息
		char                   spaceid[32] ;
		RV_ANPRRESULT   plateresult; //车牌信息
	}NET_DEV_REC_RESUT;


	//图片长度最大值
#define NET_DEV_MAX_PIC_SIZE (1024*1024)

	//相机车位识别结果列表
	typedef struct _NET_DEV_SMARTRESUTLIST 
	{
		int   smartmode ;// 类型  0 出入口相机抓拍，1 车位检测
		int    spacecount ; // 车位个数 
		NET_DEV_TIME_EX      checktime;  //车牌、车辆识别的时间
		NET_DEV_CAMBASEINFO    cambase;  //  相机唯一信息
		NET_DEV_IPADDR  DevIP;    //设备IP      
		NET_DEV_REC_RESUT  parkspaceresult[MAX_SPACE];
		int    imgwidth ;  //增加图片高度  宽度 ，方便解码前内存分派
		int    imgheight ;
		int     piclength;   //图片长度
	}NET_DEV_SMARTRECRESUTLIST;

	//精简结构体
	typedef struct  
	{
		char     camerIp[16];//相机IP地址  16字节字符串
		char     DevName[32] ; // 设备名称  32字节字符串
		char     DevId[32] ;      // 设备ID号  32字节字符串
		char   	platenum[16];//车牌颜色    16字节字符串   GB2312编码方式
		char     platecolor[8] ;//车牌号码   8字节字符串   GB2312编码方式


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
	}NET_DEV_SMARTRECRESUT_EX;


	// 设备状态
	typedef struct _NET_DEV_WORKSTATE
	{
		unsigned long  DeviceState;		// 设备的状态：0－正常；1－CPU占用率太高，超过85%；
		unsigned char  AlarmInState[NET_DEV_MAX_ALARM_IN_NUM];		//报警输入口的状态：0-没有报警；1-有报警
		unsigned char  AlarmOutState[NET_DEV_MAX_ALARM_OUT_NUM];		//报警输出口的状态：0-没有输出，1-有报警输出
		unsigned long  LocalDisplayState;		//本地显示状态：0-正常，1-不正常
	}NET_DEV_WORKSTATE;


	typedef struct _NET_DEV_STATUS
	{
		NET_DEV_IPADDR deviceipaddr; //设备IP信息
		NET_DEV_CAMBASEINFO deviceinfo; // 设备基本信息(包括ID，名称等)
		UINT   status; //状态字，上线，离线
	}NET_DEV_STATUS;



	typedef struct  
	{
		char  ipaddr[16] ;//16字节 字符串 相机IP地址
		int   status ;   //4字节 整形    0表示 离线  1 表示上线
	}NET_DEV_STATUS_EX;



	////参数ID定义
	//----------------------------------------------------

	typedef enum _NET_DEV_PARAM_ID
	{
		NET_DEV_PARAM_VERSION             = 1,  // NET_DEV_VERSION            设备出厂信息 v1
		NET_DEV_PARAM_BASECFG             = 2,  // NET_DEV_BASECFG            设备基础信息 v1
		NET_DEV_PARAM_TIME                = 3,  // NET_DEV_TIME_EX            系统时间信息 v1
		NET_DEV_PARAM_NET                 = 4,  // NET_DEV_ETHCFG             网络信息     v1
		NET_DEV_PARAM_SERVICECFG          = 5,  // NET_DEV_SERVICECFG         网络服务端口 v1
		NET_DEV_PARAM_USER_QUERY          = 6,  // NET_DEV_USERSET            用户信息查询 v1
		NET_DEV_PARAM_MODIFY_USER_CFG     = 7,  // NET_DEV_USER_MODIFY        修改用户信息 v1
		NET_DEV_PARAM_USER_ADD            = 8,  // NET_DEV_USER_INFO          增加用户(带权限)   v1
		NET_DEV_PARAM_USER_DEL            = 9,  // NET_DEV_USER               删除用户(用户名称) v1
		NET_DEV_PARAM_VIDEOIN_EFFECT      = 10, // NET_DEV_VIDEO_INPUT_EFFECT 视频输入参数 v1           CHN
		NET_DEV_PARAM_CAMERA_CFG          = 11, // NET_DEV_CAMERACFG          图像参数     v1           CHN
		NET_DEV_PARAM_ENCODECFG           = 12, // NET_DEV_ENCODECFG          编码参数     v1           CHN                  CHN
		NET_DEV_PARAM_PLATEREC            =13,//_NET_DEV_CARRECPARAM车牌识别参数
		NET_DEV_PARAM_CARREC            =14,//_NET_DEV_CARRECPARAM车辆识别参数
		NET_DEV_PARAM_OSDCFG          =15, //NET_DEV_SNAP_OSD  OSD 信息
		NET_DEV_PARAM_DEVICEINFO          =16,    // 设备信息设置NET_DEV_CAMBASEINFO 
		NET_DEV_PARAM_CMS_CFG             = 100, // NET_DEV_CMS_CFG            平台信息
		NET_DEV_PARAM_MAX
	}NET_DEV_PARAM_ID;


	//消息定义
	//----------------------------------------------------



	//用户登录请求
	typedef struct _NET_DEV_LOGIN_REQ
	{
		NET_DEV_USER_INFO User;		// 用户名，密码
		unsigned long  KeepAliveTime;		// 心跳周期 单位 s
	}NET_DEV_LOGIN_REQ;


	//相机返回登录消息
	typedef struct _NET_DEV_LOGIN_RSP
	{
		NET_DEV_USER_INFO UserInfo;		// 用户信息(包括权限)
		int            status ;   //登录状态
	}NET_DEV_LOGIN_RSP;



	// 心跳包 这里发送一个时间信息
	typedef struct _NET_DEV_KEEPALIVE_RSP
	{
		NET_DEV_TIME_EX TimeEx;		// 系统时间
	}NET_DEV_KEEPALIVE_RSP;


	typedef struct _NET_DEV_STATE_QUERY_REQ
	{
		unsigned long  StateType;		//NET_DEV_STATE_IDX
	}NET_DEV_STATE_QUERY_REQ;



	typedef  struct _NET_DEV_STATE_QUERY_RSP
	{
		unsigned long  StateType;		//NET_DEV_STATE_IDX
		NET_DEV_WORKSTATE WorkState;
	}NET_DEV_STATE_QUERY_RSP;



	//  外触发器配置参数
	typedef struct _NET_DEV_TRIGER
	{
		int   trigertype ;  //触发器类型 0 本机IO  1 网络设备,2串口设备
		char  ipaddr ;
		int    port  ;
	}NET_DEV_TRIGER;



	//////////////////////////////////////////////////////////////////////////

	//设备连接

	// 报警回调
	typedef void ( __stdcall * NET_EVENTCALLBACK)(const NET_DEV_ALARM_ITEM *Report, void* UserParam);

	//状态回掉函数
	typedef void ( __stdcall* NET_CONSTAUSCALLBACK)(NET_DEV_STATUS *status, void* UserParam);

	// 精简的状态回调 
	typedef void ( __stdcall* NET_CONSTAUSCALLBACK_EX)(char  *ipaddr ,int status);



	//智能检测状态回调函数 
	// 这里为了减少数据拷贝，修改回调函数，
	//参数改为 0 图像头部数据，1 图像jpeg数据，2 图像jpeg长度，3 用户数据
	typedef void ( __stdcall * NET_SMARTRECVCALLBACK)( NET_DEV_SMARTRECRESUTLIST *SmartResult, char *pJpeg ,int *nLength , char *userdata ,void* UserParam);


	// 精简的识别结果回调函数 
	typedef void ( __stdcall * NET_SMARTRECVCALLBACK_EX)( NET_DEV_SMARTRECRESUT_EX *SmartResultEx, char *pJpeg ,int *nLength , char *userdata ,void* UserParam);

    // IO板回传数据回调函数
	typedef void ( __stdcall* NET_IO_DATACALLBACK)(char* pData ,int *nLength, int address);


//DLL里的相机登录结构体，此处用来根据连接句柄获取IP地址用
typedef struct  _net_dev_instance
{

	char ipaddr[16];
	int    port  ;
	int    clientsock ;

	int   clientsockpic ; //  图片接收


	int      autoconnecttimes ; // 自动连接时间间隔

	BYTE  UserName[NET_DEV_USERNAME_LEN]; // 用户名
	BYTE  PassWord[NET_DEV_PASSWORD_LEN]; // 密码


	BOOL  AutoReconnect;   // 是否自动连接 
	BOOL  beautothread ;        // 自动连接线程是否启动
	BOOL  beautopicthread;         // 自动连接线程是否 pic  

	BOOL   beconnected ;  // 连接是否成功
	BOOL   bepicconnected ;  // 连接是否成功 图片接收



	HANDLE   hAutoconHandle ; // 自动链接线程句柄
	HANDLE   hAutoExit ;    // 自动连接线程退出EVENT


	HANDLE   hAutoconPicHandle ; // 自动链接线程句柄
	HANDLE   hAutoPicExit ;    // 自动连接线程退出EVENT



	HANDLE   hRecvHandle ;
	HANDLE   hRecvExit ;
	BOOL       berecvthread  ;// 接收线程是否创建

	HANDLE  hKeepAliveHandle ;
	HANDLE   hAliveExit ;


	HANDLE  hKeepAlivePicHandle ;
	HANDLE   hAlivePicExit ;


	BOOL     bekeepalive ;

	BOOL   bekeepalivepic ;


	BOOL  EventDesired;    // 是否报警上报
	UINT  TimeOut;   // 超时时间
	void* UserParam;   // 用户信息
	void * UserParamVZ;
	void  *VZLogInInfo ;
	unsigned char *pjpegmem ;

	NET_EVENTCALLBACK EventCallback; // 事件回掉
	HWND hWnd;              // 窗口句柄
	UINT Message;           
	NET_CONSTAUSCALLBACK StatusCallback; //状态回掉
	NET_SMARTRECVCALLBACK     spaceresultcallback; // 结果回掉
	NET_SMARTRECVCALLBACK_EX  spaceresultcallbackex ;//
	//VZ_CAPCALLFUN                               m_vzcallback ;
	//NET_MISC_CALLBACK                       m_misccallback ;
	_net_dev_instance()
	{
		port = 8088;
		clientsock= -1;
		autoconnecttimes =5;
		AutoReconnect = 0;
		beconnected = FALSE;
		EventDesired = 0;    // 是否订阅报警上报
		TimeOut = 20;   // 超时时间
		strcpy((char*)UserName,"admin") ;
		strcpy((char*)PassWord,"admin") ;
		EventCallback = NULL;
		StatusCallback = NULL;
		spaceresultcallback = NULL;
		spaceresultcallbackex = NULL;
		beautothread = FALSE;
		berecvthread = FALSE;
		//m_vzcallback  = NULL ;
		UserParamVZ = NULL ;
		pjpegmem = NULL;
		//m_misccallback = NULL;
	}


}net_dev_instance ;


#ifdef __cplusplus
}
#endif


#endif