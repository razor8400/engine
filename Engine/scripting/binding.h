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

			int set_enabled(lua_State* L);
			int get_enabled(lua_State* L);

			int set_position(lua_State* L);
			int get_position(lua_State* L);
			
			int set_rotation(lua_State* L);
			int get_rotation(lua_State* L);

			int set_scale(lua_State* L);
			int get_scale(lua_State* L);

			int set_size(lua_State* L);
			int get_size(lua_State* L);

			int set_anchor(lua_State* L);
			int get_anchor(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "add_child", add_child },
                { "remove_child", remove_child },
                { "remove_from_parent", remove_from_parent },
                { "add_component", add_component },
                { "remove_component", remove_component },
				{ "set_enabled", set_enabled },
				{ "get_enabled", get_enabled },
				{ "set_position", set_position },
				{ "get_position", get_position },
				{ "set_rotation", set_rotation },
				{ "get_rotation", get_rotation },
				{ "set_scale", set_scale },
				{ "get_scale", get_scale },
				{ "set_size", set_size },
				{ "get_size", get_size },
				{ "set_anchor", set_anchor },
				{ "get_anchor", get_anchor },
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
