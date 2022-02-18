
#pragma once
#ifdef P_LOG
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

#include <plog/Appenders/ColorConsoleAppender.h>
#include <windows.h>
enum logInstanceId // Define log instanceIds. Default is 0 and is omitted from this enum.
{
	SecondLog = 1
};
inline void initLogger(int iCount)
{
	static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender; // Create the 2nd appender.
	char strModuleFileName[MAX_PATH];
	char strPath[MAX_PATH];
	GetModuleFileNameA(nullptr, strModuleFileName, MAX_PATH);
	char*p = strrchr(strModuleFileName, '\\');
	*p = '\0';
	p++;
	sprintf_s(strPath, "mkdir %s\\logs\\", strModuleFileName);
	system(strPath);

	sprintf_s(strPath, "%s\\logs\\%s.log", strModuleFileName, p);
	plog::init(plog::debug, strPath, 1024 * 1024 * 5, 100).addAppender(&consoleAppender);

	if(iCount>1)
	{
		sprintf_s(strPath, "%s\\logs\\pk003-%s.log", strModuleFileName, p);
		//plog::init<i>(plog::debug, strPath, 1024 * 1024 * 5, 100).addAppender(&consoleAppender);		
		plog::init<SecondLog>(plog::debug, strPath, 1024 * 1024 * 5, 100);
	}
}
#else
#define SPDLOG_ACTIVE_LEVEL 0
#include <spdlog/spdlog.h>
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
inline void initLogger(const char *folderPath,int logLevel)
{
	if (folderPath == nullptr)
		folderPath = ".\\";
	auto pCreateLogger = [&](std::string loggerName,bool bDefault=false) {

		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_level(spdlog::level::trace);

		std::string fileName = std::string(folderPath)+"/logs/" + loggerName + ".txt";
		auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(fileName, 0, 0,false,10);
		file_sink->set_level(spdlog::level::level_enum( logLevel));

		std::vector<spdlog::sink_ptr> sinks;
		sinks.push_back(console_sink);
		sinks.push_back(file_sink);

		auto logger = std::make_shared<spdlog::logger>(loggerName, sinks.begin(), sinks.end());
		//{ console_sink, file_sink }
		//logger->flush_on(spdlog::level::info);
		logger->set_level(spdlog::level::trace);
		logger->set_pattern("[%x %X] %L %t [%s:%#-%!]>> %v");
		logger->error("########################STARt##############################");

		spdlog::register_logger(logger);
		if (bDefault)
			spdlog::set_default_logger(logger);
		//logger->flush();
	};
	/**/

	pCreateLogger("mainLog", true);
	pCreateLogger("loggerIn");
	pCreateLogger("loggerOut");
	pCreateLogger("liveIn");
	pCreateLogger("liveOut");
	pCreateLogger("callback");
	pCreateLogger("APIA");
	pCreateLogger("CronTask");

	spdlog::set_pattern("[%x %X] %L %t [%s:%#-%!]>> %v");
	spdlog::flush_every(std::chrono::seconds(5));
	spdlog::flush_on(spdlog::level::level_enum(logLevel));

}
#endif