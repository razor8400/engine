#pragma once

#include "engine.h"

class editor_scene : public engine::scene
{
public:
    friend class editor_window;
    
    void update(float dt) override;
    void draw(engine::renderer* r) override;
    
    math::vector2d cell_to_world(int x, int y) const;
    math::vector2d field_size() const;
    
    std::string to_json() const;
    bool from_json(const std::string& json);
private:
    int m_rows = 10;
    int m_colls = 10;
    int m_cell_size = 64;
};
