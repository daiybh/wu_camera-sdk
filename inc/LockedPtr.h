#pragma once

template <class SynchronizedType, class LockType>
class LockedPtr
{
	SynchronizedType* m_datum = nullptr;
	LockType*         m_locker = nullptr;
	bool              m_read = false;
public:
	LockedPtr(SynchronizedType* datum, LockType* locker, bool read) :
		m_datum(datum), m_locker(locker), m_read(read)
	{
		if (m_read)
			m_locker->lock_shared();
		else
			m_locker->lock();
	}

	LockedPtr(const LockedPtr& rhs) = delete;
	LockedPtr& operator=(const LockedPtr& rhs) = delete;
	LockedPtr() = default;
	LockedPtr(LockedPtr<SynchronizedType, LockType>&& other) noexcept = default;
	LockedPtr& operator=(LockedPtr<SynchronizedType, LockType>&& other) noexcept = default;

	~LockedPtr()
	{
		if (m_locker == nullptr)
			return;
		if (m_read)
			m_locker->unlock_shared();
		else
			m_locker->unlock();
		m_locker = nullptr;
	}

	SynchronizedType* operator->() const { return m_datum; }
	SynchronizedType& operator*() const { return *m_datum; }
};
