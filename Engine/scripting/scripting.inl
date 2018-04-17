#pragma once

#include "scripting.h"
#include "core/game_object.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        static T* get(lua_State* L, int n)
        {
            T** obj = (T**)lua_touserdata(L, n);
            return dynamic_cast<T*>(*obj);
        }
        
        template<class T>
        static T* push(lua_State* L, T* obj)
        {
            T** data = (T**)lua_newuserdata(L, sizeof(T*));
            *data = obj;
            
            return obj;
        }
        
        template<class T>
        static int create_ref(lua_State* L)
        {
            T* obj = push<T>(L, ref::create<T>());
            obj->retain();
            
            luaL_getmetatable(L, T::type_name());
            lua_setmetatable(L, -2);
            
            return 1;
        }
        
        template<class T>
        static int destroy_ref(lua_State* L)
        {
            auto obj = get<T>(L, 1);
            
            if (obj)
                obj->release();
            
            return 0;
        }
        
        template<class T>
        void push_to_table(lua_State* L, const std::string& table, const std::string& field, T* data)
        {
            lua_getglobal(L, table.c_str());
            
            T* obj = push<T>(L, data);
            obj->retain();
            
            luaL_getmetatable(L, T::type_name());
            lua_setmetatable(L, -2);
            
            lua_setfield(L, -2, field.c_str());
        }
    }
}
