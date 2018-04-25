#include "common.h"
#include "box_collider2d.h"
#include "core/game_object.h"
#include "core/director.h"

namespace engine
{
    IMPLEMENT_TYPE_INFO(box_collider2d)
    
    box_collider2d::box_collider2d()
    {
        
    }
    
    box_collider2d::box_collider2d(const math::vector2d& size) : m_size(size)
    {
        
    }
    
    bool box_collider2d::on_click(const math::vector2d& location) const
    {
        if (m_vertices.size() > 0)
        {
            auto world = director::instance().convert_screen_to_world(location);
            auto a = m_vertices[1];
            auto b = m_vertices[2];
            auto c = m_vertices[3];
            auto d = m_vertices[4];
            
            auto r = math::line_equation(a, b, math::vector2d(world.x, world.y));
            
            return false;
        }

        
        return false;
    }

    void box_collider2d::update(float dt)
    {
        update();
    }
    
    void box_collider2d::update()
    {
        if (!m_parent || !m_parent->get_enabled())
            return;
        
        auto transform = m_parent->get_transform();
        
        auto p1 = math::vector4d(0, 0, 0, 1) * transform;
        auto p2 = math::vector4d(m_size.x, 0, 0, 1) * transform;
        auto p3 = math::vector4d(m_size.x, m_size.y, 0, 1) * transform;
        auto p4 = math::vector4d(0, m_size.y, 0, 1) * transform;
        
        m_vertices.clear();
        m_vertices.push_back(math::vector2d(p1.x, p1.y));
        m_vertices.push_back(math::vector2d(p2.x, p2.y));
        m_vertices.push_back(math::vector2d(p3.x, p3.y));
        m_vertices.push_back(math::vector2d(p4.x, p4.y));
    }
}
