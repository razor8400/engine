#include "common.h"
#include "scripting.h"

#include "components/component.h"

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
		namespace vector
		{
			int create(lua_State* L, float x, float y, float z)
			{
				lua_newtable(L);
				lua_pushnumber(L, x);
				lua_setfield(L, -2, "x");
				lua_pushnumber(L, y);
				lua_setfield(L, -2, "y");
				lua_pushnumber(L, z);
				lua_setfield(L, -2, "z");

				return 1;
			}

			math::vector3d get(lua_State* L, int n)
			{
				if (!lua_istable(L, -1))
					return math::vector3d::zero;

				int a = lua_getfield(L, n + 1, "x");
				auto x = lua_tonumber(L, n - 1);
				auto y = lua_tonumber(L, n + 2);
				auto z = lua_tonumber(L, n + 3);

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
		}

        namespace game_object
        {
            int create(lua_State* L)
            {
                return scripting::create_ref<engine::game_object>(L);
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
                
                return 0;
            }
            
            int remove_child(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto child = scripting::get<engine::game_object>(L, 2);
                
                if (obj && child)
                    obj->remove_child(child);
                
                return 0;
            }
            
            int remove_from_parent(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                
                if (obj)
                    obj->remove_from_parent();
                
                return 0;
            }
            
            int add_component(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto component = scripting::get<engine::component>(L, 1);
                
                if (obj && component)
                    obj->add_component(component);
                
                return 0;
            }
            
            int remove_component(lua_State* L)
            {
                CHECK_TOP(L, 2);
                
                auto obj = scripting::get<engine::game_object>(L, 1);
                auto component = scripting::get<engine::component>(L, 1);
                
                if (obj && component)
                    obj->remove_component(component);
                
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

				return 0;
			}

			int get_enabled(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

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

				return 0;
			}

			int get_position(lua_State* L)
			{
				CHECK_TOP(L, 1);

				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

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

				return 0;
			}

			int get_rotation(lua_State* L)
			{
				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

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

				return 0;
			}

			int get_scale(lua_State* L)
			{
				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

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

				return 0;
			}

			int get_size(lua_State* L)
			{
				auto obj = scripting::get<engine::game_object>(L, 1);

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

				return 0;
			}

			int get_anchor(lua_State* L)
			{
				auto obj = scripting::get<engine::game_object>(L, 1);

				if (!obj)
					return 0;

				auto anchor = obj->get_anchor();

				return vector::create(L, anchor.x, anchor.y, anchor.z);
			}
        }
        
        namespace sprite
        {
            int create(lua_State* L)
            {
                CHECK_TOP(L, 1);
                
                if (!lua_isstring(L, 1))
                    return 0;
                
                auto texture = lua_tostring(L, 1);
                auto sprite = engine::sprite::create<engine::sprite>(texture);
                
                if (!sprite)
                    return 0;
                
                push_ref(L, sprite);
                
                return 1;
            }
            
            int set_color(lua_State* L)
            {
                CHECK_TOP(L, 1);

                auto obj = scripting::get<engine::sprite>(L, 1);
                
                if (!obj)
                    return 0;
                
                auto r = lua_tonumber(L, 2);
                auto g = lua_tonumber(L, 3);
                auto b = lua_tonumber(L, 4);
                
                obj->set_color(math::vector3d(r, g, b));
                
                return 0;
            }
        }
        
        namespace scene
        {
            int create(lua_State* L)
            {
                return scripting::create_ref<engine::scene>(L);
            }
        }
    }
}
