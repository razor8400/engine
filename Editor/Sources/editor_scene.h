#pragma once

#include "engine.h"
#include "editor_data.h"

class editor_scene : public engine::scene
{
public:
    friend class editor_window;
    
    editor_scene();
    ~editor_scene();
    
    void on_enter();
    void on_exit();
    void update(float dt) override;
    void draw(engine::renderer* r) override;
    
    editor_cell* get_cell(int x, int y) const;
    
    math::vector2d cell_to_world(int x, int y) const;
    math::vector2d field_size() const;
    
    void clear_cells();
    bool on_touch_began();
    void on_touch_moved();
    void on_touch_ended();
    
    std::string to_json() const;
    bool from_json(const std::string& json);
private:
    int m_rows = 10;
    int m_colls = 10;
    int m_cell_size = 64;
    std::string m_selected_item;
    
    engine::touch_listener* m_listener = nullptr;
    
    mutable std::vector<editor_cell*> m_cells;
};
