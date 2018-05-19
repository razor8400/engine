#include "editor_scene.h"
#include "nlohmann/json.hpp"

void editor_scene::update(float dt)
{
    scene::update(dt);
}

void editor_scene::draw(engine::renderer* r)
{
    scene::draw(r);
    
    auto command = engine::custom_render_command::create([=]()
    {
        auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_position_color);
        auto size = field_size();
        auto position = math::mat4::translate(-size.x / 2, -size.y / 2, 0);
        
        program->use(transform(r->get_world()) * position);
        
        for (int i = 1; i < m_colls; ++i)
            gl::draw_line(0, i * m_cell_size, size.x, i * m_cell_size);
        
        for (int i = 1; i < m_rows; ++i)
            gl::draw_line(i * m_cell_size, 0, i * m_cell_size, size.y);
    });
    
    r->add_command(command);
}

math::vector2d editor_scene::cell_to_world(int x, int y) const
{
    return math::vector2d(x * m_cell_size, y * m_cell_size);
}

math::vector2d editor_scene::field_size() const
{
    return math::vector2d(m_cell_size * m_rows, m_cell_size * m_colls);
}

std::string editor_scene::to_json() const
{
    nlohmann::json json;
    
    json["colls"] = m_colls;
    json["rows"] = m_rows;
    json["cell"] = m_cell_size;
    
    return json.dump();
}

bool editor_scene::from_json(const std::string& data)
{
    try
    {
        engine::logger() << "[editor_scene] parse json:\n" << data;
        
        auto json = nlohmann::json::parse(data);
        
        m_colls = json["colls"].get<int>();
        m_rows = json["rows"].get<int>();
        m_cell_size = json["cell"].get<int>();
        
        return true;
    }
    catch (const nlohmann::json::parse_error& e)
    {
        engine::logger() << "[editor_scene] " << e.what();
    }
    catch (const nlohmann::json::type_error& e)
    {
        engine::logger() << "[editor_scene] " << e.what();
    }
    return false;
}
