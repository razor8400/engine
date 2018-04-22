#include "common.h"
#include "touch_dispatcher.h"
#include "touch_listener.h"

namespace engine
{
    touch_dispatcher& touch_dispatcher::instance()
    {
        static touch_dispatcher instance;
        return instance;
    }
    
    touch_dispatcher::touch_dispatcher()
    {
        
    }
    
    touch_dispatcher::~touch_dispatcher()
    {
        
    }
    
    void touch_dispatcher::add_touch_listener(touch_listener* listener)
    {
        m_listeners.push_back(listener);
    }
    
    void touch_dispatcher::remove_touch_listener(touch_listener* listener)
    {
        m_listeners.erase(listener);
    }
    
    void touch_dispatcher::on_touch_began()
    {
        for (auto listener : m_listeners)
        {
            if (listener->on_touch_began())
            {
                m_current_listener = listener;
                break;
            }
        }
    }
    
    void touch_dispatcher::on_touch_moved()
    {
        if (m_current_listener)
            m_current_listener->on_touch_moved();
    }
    
    void touch_dispatcher::on_touch_ended()
    {
        if (m_current_listener)
            m_current_listener->on_touch_ended();
    }
}
