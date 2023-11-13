#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <functional>
#include <vector>

template <typename T, typename R> using Delegate = std::function<T(R)>;

template <typename T, typename R>
class ENGINE_API MultiCastEvent
{
private:
	std::vector<Delegate<T, R>> m_listeners;

public:
	inline void Broadcast(R userObject)
	{
		for (auto& listener : m_listeners)
		{
			listener(userObject);
		}
	}

	template <typename G, typename F>
	inline void AddListener(G* ref, F&& function)
	{
		m_listeners.push_back(std::bind(std::forward<F>(function), ref, std::placeholders::_1));
	}
};

template<>
class ENGINE_API MultiCastEvent<void, void>
{
private:
	std::vector<Delegate<void, void>> m_listeners;

public:
	inline void Broadcast()
	{
		for (const auto& listener : m_listeners)
		{
			listener();
		}
	}

	inline void AddListener(const Delegate<void, void>& function)
	{
		m_listeners.push_back(function);
	}
};