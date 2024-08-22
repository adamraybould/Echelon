#ifndef DELEGATES_H
#define DELEGATES_H

#include <functional>
#include <vector>

template <typename T, typename R> using Delegate = std::function<T(R)>;
using DelegateVoid = std::function<void()>;

template <typename T, typename R>
class MultiCastEvent
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
class MultiCastEvent<void, void>
{
private:
    std::vector<DelegateVoid> m_listeners;

public:
    inline void Broadcast()
    {
        for (const auto& listener : m_listeners)
        {
            listener();
        }
    }

    inline void AddListener(const DelegateVoid& function)
    {
        m_listeners.push_back(function);
    }
};

#endif //DELEGATES_H
