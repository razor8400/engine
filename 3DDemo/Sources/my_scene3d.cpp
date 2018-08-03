#include "my_scene3d.h"

using namespace engine;

void my_scene3d::on_enter()
{
    scene::on_enter();
    
    m_listener = ref::create<touch_listener>();
    m_listener->swallow_touches = true;
    m_listener->touch_began = std::bind(&my_scene3d::on_touch_began, this, std::placeholders::_1);
    m_listener->touch_moved = std::bind(&my_scene3d::on_touch_moved, this, std::placeholders::_1);
    m_listener->touch_ended = std::bind(&my_scene3d::on_touch_ended, this, std::placeholders::_1);
    
    touch_dispatcher::instance().add_touch_listener(m_listener);
}

void my_scene3d::on_exit()
{
    scene::on_exit();
    
    touch_dispatcher::instance().remove_touch_listener(m_listener);
}

bool my_scene3d::on_touch_began(const math::vector2d& location)
{
    return true;
}

void my_scene3d::on_touch_moved(const math::vector2d& location)
{
    if (m_mouse.lenght() > 0)
    {
        auto delta = location - m_mouse;
        
        m_camera_position += math::vector3d(delta.x, delta.y, 0.0f);
    }
    
    m_mouse = location;
}

void my_scene3d::on_touch_ended(const math::vector2d& location)
{
    
}

void my_scene3d::draw(engine::renderer* r)
{
    auto command = custom_render_command::create([=]()
    {
        auto model_view_position = transform(get_camera()->get_projection());
        
        auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_position_color);
        
        if (program)
            program->use(model_view_position);
        
        for (auto x = 1; x < m_size.x; ++x)
            gl::draw_line(x, 0, 0, x, 0, m_size.z, math::vector3d(0.0f, 0.7f, 0.0f));
        
        for (auto z = 1; z < m_size.z; ++z)
            gl::draw_line(0, 0, z, m_size.x, 0, z, math::vector3d(0.0f, 0.7f, 0.0f));
    });
    
    r->add_command(command);
    
    scene::draw(r);
}

void my_scene3d::update(float dt)
{
    scene::update(dt);
    
    if (m_camera_position.lenght() > 0)
    {
        auto camera = get_camera();
        
        auto position = camera->get_position() + m_camera_position * dt;

        camera->set_position(position);
        
        m_camera_position *= 0.9f;
    }
}
