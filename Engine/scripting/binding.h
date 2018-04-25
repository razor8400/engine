#pragma once

#include "scripting.h"

namespace engine
{
    namespace scripting
    {
        namespace functions
        {
            int load_script(lua_State* L);
            int debug_log(lua_State* L);
        }
        
        namespace vector
        {
            void push(lua_State* L, float x, float y, float z);
            int create(lua_State* L, float x, float y, float z);
            math::vector3d get(lua_State* L, int n);
        }
        
        namespace game
        {
            int get_mouse_location(lua_State* L);
            int get_win_size(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "get_mouse_location", get_mouse_location },
                { "get_win_size", get_win_size },
                { NULL, NULL, }
            };
        }
        
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
            
            int set_tag(lua_State* L);
            int get_tag(lua_State* L);
            
            int set_opacity(lua_State* L);
            int get_opacity(lua_State* L);
            
            int get_children_count(lua_State* L);
            int get_parent(lua_State* L);
            
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
				{ "set_tag", set_tag },
				{ "get_tag", get_tag },
                { "set_opacity", set_opacity },
                { "get_opacity", get_opacity },
                { "get_children_count", get_children_count },
                { "get_parent", get_parent },
                { "__gc", destroy },
                { NULL, NULL }
            };
        }
        
        namespace sprite
        {
            int create(lua_State* L);
            int set_color(lua_State* L);
            int get_color(lua_State* L);

            int set_texture(lua_State* L);
            int set_alpha(lua_State* L);
            int get_alpha(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "set_color", set_color },
                { "get_color", get_color },
                { "set_texture", set_texture },
                { "set_alpha", set_alpha },
                { "get_alpha", get_alpha },
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
        
        namespace box_collider2d
        {
            int create(lua_State* L);
            int destroy(lua_State* L);
            int on_click(lua_State* L);
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "on_click", on_click },
                { "__gc", destroy },
                { NULL, NULL }
            };
        }
    }
}
