#include "common.h"
#include "camera.h"

namespace engine
{
    void camera::set_projection_mode(projection_mode mode)
    {
        m_projection_mode = mode;
        update_projection();
    }
    
    void camera::set_near_plane(float near_plane)
    {
        m_near_plane = near_plane;
        update_projection();
    }
    
    void camera::set_far_plane(float far_plane)
    {
        m_far_plane = far_plane;
        update_projection();
    }
    
    void camera::set_field_of_view(float field_of_view)
    {
        m_field_of_view = field_of_view;
        update_projection();
    }
    
    void camera::set_position(const math::vector3d& position)
    {
        m_position = position;
        update_projection();
    }
    
    void camera::set_direction(const math::vector3d& direction)
    {
        m_direction = direction;
        update_projection();
    }
    
    void camera::set_up(const math::vector3d& up)
    {
        m_up = up;
        update_projection();
    }
    
    void camera::update_projection()
    {
        auto win_size = application::instance().get_win_size();
        
        auto camera = math::mat4::look_at(m_position, m_direction, m_up);
        
        if (m_projection_mode == perspective)
        {
            m_projection = math::mat4::perspective(m_field_of_view, win_size.x / win_size.y, m_near_plane, m_far_plane) * camera;
        }
        else if (m_projection_mode == ortographic)
        {
            m_projection = math::mat4::ortographic(win_size.x, win_size.y, m_near_plane, m_far_plane) * camera;
        }
    }
}
