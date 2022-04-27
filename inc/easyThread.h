#pragma once
#include <stdexcept>
#include <thread>
#include "stringHelper.h"

#ifdef _WIN32
#include <Windows.h>
#include <processthreadsapi.h>
#else
#include <pthread.h>
#endif

class EasyThread
{
protected:
	virtual void callBack() = 0;

	enum class Priority
	{
		low,
		normal,
		aboveNormal,
		high,
		realTime
	};

	bool isRunning() const
	{
		return !m_exitRequested;
	}

	int32_t startThread(Priority _priority = Priority::normal)
	{
		if (m_thread.joinable())
			return -1;
		m_exitRequested = false;
		m_thread = std::thread(theThread, this);
		setPriority(_priority);
		return 0;
	}

	int32_t stopThread()
	{
		if (!m_thread.joinable())
			return -1;
		m_exitRequested = true;
		m_thread.join();
		return 0;
	}

	void setName(const std::string& name)
	{
#ifdef _WIN32
		SetThreadDescription(m_thread.native_handle(), getWString(name).c_str());
#else
		pthread_setname_np(m_thread.native_handle(), name.c_str());
#endif
	}

	void setName(const std::wstring& name)
	{
#ifdef _WIN32
		SetThreadDescription(m_thread.native_handle(), name.c_str());
#else
		pthread_setname_np(m_thread.native_handle(), getAString(name).c_str());
#endif
	}

public:
	EasyThread() = default;
	virtual ~EasyThread() = default;
private:
	std::thread   m_thread;
	volatile bool m_exitRequested = false;

	static void theThread(EasyThread* me)
	{
		me->callBack();
	}

	void setPriority(Priority _priority)
	{
#ifdef _WIN32
		switch (_priority)
		{
		case Priority::low:			SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_BELOW_NORMAL);	break;
		case Priority::normal:		SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_NORMAL);		break;
		case Priority::aboveNormal: SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);	break;
		case Priority::high:		SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_HIGHEST);		break;
		case Priority::realTime:	SetThreadPriority(m_thread.native_handle(), THREAD_PRIORITY_TIME_CRITICAL); break;
		}
#else
		sched_param sch;
		int policy;
		pthread_getschedparam(m_thread.native_handle(), &policy, &sch);
		switch (_priority)
		{
		case Priority::low:			 sch.sched_priority = 10; break;
		case Priority::normal:		 sch.sched_priority = 0; break;
		case Priority::aboveNormal:	 sch.sched_priority = -5; break;
		case Priority::high:		 sch.sched_priority = -10; break;
		case Priority::realTime:	 sch.sched_priority = -20; break;
		}
		pthread_setschedparam(m_thread.native_handle(), SCHED_FIFO, &sch);
#endif
	}
};
