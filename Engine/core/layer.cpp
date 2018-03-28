#include "layer.h"
#include "application.h"

namespace engine
{
    bool layer::init()
    {
        m_size = application::instance().get_win_size();
        m_anchor = vector2d::zero;
        
        return game_object::init();
    }
}
