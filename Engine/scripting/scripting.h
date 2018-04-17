#pragma once

#include "lua/lua.hpp"

namespace engine
{
    namespace scripting
    {
        static const char* start = "start";
        static const char* update = "update";
        static const char* stop = "stop";
        
        lua_State* create_state();
        void close_state(lua_State* state);
        void register_objects(lua_State* state);
        
        void load_script(lua_State* state, const char* buffer, size_t size, const std::string& name);
        void call_method(lua_State* state, const std::string& class_name, const std::string& method);
        void create_class(lua_State* state, const std::string& class_name);
        
        template<class T>
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, T* data);
    }
}

#include "scripting.inl"

