#include "layer.h"
#include "core/application.h"

namespace engine
{
    bool layer::init()
    {
        m_size = application::instance().get_win_size();
        m_anchor = math::vector3d::zero;
        
        return game_object::init();
    }
}
