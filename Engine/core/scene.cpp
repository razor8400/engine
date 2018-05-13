#include "common.h"
#include "scene.h"

namespace engine
{
    IMPLEMENT_INHERITANCE_INFO(scene, game_object);
    
    void scene::draw(renderer* r)
    {
        for (auto& obj : m_children)
            obj->draw(r, m_transform);
    }
}
