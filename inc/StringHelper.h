#pragma once
#include <string>
#include <cstdarg>
#include <Windows.h>

inline std::wstring getWString(const char* fmt, ...)
{
	va_list marker;
	char szBuffer[5 * 1024] = { 0 };

	va_start(marker, fmt);
	_vsnprintf_s(szBuffer, std::size(szBuffer), _TRUNCATE, fmt, marker);
	va_end(marker);

	wchar_t wBuffer[5 * 1024] = { 0 };
	size_t size = 0;
	mbstowcs_s(&size, wBuffer, szBuffer, strlen(szBuffer));
	return wBuffer;
}

inline std::wstring getWString(const wchar_t* fmt, ...)
{
	va_list marker;
	wchar_t szBuffer[5 * 1024] = { 0 };
	va_start(marker, fmt);
	_vsnwprintf_s(szBuffer, std::size(szBuffer), _TRUNCATE, fmt, marker);
	va_end(marker);
	return szBuffer;
}

inline std::wstring getWString(const std::string& fmt)
{
	wchar_t wBuffer[5 * 1024] = { 0 };
	size_t size = 0;
	mbstowcs_s(&size, wBuffer, fmt.c_str(), fmt.size());
	return wBuffer;
}

inline std::string getAString(const wchar_t* fmt, ...)
{
	va_list marker;
	wchar_t szBuffer[5 * 1024] = { 0 };

	va_start(marker, fmt);
	_vsnwprintf_s(szBuffer, std::size(szBuffer), _TRUNCATE, fmt, marker);
	va_end(marker);

	char buffer[5 * 1024] = { 0 };
	size_t size = 0;
	wcstombs_s(&size, buffer, szBuffer, wcslen(szBuffer));
	return buffer;
}

inline std::string getAString(const char* fmt, ...)
{
	va_list marker;
	char szBuffer[5 * 1024] = { 0 };
	va_start(marker, fmt);
	_vsnprintf_s(szBuffer, std::size(szBuffer), _TRUNCATE, fmt, marker);
	va_end(marker);
	return szBuffer;
}

inline std::string getAString(const std::wstring& fmt)
{
	char buffer[5 * 1024] = { 0 };
	size_t size = 0;
	wcstombs_s(&size, buffer, fmt.c_str(), fmt.size());
	return buffer;
}

inline bool unicode_to_utf8(const wchar_t* _unicode_str, char* _utf8_str, int32_t _utf8_str_size)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, _unicode_str, -1, nullptr, 0, nullptr, nullptr);
	if (len > _utf8_str_size)
		return false;
	return WideCharToMultiByte(CP_UTF8, 0, _unicode_str, -1, _utf8_str, len, nullptr, nullptr) != 0;
}

inline std::wstring utf8_to_unicode(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, nullptr, 0);
	if (len == 0)
		return L"";
	--len;
	std::wstring result;
	result.resize(len, 0);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, &result[0], len);
	return result;
}

inline std::wstring ascii_to_unicode(const char* str, int32_t strLen)
{
	if (str == nullptr || strLen <= 0)		return L"";
	int len = MultiByteToWideChar(CP_ACP, 0, str, strLen, nullptr, 0);
	if (len == 0)
		return L"";
	--len;
	std::wstring result;
	result.resize(len, 0);
	MultiByteToWideChar(CP_ACP, 0, str, -1, &result[0], len);
	return result;
}

inline uint32_t unicode_to_byte_array(const std::wstring& str, char* buf, int32_t bufSize)
{
	if (buf == nullptr || str.empty() || bufSize <= 0) return 0;
	char const* p = reinterpret_cast<char const*>(&str[0]);
	std::size_t size = str.size() * sizeof(str.front());
	memcpy_s(buf, bufSize, p, size);
	return size;
}

inline std::string unicode_to_utf8(const std::wstring& strUnicode)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, strUnicode.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (len == 0)
		return "";
	--len;
	std::string result;
	result.resize(len, 0);
	WideCharToMultiByte(CP_UTF8, 0, strUnicode.c_str(), -1, &result[0], len, nullptr, nullptr);
	return result;
}

inline std::wstring string_to_wtring(const std::string& str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	if (len == 0)
		return L"";
	--len;
	std::wstring result;
	result.resize(len, 0);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &result[0], len);
	return result;
}

inline std::string wstring_to_string(const std::wstring& wstr)
{
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (len == 0)
		return "";
	--len;
	std::string result;
	result.resize(len, 0);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &result[0], len, nullptr, nullptr);
	return result;
}
