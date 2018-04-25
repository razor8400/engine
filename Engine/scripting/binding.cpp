#include "common.h"
#include "scripting.h"

#include "utils/file_utils.h"
#include "components/component.h"
#include "components/box_collider2d.h"

#include "core/application.h"
#include "core/director.h"
#include "core/game_object.h"
#include "core/scene.h"

#include "2d/sprite.h"

#define CHECK_TOP(L, TOP)\
auto n = lua_gettop(L);\
if (n < TOP)\
    return 0;

namespace engine
{
    namespace scripting
    {
        namespace functions
        {
            int load_script(lua_State* L)
            {
                if (lua_isstring(L, 1))
                {
                    auto script = lua_tostring(L, 1);
                    std::vector<char> data;
                    
                    logger() << "[scripting] load script:" << script;
                    
                    CLEAR_TOP(L)
                    
                    if (file_utils::read_resource_file(script, &data))
                    {
                        if (scripting::load_script(L, data.data(), data.size(), script))
                            return 1;
                    }
                }
                
                return 0;
            }
            
            int debug_log(lua_State* L)
            {
                if (lua_isstring(L, 1))
                    logger() << "[lua] " << lua_tostring(L, 1);
                
                if (lua_isnil(L, 1))
                    logger() << "[lua] nil";
                
                CLEAR_TOP(L)
                
                return 0;
            }
        }

		namespace vector
		{
            void push(lua_State* L, float x, float y)
            {
                lua_newtable(L);
                lua_pushnumber(L, x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, y);
                lua_setfield(L, -2, "y");
            }
            
            void push(lua_State* L, float x, float y, float z)
            {
                lua_newtable(L);
                lua_pushnumber(L, x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, z);
                lua_setfield(L, -2, "z");
            }
            
			int create(lua_State* L, float x, float y, float z)
			{
                push(L, x, y, z);

				return 1;
			}

			math::vector3d get(lua_State* L, int n)
			{
				if (lua_istable(L, n + 1))
				{
					lua_getfield(L, n + 1, "x");
					auto x = get_number(L, n + 2);

					lua_getfield(L, n + 1, "y");
					auto y = get_number(L, n + 3);
					
					lua_getfield(L, n + 1, "z");
					auto z = get_number(L, n + 4);
					
					return math::vector3d(x, y, z);
				}
				
				auto x = get_number(L, n + 1);
				auto y = get_number(L, n + 2);
				auto z = get_number(L, n + 3);

				return math::vector3d(x, y, z);
			}
		}

		namespace color
		{
			int create(lua_State* L, float r, float g, float b)
			{
				lua_newtable(L);
				lua_pushnumber(L, r);
				lua_setfield(L, -2, "r");
				lua_pushnumber(L, g);
				lua_setfield(L, -2, "g");
				lua_pushnumber(L, b);
				lua_setfield(L, -2, "b");

				return 1;
			}
            
            math::vector3d get(lua_State* L, int n)
            {
                if (lua_istable(L, n + 1))
                {
                    lua_getfield(L, n + 1, "r");
                    auto r = get_number(L, n + 2);
                    
                    lua_getfield(L, n + 1, "g");
                    auto g = get_number(L, n + 2);
                    
                    lua_getfield(L, n + 1, "b");
                    auto b = get_number(L, n + 2);
                    
                    return math::vector3d(r, g, b);
                }
                
                auto r = get_number(L, n + 1);
                auto g = get_number(L, n + 2);
                auto b = get_number(L, n + 3);
                
                return math::vector3d(r, g, b);
            }
		}
        
        namespace game
        {
            int get_mouse_location(lua_State* L)
            {
				auto location = application::instance().get_mouse_location();
                
                vector::push(L, location.x, location.y);

                return 1;
            }
            
            int get_win_size(lua_State* L)
            {
                auto location = application::instance().get_win_size();
                
                vector::push(L, location.x, location.y);
                
                return 1;
            }
        }

        namespace game_object
        {
            template<class T, class ...Args>
            int create(lua_State* L, Args... args)
            {
                auto obj = engine::game_object::create<T>(args...);
                
                if (!obj)
                    return 0;
                
                push_ref(L, obj);
                return 1;
            }
            
            int create(lua_State* L)
            {
                return create<engine::game_object>(L);
            }
            
            int destroy(lua_State* L)
            {
                return scripting::destroy_ref<engine::game_object>(L);
            }
            
