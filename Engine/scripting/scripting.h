#pragma once

#include "lua/lua.hpp"

#define CLEAR_TOP(L)\
lua_pop(L, lua_gettop(L));

namespace engine
{
    namespace scripting
    {
        static const char* start = "start";
        static const char* update = "update";
        static const char* stop = "stop";
        
        static const char* mouse_down = "mouse_down";
        static const char* mouse_move = "mouse_move";
        static const char* mouse_up = "mouse_up";
        
        lua_State* create_state();
        void close_state(lua_State* state);
        void register_objects(lua_State* state);
        
        bool load_script(lua_State* state, const char* buffer, size_t size, const std::string& name);
        void call_method(lua_State* state, const std::string& class_name, const std::string& method);
        void create_class(lua_State* state, const std::string& class_name);
        
        template<class T>
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, T* data);
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, const math::vector3d& v3);

		float get_number(lua_State* state, int n);
		int get_integer(lua_State* state, int n);
    }
}

#include "scripting.inl"

