#pragma once

#include "engine.h"

struct editor_element
{
    std::string texture;
    std::string type_name;
    bool droppabe;
};

struct editor_cell
{
    int x, y;
    bool disabled = false;
    bool spawn_elements = false;
};
