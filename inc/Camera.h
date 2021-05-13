#pragma once
#include <windows.h>
#include "incEyest/ast_netapi.h"
#include "SyncMap.h"
#include <string>
#include "led.h"
// lib
#ifdef _DEBUG
#pragma comment(lib, "EYESTNETLIB.lib")
#else
#pragma comment(lib, "EYESTNETLIB.lib")
#endif
class ClassCallBack
{
#define outFunName                      \
	{                                   \
		printf("\n%s\n", __FUNCTION__); \
	}

public:
	// 报警回调
	static void __stdcall NET_EVENTCALLBACK(const NET_DEV_ALARM_ITEM *Report, void *UserParam) { outFunName }

	//状态回掉函数
	static void __stdcall NET_CONSTAUSCALLBACK(NET_DEV_STATUS *status, void *UserParam) { outFunName }

	// 精简的状态回调
	static void __stdcall NET_CONSTAUSCALLBACK_EX(char *ipaddr, int status) { outFunName }

	static void __stdcall NET_IO_DATACALLBACK(char *pData, int *nLength, int address) { outFunName }

	//智能检测状态回调函数
	// 这里为了减少数据拷贝，修改回调函数，
	//参数改为 0 图像头部数据，1 图像jpeg数据，2 图像jpeg长度，3 用户数据
	static void __stdcall NET_SMARTRECVCALLBACK(NET_DEV_SMARTRECRESUTLIST *SmartResult, char *pJpeg, int *nLength, char *userdata, void *UserParam)
	{
		outFunName char str[1024] = {0};
		sprintf(str, "地点:%s IP:%s 车牌:%s %.2f  正常车辆", SmartResult->cambase.DevName,
				SmartResult->DevIP.IpV4, SmartResult->parkspaceresult[0].plateresult.platenum,
				SmartResult->parkspaceresult[0].plateresult.platereliability);
		printf(str);
	};

	static void __stdcall NET_SMARTRECVCALLBACKV1(NET_DEV_SMARTRECRESUTLIST_V1 *SmartResult, char *pJpeg, int *nLength, char *userdata, void *UserParam)
	{
		outFunName
	}
	// 精简的识别结果回调函数
	static void __stdcall NET_SMARTRECVCALLBACK_EX(NET_DEV_SMARTRECRESUT_EX *SmartResultEx, char *pJpeg, int *nLength, char *userdata, void *UserParam)
	{
		outFunName char str[1024] = {0};
		sprintf(str, "地点:%s IP:%s 车牌:%s %.2f\n", SmartResultEx->DevName, SmartResultEx->camerIp, SmartResultEx->platenum, SmartResultEx->realbility);
		printf(str);
	}

	//其他数据回调
	//包括脱机数据  卡数据等
	static void __stdcall NET_MISC_CALLBACK(char *pData, int len, void *UserParam)
	{
		outFunName
	}
	// 道闸状态回调原型
	static void __stdcall NET_gate_callback(const char *jsongate)
	{
		outFunName
	}

	// 视频数据回调
	static void __stdcall NET_PREVIEWDATACALLBACK(unsigned char *Frame, int framelength, int width, int height, int frametype, void *UserParam)
	{
		static long lcount = 0;
		if (lcount++ % 1000 == 0)
			outFunName
	}

	static void __stdcall NET_DECODEDATACALLBACK(unsigned char *Frame, int width, int height, void *UserParam)
	{
		outFunName
	}

	// 预览状态回调
	static void __stdcall NET_PREVIEWSTAUSCALLBACK(WORD Code, HWND hWnd, UINT Msg, void *UserParam)
	{
		static long lcount = 0;
		if (lcount++ % 1000 == 0)
			outFunName
	}

	//调试回调
	static void __stdcall NET_DEBUGVIEWCALLBACK(char *ipaddr, char *szInfo, void *pUser)
	{
		outFunName
	}
};

