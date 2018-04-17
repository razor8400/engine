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
