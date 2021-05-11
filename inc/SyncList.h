#pragma once
#include <list>
#include <functional>
#include <shared_mutex>
#include "LockedPtr.h"
#include "SemaphoreClock.h"
template <class T>
class SyncList final
{
	std::list<T>      m_list;
	std::shared_mutex m_lock;
public:
	SemaphoreClock   m_SemaphoreClock;

	template <class... _Valty>
	void emplace_back(_Valty&&..._Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_list.emplace_back(std::forward<_Valty>(_Val)...);
		m_SemaphoreClock.raiseEvent();
	}

	template <class... _Valty>
	void emplace_front(_Valty&&..._Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_list.emplace_front(std::forward<_Valty>(_Val)...); 
		m_SemaphoreClock.raiseEvent();
	}

	template <class Function>
	decltype(auto) wlock(Function&& function)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return function(m_list);
	}

	template <class Function>
	decltype(auto) rlock(Function&& function)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return function(m_list);
	}

	decltype(auto) rlock()
	{
		return LockedPtr<decltype(m_list), decltype(m_lock)>(&m_list, &m_lock, true);
	}

	decltype(auto) wlock()
	{
		return LockedPtr<decltype(m_list), decltype(m_lock)>(&m_list, &m_lock, false);
	}

	void pop_front()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		if (m_list.empty())
			return;
		m_list.pop_front();
	}

	bool pop_begin(T& _val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		if (m_list.empty())
			return false;
		_val = m_list.front();
		m_list.pop_front();
		return true;
	}

	void pop_back()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		if (m_list.empty())
			return;
		m_list.pop_back();
	}

	T front()
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_list.front();
	}

	T back()
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_list.back();
	}

	size_t size() const
	{
		return m_list.size();
	}

	bool empty() const
	{
		return m_list.empty();
	}

	void clear()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_list.clear();
	}

	bool find(const T& item)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return any_of(begin(m_list), end(m_list), [&](const T& obj) { return item == obj; });
	}

	bool find(const std::function<bool(const T&)>& predicate)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return any_of(begin(m_list), end(m_list), [&](const T& obj) { return predicate(obj); });
	}

	bool remove(const T& item)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_list.remove(item);
		return true;
	}
};