//搜索设备回调函数
typedef void(CALLBACK *ADD_LOG)(const char *log, void *UserParam);
class CCamera
{
public:
	long long m_playinstance;		 //播放视频句柄
	NET_PREVIEWPARAM m_previewparam; // 视频预览参数
	NET_CONPARAM m_conparam;		 //相机登录参数
	int m_port;
	char m_ipaddrstr[16];	 //000.000.000.000
	long long m_caminstance; //设备登录句柄
	int m_camversion;
	bool isValidIpaddr()
	{
		if (strlen(m_ipaddrstr) < 7 || strcmp(m_ipaddrstr, "0.0.0.0") == 0)
			return false;
		return true;
	}

protected:
	void AddLogtoList(const char *x)
	{
		if (_ADD_LOG == nullptr)
			printf("%s\n", x);
		else
			_ADD_LOG(x, this);
	}

public:
	//callback function
	ADD_LOG _ADD_LOG=nullptr;

	NET_SEARCHCALLBACK _NET_SEARCHCALLBACK;
	NET_EVENTCALLBACK _NET_EVENTCALLBACK;
	NET_CONSTAUSCALLBACK _NET_CONSTAUSCALLBACK;
	NET_SMARTRECVCALLBACK _NET_SMARTRECVCALLBACK;
	NET_SMARTRECVCALLBACKV1 _NET_SMARTRECVCALLBACKV1;
	NET_SMARTRECVCALLBACK_EX _NET_SMARTRECVCALLBACK_EX;
	NET_MISC_CALLBACK _NET_MISC_CALLBACK;
	NET_gate_callback _NET_gate_callback; // 新增道闸状态改变回调函数 2018.09.25

	NET_PREVIEWDATACALLBACK _NET_PREVIEWDATACALLBACK;
	NET_PREVIEWSTAUSCALLBACK _NET_PREVIEWSTAUSCALLBACK;
	NET_DECODEDATACALLBACK _NET_DECODEDATACALLBACK;
	int m_curID = -1;

public:
	SyncMap<std::string, NET_DEV_BROARDSEARCHINFO> m_iplist;
	CCamera()
	{
		EYEST_NET_INIT();
	}
	~CCamera()
	{
		EYEST_NET_RELEASE();
	}

	void setWorkmode(int mode)
	{
		NET_DEV_WORKMODE deviceworkmode;
		deviceworkmode.workmode = mode;
		EYEST_NET_SET_WORKMODE_PARAM(m_caminstance, &deviceworkmode);
	}
	static BOOL CALLBACK SearchFun(NET_DEV_BROARDSEARCHINFO *dev_info, void *UserParam)
	{
		CCamera *pThis = (CCamera *)UserParam;
		return pThis->_searchFun(dev_info);
	}
	bool _searchFun(NET_DEV_BROARDSEARCHINFO *dev_info)
	{
		char newip[1024];
		sprintf(newip, "%s", dev_info->EthCfg.EthNICs[0].IPAddr.IpV4);

		if (!m_iplist.find(newip))
		{
			m_iplist.emplace(newip, *dev_info);
		}

		long timenum = dev_info->timeflag;
		int runday = timenum / 86400;
		int runhour = (timenum % 86400) / 3600;
		int runmin = (timenum % 3600) / 60;
		int runsec = timenum % 60;

		int nCmdConnect = -1;
		int nPicConnect = -1;
		if (dev_info->ServiceCfg.MsgPort < 10)
		{
			nCmdConnect = dev_info->ServiceCfg.MsgPort;
		}
		if (dev_info->ServiceCfg.HttpPort < 10)
		{
			nPicConnect = dev_info->ServiceCfg.HttpPort;
		}

		char str[1024];
		sprintf(str, "Cam:%s,Ver:%s [已运行：%d天%d时%d分%d秒] CMD:%d PIC:%d", dev_info->EthCfg.EthNICs[0].IPAddr.IpV4,
				dev_info->SoftwareVer, runday, runhour, runmin, runsec, nCmdConnect, nPicConnect);
		printf(str);
		return 1;
	}

