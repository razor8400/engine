#pragma once

#include "engine.h"
#include "editor_data.h"

class editor_scene : public engine::scene
{
public:
    friend class editor_window;
    
    ~editor_scene();
    
    void update(float dt) override;
    void draw(engine::renderer* r) override;
    
    editor_cell* get_cell(int x, int y) const;
    
    math::vector2d cell_to_world(int x, int y) const;
    math::vector2d field_size() const;
    
    void clear_cells();
    
    std::string to_json() const;
    bool from_json(const std::string& json);
private:
    int m_rows = 10;
    int m_colls = 10;
    int m_cell_size = 64;
    
    mutable std::vector<editor_cell*> m_cells;
};
