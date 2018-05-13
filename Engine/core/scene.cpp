#include "common.h"
#include "scene.h"

#include "renderer/render_command.h"
#include "renderer/renderer.h"

namespace engine
{
    IMPLEMENT_INHERITANCE_INFO(scene, game_object);
    
    void scene::draw(renderer* r)
    {
        for (auto& obj : m_children)
            obj->draw(r, m_transform);

#if DEBUG_DRAW
		auto world = transform(r->get_world());

		for (auto& obj : m_children)
			obj->debug_draw(r, world);
#endif
    }
}