	void searchDev()
	{
		NET_SEARCHPARAM param;
		memset(&param, 0, sizeof(NET_SEARCHPARAM));
		param.Callback = (_NET_SEARCHCALLBACK == nullptr) ? &CCamera::SearchFun : _NET_SEARCHCALLBACK;
		param.UserParam = this;
		EYEST_NET_SEARCH_DEV(&param);
	}
	void connect()
	{
		connect(m_ipaddrstr, 8088);
	}
	bool drawROI(bool bEnable)
	{
		int nret = EYEST_NET_DRAW_ROI(m_caminstance, m_playinstance, bEnable ? 1 : 0);
		return nret == 1;
	}
	bool setCarHeadCheck(bool bOpen)
	{
		int nret = EYEST_NET_SET_CARHEADCHECK(m_caminstance, bOpen ? 1 : 0);
		return nret == 1;
	}
	// value: 0--9
	void chageVOLUME(int value)
	{
		bool bRet = EYEST_NET_VOLUME_CONTROL(m_ipaddrstr, 37890, value);
		char str[1024];
		sprintf(str, "changeVolume(%d)  %s", value, bRet ? "success" : "failed");
		AddLogtoList(str);
	}
	void openDoor()
	{
		if (m_caminstance <= 0)
		{
			char str[1024];
			sprintf(str, "相机未连接.");
			AddLogtoList(str);
			return;
		}
		int ret = EYEST_NET_IO_CONTROL_EX(m_ipaddrstr, 37890, 0, 1);
		if (ret)
		{
			char str[1024];
			sprintf(str, "发送开闸成功.");
			AddLogtoList(str);
		}
	}
	void GetPic(char *rgb, int *width, int *height)
	{
		if (m_caminstance < 0)
		{
			char str[1024];
			sprintf(str, "设备未登录.");
			AddLogtoList(str);
			return;
		}
		if (m_playinstance > 0)
		{

			EYEST_NET_GET_PREVIEW_RGB(m_playinstance, rgb, width, height);

			char ss[1024];
			sprintf_s(ss, "getpic-->%d--%d\n", width, height);
			AddLogtoList(ss);
		}
		else
		{
		}
	}
	void closeDoor()
	{
		if (m_caminstance <= 0)
		{
			char str[1024];
			sprintf(str, "相机未连接.");
			AddLogtoList(str);
			return;
		}
		int ret = EYEST_NET_IO_CLOSE_DOOR_EX(m_ipaddrstr, 37890, 0, 1);
		if (ret)
		{
			char str[1024];
			sprintf(str, "发送关闸成功.");
			AddLogtoList(str);
		}
	}

