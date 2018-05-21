#pragma once

#include "editor_data.h"

class editor_scene;
class editor_element;
class editor_window;

class editor
{
public:    
    static editor& instance();
    
    void new_scene();
    void save_scene();
    bool load_scene();
    void load_elements();
public:
    editor_scene* m_current_scene = nullptr;
    editor_window* m_main_window = nullptr;
    
    std::vector<editor_element*> m_elements;
};
