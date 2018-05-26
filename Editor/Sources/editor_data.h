#pragma once

#include "engine.h"

enum element_layer
{
    underground = 1,
    ground,
    gameplay,
    blockers,
    top
};

static const char* layers_str[] = { "underground", "ground", "gameplay", "blockers", "top" };

struct editor_element
{
    std::string texture;
    std::string type_name;
    element_layer layer;
    bool dropable;
};

struct editor_cell
{
    bool disabled = false;
    bool spawn_elements = false;
    
    std::map<element_layer, std::string> elements;
};

static std::string layer_to_string(element_layer layer)
{
    return layers_str[layer - 1];
}

static element_layer string_to_layer(const std::string& layer)
{
    static const int size = 5;
    
    for (int i = 0; i < size; ++i)
    {
        if (layers_str[i] == layer)
            return (element_layer)i;
    }
    
    return element_layer::top;
}