	bool getWhiteList(NET_VIPINFOLIST_V1 &vipList)
	{
		int ret = EYEST_NET_GET_PARK_VIP_PARAM_V1(m_caminstance, &vipList);
		return ret == 1;
	}
	bool setWhiteList(NET_VIPINFOLIST_V1 &vipList)
	{
		int ret = EYEST_NET_SET_PARK_VIP_PARAM_V1(m_caminstance, &vipList);
		return ret == 1;
	}
	void connect(const char *ip, int port)
	{
		strcpy(m_ipaddrstr, ip);
		m_port = port;

		memset(&m_conparam, 0, sizeof(NET_CONPARAM));

		m_conparam.AutoReconnect = 1;		  //自动重连
		strcpy(m_conparam.UserName, "admin"); //暂时未用
		strcpy(m_conparam.PassWord, "admin"); //暂时未用

		// use this fun call back

		m_conparam.EventCallback = CCamera::_NET_EVENTCALLBACK;		//错误事件回调函数
		m_conparam.StatusCallback = CCamera::_NET_CONSTAUSCALLBACK; //状态回调函数

		m_conparam.spaceresultcallback = CCamera::_NET_SMARTRECVCALLBACK;	  // 智能检测状态回调函数
		m_conparam.spaceresultcallbackv1 = CCamera::_NET_SMARTRECVCALLBACKV1; // 智能检测状态回调函数 兼容版本

		m_conparam.spaceresultcallbackex = CCamera::_NET_SMARTRECVCALLBACK_EX; // 精简的注识别结果注册回调

		m_conparam.misccallback = CCamera::_NET_MISC_CALLBACK;		 // 杂项结果回调函数
		m_conparam.gatestatuscallback = CCamera::_NET_gate_callback; // 新增道闸状态改变回调函数 2018.09.25

		m_conparam.UserParam = this;

		m_conparam.Port = m_port;

		strcpy(m_conparam.IpAddr.IpV4, m_ipaddrstr);

		if (m_caminstance > 0)
		{
			char str[1024];
			sprintf(str, "相机已连接.");
			AddLogtoList(str);
			if (m_playinstance > 0)
			{
				EYEST_NET_STOP_PREVIEW(m_caminstance, m_playinstance);
				m_playinstance = 0;
			}
			EYEST_NET_LOGOUT(m_caminstance);

			//return;
		}

		m_caminstance = EYEST_NET_LOGIN(&m_conparam);
		if (m_caminstance > 0)
		{
			m_camversion = EYEST_NET_GET_DEVICETYYPE(m_caminstance);
			char strLog[1024];
			sprintf(strLog, "相机连接成功,IP:%s ,Version:%d\n", m_ipaddrstr, m_camversion);
			AddLogtoList(strLog);
		}
		else
		{
			char strLog[1024];
			sprintf(strLog, "相机连接失败,IP:%s 请检查网络连接\n", m_ipaddrstr);
			AddLogtoList(strLog);
		}
	}
	void disconnect()
	{
		if (m_playinstance > 0)
		{
			EYEST_NET_STOP_PREVIEW(m_caminstance, m_playinstance);
			m_playinstance = 0;
		}
		EYEST_NET_LOGOUT(m_caminstance);
		m_caminstance = 0;
	}
	void getDeviceType()
	{
		int camversion = EYEST_NET_GET_DEVICETYYPE(m_caminstance);
		char strLog[1024];
		sprintf(strLog, "EYEST_NET_GET_DEVICETYYPE,IP:%s ,Version:%d\n", m_ipaddrstr, camversion);
		AddLogtoList(strLog);
	}
	void preview(HWND hWnd)
	{

		if (m_caminstance < 0)
		{
			char str[1024];
			sprintf(str, "相机未连接,请先连接相机");
			AddLogtoList(str);
			return;
		}
		if (m_playinstance > 0)
		{
			char str[1024];
			sprintf(str, "视频正在播放");
			AddLogtoList(str);
			return;
		}

		m_previewparam.AutoReconnect = 1; //视频掉线自动重连
		m_previewparam.Channel = 0;
		m_previewparam.VideoPort = 556; // RTSP端口
		m_previewparam.StreamType = 1;	// m_videotype.GetCurSel(); // 子码流

		m_previewparam.StatusCallback = _NET_PREVIEWSTAUSCALLBACK;
		m_previewparam.DataCallback = _NET_PREVIEWDATACALLBACK;	 //编码数据回调
		m_previewparam.DecodeCallback = _NET_DECODEDATACALLBACK; //解码BGR 数据回调
		m_previewparam.hWnd = hWnd;								 // GetDesktopWindow();;// GetDlgItem(IDC_VIDEO)->GetSafeHwnd(); // 播放窗口
		m_previewparam.UserParam = this;
		m_previewparam.Protol = 1; //0 tcp 1:udp

		// if need assist focus , set nNeedFocus = 1, then start preview ...
		m_previewparam.nNeedFocus = 0; // m_needfocus;
		int nHard = 0;
		int nD3d = 0;

		EYEST_NET_GET_SUPORT((int)m_previewparam.hWnd, &nHard, &nD3d);
		std::string str;
		if (nHard)
		{
			str = "Hard Decode:Yes";
		}
		else
		{
			str = "Hard Decode:No";
		}
		if (nD3d)
		{
			str += ",D3D:Yes";
		}
		else
		{
			str += ",D3D:No";
		}
		AddLogtoList(str.c_str());
		// 用户数据
		m_playinstance = EYEST_NET_START_PREVIEW(m_caminstance, &m_previewparam);
		if (m_playinstance > 0)
		{
			AddLogtoList("视频预览成功");
		}
		else
		{
			AddLogtoList("视频预览失败");
		}
		/*if (m_needfocus)
		{
			_beginthread(FocusThread, 0, this);
		}*/
	}
	bool LEDScreen_setText(const char *textData)
	{

		unsigned char pSendData[1280] = {0x1A, 0x1B};

		memcpy(pSendData + 2, textData, strlen(textData));

		int nlength = strlen(textData);
		pSendData[2 + nlength] = 0x01;

		pSendData[3 + nlength] = 0x1C;
		pSendData[4 + nlength] = 0x1D;

		int len = LEDFunc::ledCls(pSendData);

		BOOL ret = EYEST_NET_SERIAL_CONTROL_EX(m_ipaddrstr, 37890, 1, (char *)pSendData, len);
		if (ret)
		{
			len = LEDFunc::ledText(1, 5000, textData, "rd", pSendData);
			ret = EYEST_NET_SERIAL_CONTROL_EX(m_ipaddrstr, 37890, 1, (char *)pSendData, len);
		}

		char log[1024];
		sprintf(log, "LED发送字符串%s--%s", ret ? "成功" : "失败", textData);

		AddLogtoList(log);
		return ret;
	}

