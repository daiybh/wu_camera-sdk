#pragma once

#ifdef _MSC_VER
#include <Windows.h>
#else
#include<semaphore.h>
#endif

class SemaphoreClock
{
#ifdef _MSC_VER
	HANDLE m_handle = nullptr;
#else
	sem_t  m_handle;
#endif
public:
	SemaphoreClock()
	{
#ifdef _MSC_VER
		m_handle = ::CreateSemaphore(nullptr, 0, LONG_MAX, nullptr);
#else
		sem_init(&m_handle, 0, LONG_MAX);
#endif
	}

	~SemaphoreClock()
	{
#ifdef _MSC_VER
		CloseHandle(m_handle);
#else
		sem_destroy(&m_handle);
#endif
	}

	void raiseEvent() const
	{
#ifdef _MSC_VER
		ReleaseSemaphore(m_handle, 1, nullptr);
#else
		sem_post(&m_handle);
#endif
	}

	bool waitEvent(int nTimeOut) const
	{
#ifdef _MSC_VER
		return WaitForSingleObject(m_handle, nTimeOut) == WAIT_OBJECT_0;
#else
		return sem_wait(&m_handle) == 0;//here we don't have time
#endif
	}
};
