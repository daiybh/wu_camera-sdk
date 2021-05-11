#pragma once
#include <windows.h>
#include <string>
#include <shlwapi.h>
//#define ConfigPath  _T(".\\Config.ini")

#define IConfig (Config::getInstance())
class Config
{
	std::string m_ConfigPathA = ".\\Config.ini";
public:
	std::string url,
		appkey,
		appsecret,
		hotelid_G000001, hotelid_2
		;
	std::string dbServer, dbUserName, dbPassword;
	std::string dbName="property";
	int pk003_interval = 10;
public:
	const char*ConfigPathA() {
		return m_ConfigPathA.c_str();
	}
	static Config*                                 getInstance() {
		static Config a;
		return &a;
	}
	Config() {
		load();
	}
	void load() {

		char szBuf1[MAX_PATH];

		ZeroMemory(szBuf1, MAX_PATH);
		GetModuleFileNameA(nullptr, szBuf1, MAX_PATH);
		PathRemoveFileSpecA(szBuf1);
			
		strcat(szBuf1, "\\Config.ini");
		m_ConfigPathA = szBuf1;

		char _url[1024], _appid[1024], _appsecret[1024];

		GetPrivateProfileStringA(("webServer"), "url", ("http://tcar.cm-park.com/gates"), _url, 1024, ConfigPathA()); url = _url;
		GetPrivateProfileStringA(("webServer"), "appkey", ("JNHA"), _appid, 1024, ConfigPathA()); appkey = _appid;
		GetPrivateProfileStringA(("webServer"), "appsecret", ("7OdkvoBRGfWnnDxB345"), _appsecret, 1024, ConfigPathA()); appsecret = _appsecret;

		GetPrivateProfileStringA(("webServer"), "hotelid_G000001", ("G000001"), _appsecret, 1024, ConfigPathA()); hotelid_G000001 = _appsecret;
		GetPrivateProfileStringA(("webServer"), "hotelid_2", ("H000025"), _appsecret, 1024, ConfigPathA()); hotelid_2 = _appsecret;

		pk003_interval = GetPrivateProfileIntA("webServer", "pk003_interval", 10, ConfigPathA());
		bool bWriteBack = false;
		if (bWriteBack)
		{
			sprintf_s(_url, "%d", pk003_interval);
			WritePrivateProfileStringA("webServer", "pk003_interval", _url, ConfigPathA());
		}
		pk003_interval *= 1000 ;

		GetPrivateProfileStringA(("db"), "dbServer", ("192.168.0.120,1433"), _url, 1024, ConfigPathA()); dbServer = _url;
		GetPrivateProfileStringA(("db"), "dbUserName", ("sa"), _appid, 1024, ConfigPathA()); dbUserName = _appid;
		GetPrivateProfileStringA(("db"), "dbPassword", ("<YourStrong!Passw0rd>"), _appsecret, 1024, ConfigPathA()); dbPassword = _appsecret;
		GetPrivateProfileStringA(("db"), "dbName", ("property"), _appsecret, 1024, ConfigPathA()); dbName = _appsecret;


		if (bWriteBack)
		{
			WritePrivateProfileStringA(("webServer"), "url", url.data(), ConfigPathA());
			WritePrivateProfileStringA(("webServer"), "appid", appkey.data(), ConfigPathA());
			WritePrivateProfileStringA(("webServer"), "appsecret", appsecret.data(), ConfigPathA());
			WritePrivateProfileStringA(("webServer"), "hotelid_G000001", hotelid_G000001.data(), ConfigPathA());
			WritePrivateProfileStringA(("webServer"), "hotelid_2", hotelid_2.data(), ConfigPathA());



			WritePrivateProfileStringA(("db"), "dbServer", dbServer.data(), ConfigPathA());
			WritePrivateProfileStringA(("db"), "dbUserName", dbUserName.data(), ConfigPathA());
			WritePrivateProfileStringA(("db"), "dbPassword", dbPassword.data(), ConfigPathA());
			WritePrivateProfileStringA(("db"), "dbName", dbName.data(), ConfigPathA());
		}
	}
};