	static void __stdcall RecvRecResultFull(NET_DEV_SMARTRECRESUTLIST *SmartResult, char *pJpeg, int *nLength, char *userdata, void *UserParam)
	{
		printf("%s\n", __FUNCTION__);
		//		CConfigToolDlg *pdlg = (CConfigToolDlg*)UserParam;
		//
		//		if (SmartResult->smartmode == 0xE1)
		//		{
		//			memcpy(AEDATA, pJpeg, *nLength);
		//			// pdlg->GetDlgItem(IDC_PIC)->Line
		//			CDC *pdc = pdlg->GetDlgItem(IDC_PIC)->GetDC();
		//			if (pdc != NULL)
		//			{
		//
		//				if (!TempImg.empty())
		//				{
		//					cv::Mat TempImg1 = TempImg.clone();
		//					pdlg->DrawAEToHDC(TempImg1, IDC_PIC, AEDATA, 16, 16);
		//				}
		//
		//			}
		//			return;
		//		}
		//		vector<char>data(*nLength);
		//		for (int i = 0; i < *nLength; i++)
		//		{
		//			data[i] = pJpeg[i];
		//		}
		//		cv::Mat show = cv::imdecode(cv::Mat(data), CV_LOAD_IMAGE_COLOR);
		//
		//		TempImg = show.clone();
		//
		//		CString  str;
		//		str.Format("%s", SmartResult->parkspaceresult[0].plateresult.platenum);
		//		pdlg->GetDlgItem(IDC_EDIT_PLATE)->SetWindowText(str);
		//
		//
		//
		//		cv::Rect platerect;
		//		platerect.x = SmartResult->parkspaceresult[0].plateresult.platerect.left;
		//		platerect.y = SmartResult->parkspaceresult[0].plateresult.platerect.top;
		//		platerect.width = SmartResult->parkspaceresult[0].plateresult.platerect.right - SmartResult->parkspaceresult[0].plateresult.platerect.left;
		//		platerect.height = SmartResult->parkspaceresult[0].plateresult.platerect.bottom - SmartResult->parkspaceresult[0].plateresult.platerect.top;
		//
		//		if (platerect.x >= 0 && platerect.y >= 0 &&
		//			platerect.width >= 0 && platerect.width < show.cols && platerect.height < show.rows &&
		//			platerect.height>0)
		//		{
		//			cv::Mat plateimg = show(platerect).clone();
		//			pdlg->DrawMatToHDC(plateimg, IDC_PLATEIMG);
		//			cv::rectangle(show, platerect, CV_RGB(0x00, 0xFF, 0x00), 2);
		//
		//		}
		//
		//		if (strstr(SmartResult->parkspaceresult[0].plateresult.platenum, "FACE") != NULL)
		//		{
		//
		//			float *pppoint = (float*)SmartResult->parkspaceresult[0].plateresult.cartype;
		//
		//			for (int num = 0; num < 5; num++)
		//			{
		//				cv::circle(show, cv::Point(pppoint[num * 2], pppoint[num * 2 + 1]), 6, cv::Scalar(255, 255, 0), 6);
		//			}
		//
		//		}
		//
		//		pdlg->DrawMatToHDC(show, IDC_PIC);
		//		char szcartype[64] = { 0 };
		//		char szcar[12] = { 0 };
		//		if (SmartResult->parkspaceresult[0].spacestatus == 2)
		//		{
		//			str.Format("地点:%s IP:%s 车牌:%s %.2f  正常车辆", SmartResult->cambase.DevName,
		//				SmartResult->DevIP.IpV4, SmartResult->parkspaceresult[0].plateresult.platenum,
		//				SmartResult->parkspaceresult[0].plateresult.platereliability);
		//			strcpy(szcar, "car");
		//			nNormalCount++;
		//		}
		//		else  if (SmartResult->parkspaceresult[0].spacestatus == 1)
		//		{
		//			str.Format("地点:%s IP:%s 车牌:%s %.2f  异常车辆", SmartResult->cambase.DevName,
		//				SmartResult->DevIP.IpV4, SmartResult->parkspaceresult[0].plateresult.platenum,
		//				SmartResult->parkspaceresult[0].plateresult.platereliability);
		//			strcpy(szcar, "nocar");
		//			nNoCarCount++;
		//		}
		//		else
		//		{
		//			str.Format("地点:%s IP:%s 车牌:%s %.2f ", SmartResult->cambase.DevName,
		//				SmartResult->DevIP.IpV4, SmartResult->parkspaceresult[0].plateresult.platenum,
		//				SmartResult->parkspaceresult[0].plateresult.platereliability);
		//			strcpy(szcar, "uncar");
		//		}
		//
		//		static int icount = 0;
		//		CString strface;
		//		pdlg->AddLogtoList(str);
		//
		//		str.Format("正常:%d 非正常:%d", nNormalCount, nNoCarCount);
		//
		//		pdlg->AddLogtoList(str);
		//#if 1
		//		char save_path[256] = { 0 };
		//
		//		CString m_strPathSnap = "D:\\PARKSAVE";
		//		sprintf(save_path, "%s\\", m_strPathSnap);
		//		if (!CreateMultiLevelDirectory(save_path))
		//		{
		//			m_strPathSnap = "C:\\PARKSAVE";
		//			sprintf(save_path, "%s\\", m_strPathSnap);
		//			CreateMultiLevelDirectory(save_path);
		//		}
		//		CString timestip;
		//		CString  place;
		//		timestip.Format("%04d%02d%02d%02d", SmartResult->checktime.Year, SmartResult->checktime.Month
		//			, SmartResult->checktime.Day, SmartResult->checktime.Hour);
		//
		//
		//		place.Format("%s", SmartResult->cambase.DevName);
		//		sprintf(save_path, "%s\\%s", m_strPathSnap, place);
		//		CreateMultiLevelDirectory(save_path);
		//
		//		sprintf(save_path, "%s\\%s\\%s", m_strPathSnap, place, timestip);
		//		CreateMultiLevelDirectory(save_path);
		//
		//		char save_path1[128] = { 0 };
		//		static  int count = 0;
		//		sprintf(save_path1, "%s\\%04d-%02d-%02d _%02d_%02d_%02d_%03d_%d_%s_%s_%s.jpg", save_path,
		//			SmartResult->checktime.Year, SmartResult->checktime.Month
		//			, SmartResult->checktime.Day, SmartResult->checktime.Hour,
		//			SmartResult->checktime.Minute, SmartResult->checktime.Second, SmartResult->checktime.MilliSec, count++,
		//			SmartResult->parkspaceresult[0].plateresult.platenum, SmartResult->parkspaceresult[0].plateresult.platecolor, szcar);
		//		FILE* pf = fopen(save_path1, "wb");
		//		if (!pf)
		//		{
		//			return;
		//		}
		//		fwrite(pJpeg, (*nLength), 1, pf);
		//		fclose(pf);
		//
		//
		//#endif
	}

