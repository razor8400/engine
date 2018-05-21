#include "editor_scene.h"
#include "nlohmann/json.hpp"

editor_scene::~editor_scene()
{
    clear_cells();
}

void editor_scene::clear_cells()
{
    std::for_each(m_cells.begin(), m_cells.end(), std::default_delete<editor_cell>());
}

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
        
        for (int x = 0; x < m_colls; ++x)
        {
            for (int y = 0; y < m_rows; ++y)
            {
                auto cell = get_cell(x, y);
                
                if (cell->disabled)
                    continue;
                
                gl::draw_solid_rect(y * m_cell_size, x * m_cell_size, m_cell_size, m_cell_size, math::vector3d(0.0f, 0.3f, 0.0f));
            }
        }
        
        for (int i = 1; i < m_colls; ++i)
            gl::draw_line(0, i * m_cell_size, size.x, i * m_cell_size);
        
        for (int i = 1; i < m_rows; ++i)
            gl::draw_line(i * m_cell_size, 0, i * m_cell_size, size.y);
    });
    
    r->add_command(command);
}

editor_cell* editor_scene::get_cell(int x, int y) const
{
    if (x < 0 || x >= m_colls || y < 0 || y >= m_rows)
        return nullptr;
    
    auto index = y * m_colls + x;
    
    if (m_colls * m_rows >= m_cells.size())
    {
        m_cells.resize(m_colls * m_rows);
        
        for (int x = 0; x < m_colls; ++x)
        {
            for (int y = 0; y < m_rows; ++y)
            {
                auto cell = new editor_cell();
                
                cell->x = x;
                cell->y = y;
                
                if (m_cells[y * m_colls + x] == nullptr)
                    m_cells[y * m_colls + x] = cell;
            }
        }
    }
    
    return m_cells[index];
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
        
        clear_cells();
        
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
