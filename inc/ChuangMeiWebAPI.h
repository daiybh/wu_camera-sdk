#pragma once

#include "myLogger.h"
#include <vector>
#include <string>
#include <ctime>
#include "StringHelper.h"
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include "MD5.h"
#include <map>
#include <shared_mutex>
#include "LockedPtr.h"
using namespace std;
#define CURL_STATICLIB
extern "C"
{
#include "curl/curl.h"
}
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib,"libcurl.lib")
#include "Config.h"
#include <set>
#include "rapidjson/rapidjson.h"
#include <functional>
#include "HotelItemDefine.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

class WebAPI
{
	string url_encode(const string &value) {
		std::ostringstream escaped;
		escaped.fill('0');
		escaped << hex;

		for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
			string::value_type c = (*i);

			// Keep alphanumeric and other accepted characters intact
			if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
				escaped << c;
				continue;
			}

			// Any other characters are percent-encoded
			escaped << uppercase;
			escaped << '%' << setw(2) << int((unsigned char)c);
			escaped << nouppercase;
		}

		return escaped.str();
	}
	std::shared_ptr<spdlog::logger> m_logger;
	static size_t write_data(char *ptr, size_t size, size_t nmemb, std::string *writerData)
	{
		if (writerData == nullptr)return 0;
		writerData->append(ptr, size * nmemb);
		return size * nmemb;
	}
	std::string curl_main(std::string url, std::string sPost, std::vector<std::string> vheader, int bDebug = 0)
	{
		printf("\n%s\n", url.c_str());
		SPDLOG_LOGGER_INFO(m_logger, "url:{}", url);
		CURL *curl;
		CURLcode res;
		curl_global_init(CURL_GLOBAL_ALL);
		curl = curl_easy_init();
		std::string buffer;
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
			curl_easy_setopt(curl, CURLOPT_URL, url.data());
			struct curl_slist *headers = NULL;
			//增加HTTP header
			headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
			for (auto item : vheader)
			{
			//	headers = curl_slist_append(headers, item.c_str());
			}
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sPost.data());
			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
			{
				//写入到文件
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
			}
			res = curl_easy_perform(curl);
			
			if (res != CURLE_OK)
			{
				SPDLOG_LOGGER_ERROR(m_logger,"ncurl_easy_perform() failed: url:{} msg:{}", url,curl_easy_strerror(res));
			}
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
			if (CURLE_OPERATION_TIMEDOUT == res)
			{
				SPDLOG_LOGGER_ERROR(m_logger, "ncurl_easy_perform({}) failed .timeout",url);
			}
		}
		SPDLOG_LOGGER_INFO(m_logger, "end:{}", url);
	//	curl_global_cleanup();
		return buffer;
	}

	std::vector<std::string> vHeeader = {
				"Content-Type: application/json;charset=\"utf-8\""
	};
	using signParamMap = std::map<std::string, std::string>;
	std::string getTs()
	{
		time_t tnow = time(0);
		// 把 now 转换为 tm 结构
		tm gmtm;
		localtime_s(&gmtm, &tnow);

		char ts[50];
		sprintf_s(ts, "%d%02d%02d%02d%02d%02d", gmtm.tm_year + 1900, gmtm.tm_mon + 1, gmtm.tm_mday,
			gmtm.tm_hour, gmtm.tm_min, gmtm.tm_sec);
		return ts;
	}
	string  creatRequestSign(string ts, signParamMap params)
	{
		string signText = "";
		std::string loc="zh_CN";		
		signText += IConfig->appkey + IConfig->hotelid_G000001 + loc + ts;
		std::set<string > setList;
		for (auto &item : params)
		{
			string value(item.second);

			std::transform(value.begin(), value.end(), value.begin(), ::toupper);
			setList.emplace(value);
		}
		for (auto &item : setList)
			signText += item;

		hash_library::MD5 md5;
		return md5(signText);
	}
	/*
	接口地址：
		http://xop360.test.foxhis.com/xmsopen-web/rest
	授权参数：
		appkey：JNHA（酒店环境根据实际值填）
		secret：7OdkvoBRGfWnnDxB345（酒店环境根据实际值填）
		hotelid：G000001（固定值）
		hotelid：H000025（酒店环境根据实际值填）
		注意事项：session有效期为8天，可以定时7天重新获取。不需要每次调用接口都获取一次
		/**/
	std::string m_session = "";
	uint64_t m_lastUpdateTime = 0;//GetTickCount64
	
	std::shared_mutex m_lock;
	std::string covert_utf8_to_unicode(std::string sutf8)
	{
		std::wstring retU = utf8_to_unicode(sutf8);
		return wstring_to_string(retU);		
	}
	std::string covert_unicode_to_utf8(std::string sutf8)
	{
		std::wstring retU= string_to_wtring(sutf8);

		return unicode_to_utf8(retU);		
	}

	std::string curl_main(std::string &predata,std::string &data)
	{
		std::string vRequest = curl_main(IConfig->url, (data.length()==0)?predata:makeData(predata,data), vHeeader);

		std::string a = covert_utf8_to_unicode(vRequest);
		SPDLOG_LOGGER_INFO(m_logger, "ret: {}", a);
		return a;
	}
