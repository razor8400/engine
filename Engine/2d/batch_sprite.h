#pragma once

#include "core/game_object.h"

namespace engine
{
    class sprite;
    
    class batch_sprite : public game_object
    {
    public:
        bool init() override;
        bool init(const std::string& file_name);
        bool init(const texture2d_ptr& texture);
        
        void add_child(game_object* obj) override;
        void remove_child(game_object* obj) override;
        
        void draw(const math::mat4& world) override;
        void render(const math::mat4& transform) override;
    private:
        texture2d_ptr m_texture;
        vector<sprite*> m_sprites;
        
        vector<math::vector3d> m_vertices;
        vector<math::vector4d> m_colors;
    };
}
