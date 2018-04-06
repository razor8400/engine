#include "common.h"
#include "resources/texture2d.h"
#include "resources/resources_manager.h"
#include "sprite.h"

namespace engine
{
    std::shared_ptr<sprite> sprite::create(const std::string& file_name)
    {
        auto obj = std::make_shared<sprite>();
        
        if (obj->init(file_name))
            return obj;
        
        return nullptr;
    }
    
    std::shared_ptr<sprite> sprite::create(const texture2d_ptr& texture)
    {
        auto obj = std::make_shared<sprite>();
        
        if (obj->init(texture))
            return obj;
        
        return nullptr;
    }
    
    bool sprite::init(const std::string& texture_file_name)
    {
        if (!game_object::init())
            return false;
        
        resource_loader_callback complete_callback = [this](const resource_ptr& resource)
        {
            auto texture = std::dynamic_pointer_cast<texture2d>(resource);
            
            if (texture)
                set_texture(texture);
        };
        
        resource_error_callback error_callback = [](const char* error)
        {
            log(error);
        };
        
        resources_manager::instance().load_resource_from_file<texture2d>(texture_file_name, complete_callback, error_callback);
        
        return true;
    }
    
    bool sprite::init(const texture2d_ptr& texture)
    {
        if (!texture || !game_object::init())
            return false;
        
        set_texture(texture);
            
        return true;
    }
    
    void sprite::render(const math::mat4& world)
    {
        if (m_texture)
        {
            auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_texture_position_color);
            program->use(world * world_transform());
            
            m_texture->draw();
        }
    }
    
    void sprite::set_texture(const texture2d_ptr& texture)
    {
        m_texture = texture;
        m_size.x = (float)m_texture->get_width();
        m_size.y = (float)m_texture->get_height();
    }
}
