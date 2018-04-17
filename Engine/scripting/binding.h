#pragma once

#include "scripting.h"

namespace engine
{
    namespace scripting
    {
        namespace game_object
        {
            int create(lua_State* L);
            int destroy(lua_State* L);
            
            int add_child(lua_State* L);
            int remove_child(lua_State* L);
            int remove_from_parent(lua_State* L);
            
            int add_component(lua_State* L);
            int remove_component(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "add_child", add_child },
                { "remove_child", remove_child },
                { "remove_from_parent", remove_from_parent },
                { "add_component", add_component },
                { "remove_component", remove_component },
                { "__gc", destroy },
                { NULL, NULL }
            };
        }
        
        namespace sprite
        {
            int create(lua_State* L);
            int set_color(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "set_color", set_color },
                { NULL, NULL }
            };
        }
        
        namespace scene
        {
            int create(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { NULL, NULL }
            };
        }
    }
}