	static void __stdcall RecvRecResultFun(NET_DEV_SMARTRECRESUT_EX *SmartResultEx, char *pJpeg, int *nLength, char *userdata, void *UserParam)
	{
		printf("%s\n", __FUNCTION__);

		////这里需要将图像加入队列中，另外开一个线程解码或者存储 否则会导致丢图

		//CConfigToolDlg *pdlg = (CConfigToolDlg*)UserParam;
		//vector<char>data(*nLength);
		//for (int i = 0; i < *nLength; i++)
		//{
		//	data[i] = pJpeg[i];
		//}
		//cv::Mat show = cv::imdecode(cv::Mat(data), CV_LOAD_IMAGE_COLOR);

		//CString  str;
		//str.Format("%s", SmartResultEx->platenum);
		//pdlg->GetDlgItem(IDC_EDIT_PLATE)->SetWindowText(str);

		//cv::Rect platerect;
		//platerect.x = SmartResultEx->plateleft;
		//platerect.y = SmartResultEx->platetop;
		//platerect.width = SmartResultEx->plateright - SmartResultEx->plateleft;
		//platerect.height = SmartResultEx->platebottom - SmartResultEx->platetop;

		//cv::Mat plateimg = show(platerect).clone();
		//pdlg->DrawMatToHDC(plateimg, IDC_PLATEIMG);
		//cv::rectangle(show, platerect, CV_RGB(0x00, 0xFF, 0x00), 2);

		//pdlg->DrawMatToHDC(show, IDC_PIC);
		//char szcartype[64] = { 0 };

		//str.Format("地点:%s IP:%s 车牌:%s %.2f", SmartResultEx->DevName, SmartResultEx->camerIp, SmartResultEx->platenum, SmartResultEx->realbility);

		//if (SmartResultEx->snapmode == 2)
		//{
		//	str += "    [A]";
		//}
		//else
		//{
		//	str += "    [M]";
		//	char  szvoice[64] = { 0 };
		//	sprintf(szvoice, "%s, %s,欢迎光临", SmartResultEx->platenum, szcartype);
		//	EYEST_NET_AUDIO_CONTROL(SmartResultEx->camerIp, 37890, szvoice, strlen(szvoice));

		//}

		//pdlg->AddLogtoList(str);
		//char save_path[256] = { 0 };

		//CString m_strPathSnap = "D:\\PARKSAVE";
		//sprintf(save_path, "%s\\", m_strPathSnap);
		//if (!CreateMultiLevelDirectory(save_path))
		//{
		//	m_strPathSnap = "C:\\PARKSAVE";
		//	sprintf(save_path, "%s\\", m_strPathSnap);
		//	CreateMultiLevelDirectory(save_path);
		//}
		//CString timestip;
		//CString  place;
		//timestip.Format("%04d%02d%02d%02d", SmartResultEx->nyear, SmartResultEx->nmonth, SmartResultEx->nday, SmartResultEx->nhour);
		//place.Format("%s", SmartResultEx->DevName);
		//sprintf(save_path, "%s\\%s", m_strPathSnap, place);
		//CreateMultiLevelDirectory(save_path);

		//sprintf(save_path, "%s\\%s\\%s", m_strPathSnap, place, timestip);
		//CreateMultiLevelDirectory(save_path);

		//char save_path1[128] = { 0 };
		//static  int count = 0;
		//sprintf(save_path1, "%s\\%04d-%02d-%02d _%02d_%02d_%02d_%03d_%d_%s_%s.jpg", save_path,
		//	SmartResultEx->nyear, SmartResultEx->nmonth, SmartResultEx->nday, SmartResultEx->nhour,
		//	SmartResultEx->nminite, SmartResultEx->nsecond, SmartResultEx->nmillisec, count++,
		//	SmartResultEx->platenum, SmartResultEx->platecolor);

		//FILE* pf = fopen(save_path1, "wb");
		//if (!pf)
		//{
		//	return;
		//}
		//fwrite(pJpeg, (*nLength), 1, pf);
		//fclose(pf);
	}

