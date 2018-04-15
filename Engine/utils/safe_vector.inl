#pragma once

#include "safe_vector.h"

namespace engine
{
    template<class T>
    void safe_vector<T>::lock()
    {
        m_locked = true;
    }
    
    template<class T>
    void safe_vector<T>::unlock()
    {
        m_locked = false;
        update();
    }
    
    template<class T>
    void safe_vector<T>::push_back(T obj)
    {
        m_push.push_back(obj);
        update();
    }
    
    template<class T>
    void safe_vector<T>::erase(typename base_class::const_iterator it)
    {
        m_erase.push_back(*it);
        update();
    }

    template<class T>
    void safe_vector<T>::update()
    {
        if (m_locked)
            return;
        
        for (auto obj : m_push)
            base_class::push_back(obj);
        
        for (auto obj : m_erase)
        {
            auto it = std::find(this->begin(), this->end(), obj);
            
            if (it != this->end())
                base_class::erase(it);
        }
        
        m_push.clear();
        m_erase.clear();
    }
}
