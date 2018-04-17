#pragma once

#include "scripting.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "2d/sprite.h"

namespace engine
{
    namespace scripting
    {
        namespace game_object
        {
            static int create(lua_State* L)
            {
                return scripting::create_ref<engine::game_object>(L);
            }
            
            static int destroy(lua_State* L)
            {
                return scripting::destroy_ref<engine::game_object>(L);
            }
            
            static int add_child(lua_State* L)
            {
                auto n = lua_gettop(L);
                
                if (n != 2)
                    return 0;
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto child = scripting::get<engine::game_object>(L, 2);
                
                if (obj && child)
                    obj->add_child(child);
                
                return 1;
            }
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "add_child", add_child },
                { "__gc", destroy },
                { NULL, NULL }
            };
        }
        
        namespace sprite
        {
            static int create(lua_State* L)
            {
                return scripting::create_ref<engine::sprite>(L);
            }
            
            static int set_color(lua_State* L)
            {
                auto n = lua_gettop(L);
                
                if (n != 4)
                    return 0;

                auto obj = scripting::get<engine::sprite>(L, 1);
                auto r = lua_tonumber(L, 1);
                auto g = lua_tonumber(L, 2);
                auto b = lua_tonumber(L, 3);
                
                if (obj)
                    obj->set_color(math::vector3d(r, g, b));
                
                return 1;
            }
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "set_color", set_color },
                { NULL, NULL }
            };
        }
    }
}
