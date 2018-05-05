#include "common.h"
#include "sprite.h"
#include "batch_sprite.h"

namespace engine
{
    bool batch_sprite::init()
    {
        if (!game_object::init())
            return false;
        
        m_shader_program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_texture_position_color);
        
        return true;
    }
    
    bool batch_sprite::init(const std::string& file_name)
    {
        auto texture = resources_manager::instance().load_resource_from_file<texture2d>(file_name);
        
        return init(texture);
    }
    
    bool batch_sprite::init(const texture2d_ptr& texture)
    {
        if (!texture || !init())
            return false;
        
        m_texture = texture;
        
        return true;
    }
    
    void batch_sprite::add_child(game_object* obj)
    {
        auto sprite = dynamic_cast<class sprite*>(obj);
        
        assert(sprite && sprite->get_texture() == m_texture);
        
        m_sprites.push_back(sprite);
        
        game_object::add_child(obj);
    }
    
    void batch_sprite::remove_child(game_object* obj)
    {
        auto sprite = dynamic_cast<class sprite*>(obj);
        
        assert(sprite);
        
        m_sprites.erase(sprite);
        
        game_object::remove_child(obj);
    }
    
    void batch_sprite::render(const math::mat4& transform)
    {
        game_object::render(transform);
    }
    
    void batch_sprite::draw(const math::mat4& parent)
    {
        if (!m_enabled)
            return;
        
        auto model_view_transform = transform(parent);
        
        m_vertices.clear();
        
        for (auto obj : m_sprites)
        {
            auto transform = obj->transform(model_view_transform);
            
            auto p1 = math::transform_point(math::vector2d::zero, transform);
            auto p2 = math::transform_point(math::vector2d(m_size.x, 0), transform);
            auto p3 = math::transform_point(m_size, transform);
            auto p4 = math::transform_point(math::vector2d(0, m_size.y), transform);
            
            m_vertices.push_back(p1);
            m_vertices.push_back(p2);
            m_vertices.push_back(p3);
            m_vertices.push_back(p4);
            
            auto color = obj->get_color();
            auto alpha = obj->get_alpha();
            auto color4 = math::vector4d(color.x, color.y, color.z, alpha);
            
            m_colors.push_back(color4);
            m_colors.push_back(color4);
            m_colors.push_back(color4);
            m_colors.push_back(color4);
        }
        
        render(model_view_transform);
    }
}
