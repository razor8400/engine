#include "editor_scene.h"
#include "editor.h"
#include "nlohmann/json.hpp"

editor_scene::editor_scene()
{
    m_listener = ref::create<engine::touch_listener>();
    m_listener->retain();
    
    m_listener->touch_began = std::bind(&editor_scene::on_touch_began, this);
    m_listener->touch_moved = std::bind(&editor_scene::on_touch_moved, this);
    m_listener->touch_ended = std::bind(&editor_scene::on_touch_ended, this);
}

editor_scene::~editor_scene()
{
    m_listener->release();
    clear_cells();
}

void editor_scene::clear_cells()
{
    std::for_each(m_cells.begin(), m_cells.end(), std::default_delete<editor_cell>());
    m_cells.clear();
}

bool editor_scene::on_touch_began()
{
    auto location = global_to_local(engine::director::instance().get_mouse_location());
    auto tile = world_to_cell(location.x, location.y);
    auto cell = get_cell(tile.x, tile.y);
    
    if (m_selected_item.size() > 0 && cell != nullptr)
        on_cell_clicked(cell);
    
    return true;
}

void editor_scene::on_cell_clicked(editor_cell* cell)
{
    static std::map<std::string, std::function<void(editor_cell*)>> handlers;
    
    if (handlers.empty())
    {
        handlers["clear"] = [](editor_cell* cell)
        {
            cell->elements.clear();
            cell->spawn_elements = false;
            cell->disabled = false;
        };
        
        handlers["disable"] = [](editor_cell* cell)
        {
            cell->disabled = !cell->disabled;
        };
        
        handlers["spawn"] = [](editor_cell* cell)
        {
            cell->spawn_elements = !cell->spawn_elements;
        };
    }
    
    auto it = handlers.find(m_selected_item);
    
    if (it != handlers.end())
    {
        it->second(cell);
    }
    else
    {
        auto data = editor::instance().find_element(m_selected_item);
        
        if (data)
            cell->elements[data->layer] = data->type_name;
    }
}

void editor_scene::on_touch_moved()
{
    
}

void editor_scene::on_touch_ended()
{
    
}

void editor_scene::on_enter()
{
    scene::on_enter();
    engine::touch_dispatcher::instance().add_touch_listener(m_listener);
}

void editor_scene::on_exit()
{
    scene::on_exit();
    engine::touch_dispatcher::instance().remove_touch_listener(m_listener);
}

void editor_scene::update(float dt)
{
    auto size = field_size();
    set_position(-size / 2);
    set_size(size);
    
    scene::update(dt);
}

void editor_scene::draw(engine::renderer* r)
{
    scene::draw(r);
    
    auto command = engine::custom_render_command::create([=]()
    {
        auto program = gl::shaders_manager::instance().get_program(gl::shader_program::shader_position_color);
        auto size = field_size();
        auto model_view_position = transform(r->get_world());
        
        for (int x = 0; x < m_colls; ++x)
        {
            for (int y = 0; y < m_rows; ++y)
            {
                auto cell = get_cell(y, x);
                
                if (cell->disabled)
                    continue;
                
                program->use(model_view_position);
                
                gl::draw_solid_rect(y * m_cell_size, x * m_cell_size, m_cell_size, m_cell_size, math::vector3d(0.0f, 0.3f, 0.0f));
                
                std::vector<std::string> textures;
                
                if (cell->spawn_elements)
                    textures.push_back("spawn.png");
                
                for (auto it : cell->elements)
                {
                    auto data = editor::instance().find_element(it.second);
                    
                    if (data)
                        textures.push_back(data->texture);
                }
                
                for (auto str : textures)
                {
                    auto texture = engine::resources_manager::instance().load_resource_from_file<engine::texture2d>(str);
                    
                    if (texture)
                    {
                        auto rect = math::rect(cell_to_world(y, x), math::vector2d(m_cell_size, m_cell_size));
                        texture->draw(rect, model_view_position);
                    }
                }
            }
        }
        
        program->use(model_view_position);
        
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
                
                if (m_cells[y * m_colls + x] == nullptr)
                    m_cells[y * m_colls + x] = cell;
            }
        }
    }
    
    return m_cells[index];
}

math::vector2d editor_scene::world_to_cell(int x, int y) const
{
    return math::vector2d(x / m_cell_size, y / m_cell_size);
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
    
    for (int y = 0; y < m_rows; ++y)
    {
        for (int x = 0; x < m_colls; ++x)
        {
            auto cell = get_cell(x, y);
            
            assert(cell);
            
            nlohmann::json data;
            
            for (auto it : cell->elements)
            {
                auto layer = layer_to_string(it.first);
                data["elements"][layer] = it.second;
            }
            
            data["disabled"] = cell->disabled;
            data["spawn"] = cell->spawn_elements;

            json["cells"].push_back(data);
        }
    }
    
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
        
        auto cells = json["cells"];
        
        for (auto data : cells)
        {
            auto cell = new editor_cell();
            
            cell->disabled = data["disabled"];
            cell->spawn_elements = data["spawn"];
            
            for (auto key : layers_str)
            {
                auto layer = string_to_layer(key);
                if (data["elements"][key].is_string())
                    cell->elements[layer] = data["elements"][key];
            }
            
            m_cells.push_back(cell);
        }
        
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