	//offline 记录
	typedef struct
	{
		unsigned char szCamId[32];
		unsigned char szCamIp[32];
		char szPlateNum[16];
		char szPlateColor[8];
		unsigned char szTime[16];
		int mode; //
	} CarRecord;

	//出场后流记录
	typedef struct
	{
		int ids; // 编号
		float fees;
		CarRecord g_inrecord;
		CarRecord g_outrecord;
	} CarFlow;

	void setAudio(char *audioData, int dataLen)
	{
#define SOFTVOICE
#ifdef SOFTVOICE
		EYEST_NET_AUDIO_CONTROL_EX(m_caminstance, audioData, dataLen);
#endif

		int ret = EYEST_NET_AUDIO_CONTROL(m_ipaddrstr, 37890, audioData, dataLen);
		char log[1024];
		sprintf(log, "发送语音%s--%s", ret ? "成功" : "失败", audioData);
		AddLogtoList(log);
	}

	void set_3A_PARAM_V1(NET_DEV_CAMERAPARAM_V1 &paramV1)
	{
		NET_DEV_CAMERACFG_V1 v1;

		memcpy(&v1.CameraParam, &paramV1, sizeof(paramV1));

		EYEST_NET_SET_3A_PARAM_V1(m_caminstance, &v1);
	}
};