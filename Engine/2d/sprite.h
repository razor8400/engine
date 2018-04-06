#pragma once

#include "core/game_object.h"

namespace engine
{    
    class sprite : public game_object
    {
    public:
        static std::shared_ptr<sprite> create(const std::string& file_name);
        static std::shared_ptr<sprite> create(const texture2d_ptr& texture);
        
        bool init(const std::string& texture_file_name);
        bool init(const texture2d_ptr& texture);
        void render(const math::mat4& world) override;
        void set_texture(const texture2d_ptr& texture);
    private:
        texture2d_ptr m_texture;
    };
}
