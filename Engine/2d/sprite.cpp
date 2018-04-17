#include "common.h"
#include "resources/texture2d.h"
#include "resources/resources_manager.h"
#include "sprite.h"

namespace engine
{
    IMPLEMENT_INHERITED_CLASS(sprite, game_object);
    
    sprite* sprite::create(const std::string& file_name)
    {
        auto obj = ref::create<sprite>();
        auto texture = resources_manager::instance().load_resource_from_file<texture2d>(file_name);
        
        if (obj->init(texture))
            return obj;
        
        return nullptr;
    }
    
    sprite* sprite::create(const texture2d_ptr& texture)
    {
        auto obj = ref::create<sprite>();
        
        if (obj->init(texture))
            return obj;
        
        return nullptr;
    }
    
    bool sprite::init(const texture2d_ptr& texture)
    {
        if (!texture || !game_object::init())
            return false;
        
        m_shader_program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_texture_position_color);
        set_texture(texture);
            
        return true;
    }
    
    void sprite::render(const math::mat4& world)
    {
        if (m_texture)
        {
            m_texture->set_color(math::vector4d(m_color.x, m_color.y, m_color.z, m_opacity / 255.0f));
            m_texture->draw(transfrom(world), m_shader_program);
        }
        
        game_object::render(world);
    }
    
    void sprite::set_texture(const texture2d_ptr& texture)
    {
        m_texture = texture;
        m_size.x = (float)m_texture->get_width();
        m_size.y = (float)m_texture->get_height();
    }
}
