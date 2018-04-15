#pragma once

#include "scripting.h"
#include "core/game_object.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, T* data)
        {
            lua_getglobal(state, table.c_str());
            
            T** obj = (T**)lua_newuserdata(state, sizeof(T*));
            
            *obj = data;
            data->retain();
            
            luaL_getmetatable(state, T::type_name());
            lua_setmetatable(state, -2);
            
            lua_setfield(state, -2, field.c_str());
        }
    }
}