            int add_child(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto child = scripting::get<engine::game_object>(L, 2);
                
                if (obj && child)
                    obj->add_child(child);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int remove_child(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto child = scripting::get<engine::game_object>(L, 2);
                
                if (obj && child)
                    obj->remove_child(child);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int remove_from_parent(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                if (obj)
                    obj->remove_from_parent();
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int add_component(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto component = scripting::get<engine::component>(L, 2);
                
                if (obj && component)
                    obj->add_component(component);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int remove_component(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto component = scripting::get<engine::component>(L, 1);
                
                if (obj && component)
                    obj->remove_component(component);
                
                CLEAR_TOP(L);
                
                return 0;
            }

			int set_enabled(lua_State* L)
			{
				CHECK_TOP(L, 2);

				if (!lua_isboolean(L, 2))
					return 0;

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (obj)
					obj->set_enabled(lua_toboolean(L, 2) > 0);
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_enabled(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);

				if (obj)
				{
					lua_pushboolean(L, obj->get_enabled());
					return 1;
				}

				return 1;
			}

			int set_position(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;
                
				obj->set_position(vector::get(L, 1));
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_position(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;
                
                CLEAR_TOP(L);

				auto position = obj->get_position();

				return vector::create(L, position.x, position.y, position.z);
			}

			int set_rotation(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

				obj->set_rotation(vector::get(L, 1));
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_rotation(lua_State* L)
			{
                CHECK_TOP(L, 1);
                
				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;
                
                CLEAR_TOP(L);

				auto rotation = obj->get_rotation();

				return vector::create(L, rotation.x, rotation.y, rotation.z);
			}

			int set_scale(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

				obj->set_scale(vector::get(L, 1));
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_scale(lua_State* L)
			{
                CHECK_TOP(L, 1);
                
				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;
                
                CLEAR_TOP(L);

				auto scale = obj->get_scale();

				return vector::create(L, scale.x, scale.y, scale.z);
			}

			int set_size(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

				obj->set_size(vector::get(L, 1));
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_size(lua_State* L)
			{
                CHECK_TOP(L, 1);
                
				auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);

				if (!obj)
					return 0;

				auto size = obj->get_size();

				return vector::create(L, size.x, size.y, size.z);
			}

			int set_anchor(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

				obj->set_anchor(vector::get(L, 1));
                
                CLEAR_TOP(L);

				return 0;
			}

			int get_anchor(lua_State* L)
			{
                CHECK_TOP(L, 1);
                
				auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);

				if (!obj)
					return 0;

				auto anchor = obj->get_anchor();

				return vector::create(L, anchor.x, anchor.y, anchor.z);
			}
            
            int set_tag(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                if (!obj)
                    return 0;
                
                int tag = (int)lua_tointeger(L, 2);
                
                obj->set_tag(tag);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int get_tag(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                lua_pushnumber(L, obj->get_tag());
                
                return 1;
            }
            
            int set_opacity(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                if (!obj)
                    return 0;
                
                int opacity = get_integer(L, 2);
                
                obj->set_opacity(opacity);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int get_opacity(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                lua_pushinteger(L, obj->get_opacity());
                
                return 1;
            }
            
            int get_children_count(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                lua_pushnumber(L, obj->get_children_count());
                
                return 1;
            }
            
            int get_parent(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                push_ref<engine::game_object>(L, obj->get_parent());
                
                return 1;
            }
        }
        
        namespace sprite
        {
            int create(lua_State* L)
            {
                if (lua_isstring(L, 1))
                {
                    auto texture = lua_tostring(L, 1);
                    
                    CLEAR_TOP(L);
                    
                    return game_object::create<engine::sprite>(L, texture);
                } 
                
                return game_object::create<engine::sprite>(L);
            }
            
            int set_color(lua_State* L)
            {
                CHECK_TOP(L, 1);

                auto obj = scripting::get<engine::sprite>(L, 1);
                
                if (!obj)
                    return 0;
                
                obj->set_color(vector::get(L, 1));
                
                CLEAR_TOP(L);
                
                return 0;
            }

            int get_color(lua_State* L)
            {
                CHECK_TOP(L, 1);

                auto obj = scripting::get<engine::sprite>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                auto color = obj->get_color();
                
                return color::create(L, color.x, color.y, color.z);
            }

            int set_texture(lua_State* L)
            {
                CHECK_TOP(L, 1);

                auto obj = scripting::get<engine::sprite>(L, 1);
                
                if (!obj || !lua_isstring(L, 2))
                    return 0;
                
                auto texture = lua_tostring(L, 2);
                obj->set_texture(texture);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int set_alpha(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::sprite>(L, 1);
                
                if (!obj)
                    return 0;
                
                auto alpha = get_number(L, 2);
                obj->set_alpha(alpha);
                
                CLEAR_TOP(L);
                
                return 0;
            }
            
            int get_alpha(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::sprite>(L, 1);
                
                CLEAR_TOP(L);
                
                if (!obj)
                    return 0;
                
                auto alpha = obj->get_alpha();
                
                lua_pushnumber(L, alpha);
                
                return 1;
            }
        }
        
        namespace scene
        {
            int create(lua_State* L)
            {
                return game_object::create<engine::game_object>(L);
            }
        }
        
        namespace box_collider2d
        {
            int create(lua_State* L)
            {
                auto w = lua_tonumber(L, 1);
                auto h = lua_tonumber(L, 2);
                
                CLEAR_TOP(L);
                
                auto collider = ref::create<engine::box_collider2d>();
                
                collider->set_size(math::vector2d(w, h));
                push_ref(L, collider);
                
                return 1;
            }
            
            int destroy(lua_State* L)
            {
                return destroy_ref<engine::box_collider2d>(L);
            }
            
            int on_click(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto collider = get<engine::box_collider2d>(L, 1);
                auto mouse = vector::get(L, 1);
                
                CLEAR_TOP(L);
                
                if (collider)
                {
                    auto result = collider->on_click(math::vector2d(mouse.x, mouse.y));
                    lua_pushboolean(L, result);
                }
                
                return 1;
            }
        }
    }
}
