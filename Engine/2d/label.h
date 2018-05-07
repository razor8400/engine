#pragma once

#include "core/game_object.h"

namespace engine
{
    class label : public game_object
    {
    public:
        bool init() override;
        bool init(const std::string& font_name);
        bool init(const std::string& font_name, int font_size);
        bool init(const std::string& font_name, int font_size, const std::string& caption);
        
        void set_font(const std::string& font_name);
        
        const font_ttf_ptr& get_font() const { return m_font; }
        void set_font(const font_ttf_ptr& font) { m_font = font; }
        
        const std::string& get_caption() const { return m_caption; }
        void set_caption(const std::string& caption) { m_caption = caption; }
        
        const math::vector4d& get_color() const { return m_color; }
        void set_color(const math::vector4d& color) { m_color = color; }
        
        void render(const math::mat4& t) override;
    private:
        std::string m_caption;
        math::vector4d m_color;
        int m_font_size;
        font_ttf_ptr m_font;
    };
}