public:
	void setLogger(std::shared_ptr<spdlog::logger> _logger)
	{
		m_logger = _logger;
	}
	WebAPI()
	{
		 m_pcurl= curl_easy_init();
	}
	CURL *m_pcurl = nullptr;
	std::pair<int, std::string> query_1_CheWei(CheWeiItem &item)
	{		
		std::string data = ("act=car_park");
		std::string dataB("");
		std::string vRequest = curl_main(data,dataB);
		rapidjson::Document m_json;
		
		if (m_json.Parse(vRequest.data()).HasParseError())
		{
			SPDLOG_LOGGER_ERROR(m_logger, "parse error");
			return std::make_pair(-1, "parse error");
		}
		rapidjson::Value& result = m_json["result"];

		if (!result["ok"].GetBool())
			return std::make_pair(-2, result["msg"].GetString());
		rapidjson::Value & jsondata = result["data"];


		int totalct = jsondata["ct"].GetInt();
		int total_kct = jsondata["kct"].GetInt();

		int downFloor_kct = 0;
		int upFloor_kct = 0;
		rapidjson::Value& yctarr = jsondata["yct"];
		if (yctarr.IsArray()) {
			for (int i = 0; i < yctarr.Size(); i++)
			{
				const rapidjson::Value& object = yctarr[i];
				std::string pcName = object["cname"].GetString();
				if (pcName == "地下层")
				{
					item.strDownFloor_kct = fmt::format("{}", object["kct"].GetInt());
					item.strDownFloor_ct = fmt::format("{}", object["ct"].GetInt());
				}
				else if (pcName == "地面层")
				{
					item.strUpFloor_kct = fmt::format("{}", object["kct"].GetInt());
					item.strUpFloor_ct = fmt::format("{}", object["ct"].GetInt());
				}
			}
		}
		return std::make_pair(0,vRequest);
	}
	std::string makeData(std::string preData,std::string &value)
	{
		char *output = curl_easy_escape(m_pcurl, value.data(), value.length());
		if (output)
		{
			std::string pret = preData + std::string(output);
			curl_free(output);
			return pret;
		}
		return preData;
	}
	std::pair<int, std::string> query_2_YuyueCheWei(std::string& carNo,int &carType, int64_t &bdate, int64_t &edate)
	{		
		std::string dataB = R"({"tp":2,"carno":")" + covert_unicode_to_utf8(carNo) + R"("})";		
		std::string dataA = R"(act=routes&data=)" ;

		std::string vRequest = curl_main(dataA, dataB);
		
		rapidjson::Document m_json;

		if (m_json.Parse(vRequest.data()).HasParseError())
		{
			SPDLOG_LOGGER_ERROR(m_logger, "parse error");
			return std::make_pair(-1, "parse error");
		}
		rapidjson::Value& result = m_json["result"];

		if (!result["ok"].GetBool())
			return std::make_pair(-2, result["msg"].GetString());
		if(!result.HasMember("data"))
			return std::make_pair(-3, "don't have data node");

		rapidjson::Value & jsondata = result["data"];
		if (!jsondata.HasMember("sname"))
			return std::make_pair(-4, "don't have node [data/sname]");
		std::string sname = jsondata["sname"].GetString();
		if (sname == "无预约")
			return std::make_pair(-4, "无预约");

		std::string rCarNo = jsondata["carno"].GetString();
		carType = jsondata["cartype"].GetInt();
		bdate = jsondata["bdate"].GetInt64();
		edate = jsondata["edate"].GetInt64();

		return std::make_pair(0, jsondata["lname"].GetString());
	}

	std::pair<int, std::string> OutGates_3(std::string& carNo)
	{	
		std::string dataB = R"({"tp":1,"carno":")" + covert_unicode_to_utf8(carNo) + R"("})";
		std::string dataA = R"(act=routes&data=)";
		std::string vRequest = curl_main(dataA, dataB);

		rapidjson::Document m_json;

		if (m_json.Parse(vRequest.data()).HasParseError())
		{
			SPDLOG_LOGGER_ERROR(m_logger, "parse error");
			return std::make_pair(-1, "parse error");
		}
		rapidjson::Value& result = m_json["result"];

		if (!result["ok"].GetBool())
			return std::make_pair(-2, result["msg"].GetString());
		rapidjson::Value & jsondata = result["data"];

		return std::make_pair(0, vRequest);
	}
	std::pair<int, std::string> InGates_4(std::string& carNo)
	{
		std::string dataB = R"({"tp":0,"carno":")" + covert_unicode_to_utf8(carNo) + R"("})";
		std::string dataA = R"(act=routes&data=)";
		std::string vRequest = curl_main(dataA, dataB);


	/*	vRequest = R"({
{
  "result": {
      "ok": true,
      "msg": "",
      "data": {
          "cid": 0,
          "sid": 4,
          "orderid": 41,
          "tel": "138522783566",
          "pid": 7,
          "bdate": 1578538883175,
          "carno": "ssssss",
          "id": 111
      }
  }
} 
)";/**/
		rapidjson::Document m_json;

		if (m_json.Parse(vRequest.data()).HasParseError())
		{
			SPDLOG_LOGGER_ERROR(m_logger, "parse error");
			return std::make_pair(-1, "parse error");
		}
		rapidjson::Value& result = m_json["result"];

		if (!result["ok"].GetBool())
			return std::make_pair(-2, result["msg"].GetString());
		rapidjson::Value & jsondata = result["data"];

		return std::make_pair(0, vRequest);
	}
	
	
};