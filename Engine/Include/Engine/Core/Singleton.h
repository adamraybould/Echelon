#ifndef SINGLETON_H
#define SINGLETON_H

namespace Core
{
    template <typename T>
    class Singleton
    {
    private:
        static T* m_pInstance;

    public:
        Singleton(){ m_pInstance = static_cast<T*>(this); }
        Singleton& operator=(const Singleton&) = delete;

        static T& GetInstance() { return *m_pInstance; }

    protected:
        virtual ~Singleton() = default;
    };

    template <typename T>
    T* Singleton<T>::m_pInstance = nullptr;
}

#endif //SINGLETON_H
