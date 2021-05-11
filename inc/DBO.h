#pragma once

#include <wbemcli.h>
#include <functional>
#include <optional>
#include <windows.h>
#include "locker.h"
#include <map>
#include <atltime.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <iostream>
#pragma comment(lib,"odbccp32.lib")
#pragma comment(lib,"odbc32.lib")

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
class DBO {
	std::string m_connectStr;//"Driver={sql server};server=DESKTOP-HMVR0JT;uid=sa;pwd=123456;database=property;"
	

	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;

	bool m_bConnected = false;
	Locker  m_locker;
	
	bool connectDB() 
	{
		do
		{
			SQLDisconnect(sqlConnHandle);
			if (sqlStmtHandle)
				SQLFreeHandle(SQL_HANDLE_STMT,sqlStmtHandle);
			//output
			std::cout << "Attempting connection to SQL Server...";
			std::cout << "\n";
			SQLCHAR retconstring[SQL_RETURN_CODE_LEN];
			SQLRETURN ret = SQLDriverConnectA(sqlConnHandle,
				NULL,
				//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
				//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
				(SQLCHAR*)m_connectStr.data(),
				SQL_NTS,
				retconstring,
				1024,
				NULL,
				SQL_DRIVER_NOPROMPT);

			if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
			{
				SPDLOG_LOGGER_ERROR(m_logger, "connect failed. {}", ret);
				break;
			}
			

			//if there is a problem connecting then exit application
			if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
				break;
			m_bConnected = true;
			SPDLOG_LOGGER_INFO(m_logger, "Successfully connected to SQL Server ");
			return true;
		} while (0);

		/*SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle);
		SQLDisconnect(sqlconnectionhandle);
		SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
		SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);*/
		SPDLOG_LOGGER_ERROR(m_logger, "Could not connect to SQL Server  {}", m_connectStr);
		return false;
	}
	bool init()
	{
		m_bConnected = false;
		try {
			connectDB();			
			return true;
		}
		catch (...) { // intercept OTL exceptions
			
		}
		return false;
	}	

	void doUpdate_tbParkLot(CheWeiItem &Item)
	{		
		//更新地下层
		string updateSqlB = R"(UPDATE property.dbo.tbParkLot SET  num=)"+ Item.strDownFloor_ct +R"(, use_lot=)"+ Item.strDownFloor_kct +R"( where park_id=2)";
		//更新地面层
		string updateSqlA = R"(UPDATE property.dbo.tbParkLot SET  num=)"+ Item.strUpFloor_ct +R"(, use_lot=)"+ Item.strUpFloor_kct +R"( where park_id=1)";

		{
			SPDLOG_LOGGER_DEBUG(m_logger, updateSqlA);
			SQLRETURN ret;
			ret = SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)updateSqlA.data(), SQL_NTS);

			if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
			{
				m_bConnected = false;
				SPDLOG_LOGGER_ERROR(m_logger, "SQLExecDirectA failed. {}", ret);
			}
		}
		{
			SPDLOG_LOGGER_DEBUG(m_logger, updateSqlB);
			SQLRETURN ret;
			ret = SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)updateSqlB.data(), SQL_NTS);

			if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
			{
				m_bConnected = false;
				SPDLOG_LOGGER_ERROR(m_logger, "SQLExecDirectA failed. {}", ret);
			}
		}
	}
	bool DoisAccntExist(std::string &carNO)
	{//
		string querySql = R"( select count(*) as v2 from card_view where right(car_cp,5)=')" + carNO.substr(carNO.length() - 5) + R"(')";
		
		SPDLOG_LOGGER_DEBUG(m_logger, querySql);
		int count = 0;
		SQLINTEGER v2 = 0;
		SQLLEN v2size = 0;
		SQLBindCol(sqlStmtHandle, 1, SQL_C_LONG, &v2, 200, &v2size);
		SQLRETURN ret = SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)querySql.data(), SQL_NTS);

		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			m_bConnected = false;
			SPDLOG_LOGGER_ERROR(m_logger, "SQLExecDirectA failed. {}", ret);
			return 0;
		}
		//return 0;
		if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			//	SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &count, 0, nullptr);
		}
		ret = SQLCloseCursor(sqlStmtHandle);
		SPDLOG_LOGGER_DEBUG(m_logger, "isAccntExist  v2:{} v2size:{}", v2, v2size);
		return v2 > 0 ;
	}

	std::shared_ptr<spdlog::logger> m_logger;
public:
	DBO() {}
	void setLogger(std::shared_ptr<spdlog::logger> _logger)
	{
		m_logger = _logger;
	}
	void Init(string serverIP, string user, string password, string property) {
		char log[1024];
		sprintf_s(log, "Driver={sql server};server=%s;uid=%s;pwd=%s;database=%s;", serverIP.data(),user.data(),password.data(),property.data());
		m_connectStr = log;
		SPDLOG_LOGGER_INFO(m_logger, "m_connectStr..  {}", m_connectStr);
		//allocations
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
			return;
		if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
			return;
		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
			return;
	}
	bool isAccntExist(std::string &carNo)
	{
		LockHolder l(m_locker);
		if (!m_bConnected)
			init();
		if (!m_bConnected)
		{
			SPDLOG_LOGGER_ERROR(m_logger, "db don't connected");
			return 0;
		}
		return DoisAccntExist(carNo);
	}
	int Update_tbParkLot(CheWeiItem &Item)
	{
		LockHolder l(m_locker);
		if (!m_bConnected)
			init();
		if (!m_bConnected)
		{
			SPDLOG_LOGGER_ERROR(m_logger, "db don't connected");
			return 0;
		}

		doUpdate_tbParkLot(Item);
		return 1;
	}
	
	void CleanData()
	{
		string cleanSql = R"(delete from zk_platelist datediff(day,list_time,getdate())>=90 and sta='false' )";

		SPDLOG_LOGGER_INFO(m_logger, cleanSql);
		SQLRETURN ret;
		ret = SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)cleanSql.data(), SQL_NTS);

		if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		{
			m_bConnected = false;
			SPDLOG_LOGGER_ERROR(m_logger, "SQLExecDirectA failed. {}" ,ret);
		}
	}
	void test()
	{
		LockHolder l(m_locker);
		if (!m_bConnected)
			init();
		if (!m_bConnected)return;
		const hotelItem item;
		
	}
};