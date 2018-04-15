#pragma once

#include <vector>

namespace engine
{
    template<class T>
    class safe_vector : public std::vector<T>
    {
    public:
        typedef std::vector<T> base_class;
        void lock();
        void unlock();
        
        void push_back(T obj);
        void erase(typename base_class::const_iterator it);
    private:
        void update();
    private:
        std::vector<T> m_push;
        std::vector<T> m_erase;
        
        bool m_locked = false;
    };
}

#include "safe_vector.inl"
