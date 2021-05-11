#include<Windows.h>  
#include<DbgHelp.h>  
#pragma comment(lib,"DbgHelp.lib")  

#include <filesystem>
// 创建Dump文件  
inline void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)  
{  
    HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  
    // Dump信息  
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;  
    dumpInfo.ExceptionPointers = pException;  
    dumpInfo.ThreadId = GetCurrentThreadId();  
    dumpInfo.ClientPointers = TRUE;  
    // 写入Dump文件内容  
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);  
    CloseHandle(hDumpFile);  
}  
// 处理Unhandled Exception的回调函数  
inline LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)  
{
	wchar_t filePath[1024];
    std::error_code error;
    std::filesystem::create_directories("dumps", error);
	std::time_t t = std::time(nullptr);
	std::wcsftime(filePath, 1024, L"dumps\\xieTongApp_%F-%H%M%S.dmp", std::localtime(&t));
    
    CreateDumpFile(filePath,pException);  

	char strModuleFileName[MAX_PATH];
	char strDriver[MAX_PATH];
	char strPath[MAX_PATH];
	GetModuleFileNameA(nullptr, strModuleFileName, MAX_PATH);
    ShellExecuteA(nullptr, nullptr, strModuleFileName, nullptr, nullptr, SW_SHOWNORMAL);
    return EXCEPTION_EXECUTE_HANDLER;  
}  