#pragma once
#include <functional>
#include <map>
#include <shared_mutex>

template<class _K, class _V, class _Pr = std::less<_K>>
class SyncMap
{
	std::map<_K, _V, _Pr>	m_map;
	std::shared_mutex		m_lock;

public:

	SyncMap() = default;

	virtual ~SyncMap() = default;

	bool pop_front()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		if (m_map.empty())
			return false;
		m_map.erase(m_map.begin());
		return true;
	}

	bool pop_begin(_V& _val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		if (m_map.empty())
			return false;
		auto iter = m_map.begin();
		_val = iter->second;
		m_map.erase(iter);
		return true;
	}

	bool emplace(const std::pair<_K, _V>& _Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_map.emplace(_Val).second;
	}

	template<class... _Valty>
	bool emplace(_Valty&&... _Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_map.emplace(std::forward<_Valty>(_Val)...).second;
	}

	template<class... _Valty>
	bool try_emplace(_Valty&&... _Val)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_map.try_emplace(std::forward<_Valty>(_Val)...).second;
	}

	void erase(const _K& key)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_map.erase(key);
	}

	bool insert_or_assign(const _K& key, const _V& value)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_map.insert_or_assign(key, value).second;
	}

	bool empty() const
	{
		return m_map.empty();
	}

	size_t size() const
	{
		return m_map.size();
	}

	void clear()
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		m_map.clear();
	}

	bool find(const _K& key)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		return m_map.find(key) != m_map.end();
	}

	bool find(const _K& key, _V& value)
	{
		std::shared_lock<std::shared_mutex> lock(m_lock);
		auto item = m_map.find(key);
		if (item == m_map.end())
			return false;
		value = item->second;
		return true;
	}

	decltype(auto) operator[](const _K& _Keyval)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return m_map[_Keyval];
	}

	template <class Function>
	decltype(auto) wlock(Function&& function)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return function(m_map);
	}

	template <class Function>
	decltype(auto) rlock(Function&& function)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		return function(m_map);
	}

	void remove_if(const std::function<bool(const _K& key, const _V& value)>& predicate)
	{
		std::lock_guard<std::shared_mutex> lock(m_lock);
		for (auto iter = m_map.begin(); iter != m_map.end();)
		{
			if (predicate(iter->first, iter->second))
				iter = m_map.erase(iter);
			else
				++iter;
		}
	}
};
