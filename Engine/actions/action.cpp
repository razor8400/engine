#include "common.h"
#include "action.h"
#include "core/game_object.h"

namespace engine
{
    void action::update(float dt)
    {
        if (m_done)
            return;
        
        step(dt);
        
        if (action_done())
        {
            if (m_target)
                m_target->on_action_done(this);
            
            m_done = true;
        }
    }
    
    void action::start(game_object* target)
    {
        m_done = false;
        m_target = target;
    }
}
