#pragma once

#include "ref.h"

namespace engine
{
    class camera : public ref
    {
    public:
        void set_projection_mode(projection_mode mode);
        
        void set_near_plane(float near_plane);
        void set_far_plane(float far_plane);
        void set_field_of_view(float field_of_view);
        
        void set_position(const math::vector3d& position);
        void set_target(const math::vector3d& target);
        
        const math::mat4& get_projection() const { return m_projection; }
        void update_projection();
    private:
        float m_near_plane = -1000;
        float m_far_plane = 1000;
        float m_field_of_view = 0;
        
        math::vector3d m_position = math::vector3d(0, 0, -1);
        math::vector3d m_target = math::vector3d::zero;
        
        projection_mode m_projection_mode = projection_mode::ortographic;
        
        math::mat4 m_projection;
    };
}
