#pragma once
#include <vector>
#include <shared_mutex>
#include "lockedPtr.h"

template <class T>
class SyncVector final
{
public:

	template <class... Valty>
	void emplace_back(Valty&&...Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_vector.emplace_back(std::forward<Valty>(Val)...);
	}

	bool empty() const
	{
		return m_vector.empty();
	}

	T front()
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_vector.front();
	}

	T back()
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_vector.back();
	}

	template <class Function>
	decltype(auto) wlock(Function&& function)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return function(m_vector);
	}

	template <class Function>
	decltype(auto) rlock(Function&& function)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return function(m_vector);
	}

	decltype(auto) rlock()
	{
		return LockedPtr<decltype(m_vector), decltype(m_lock)>(&m_vector, &m_lock, true);
	}

	decltype(auto) wlock()
	{
		return LockedPtr<decltype(m_vector), decltype(m_lock)>(&m_vector, &m_lock, false);
	}

	void clear()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_vector.clear();
	}

	size_t size() const
	{
		return m_vector.size();
	}

	decltype(auto) operator[](size_t Pos)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_vector[Pos];
	}

	decltype(auto) at(size_t Pos)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_vector.at(Pos);
	}

private:
	std::vector<T>    m_vector;
	std::shared_mutex m_lock;
};
