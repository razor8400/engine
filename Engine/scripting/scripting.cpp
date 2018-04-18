#include "common.h"
#include "scripting.h"
#include "binding.h"

#include "components/component.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "2d/sprite.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        void register_class(lua_State* state, const luaL_Reg* methods)
        {
            auto type_name = T::type_name();
            
            luaL_newmetatable(state, type_name);
            
            if (methods)
                luaL_setfuncs(state, methods, NULL);
            
            lua_pushvalue(state, -1);
            lua_setfield(state, -1, "__index");
            
            auto parent = T::type_info()->get_parent();
            
            if (parent)
            {
                lua_getglobal(state, parent->get_class());
                lua_setmetatable(state, -2);
            }
            
            lua_setglobal(state, type_name);
            
            CLEAR_TOP(state);
        }
        
        lua_State* create_state()
        {
            auto state = luaL_newstate();
            luaL_openlibs(state);
            
            return state;
        }
        
        void register_objects(lua_State* state)
        {
            register_class<engine::game_object>(state, scripting::game_object::functions);
            register_class<engine::sprite>(state, scripting::sprite::functions);
            register_class<engine::scene>(state, scripting::scene::functions);
        }
        
        void close_state(lua_State* state)
        {
            lua_close(state);
        }
        
        void load_script(lua_State* state, const char* buffer, size_t size, const std::string& name)
        {
            if (luaL_loadbuffer(state, buffer, size, name.c_str()) || lua_pcall(state, 0, 0, 0))
                log("[scripting] load error: %s", lua_tostring(state, -1));
        }
        
        void call_method(lua_State* state, const std::string& class_name, const std::string& method)
        {
            lua_getglobal(state, class_name.c_str());
            lua_getfield(state, -1, method.c_str());
            lua_pushvalue(state, -2);
            
            if (lua_pcall(state, 1, 0, 0))
                log("[scripting] call_method error: %s", lua_tostring(state, -1));
            
            CLEAR_TOP(state);
        }
        
        void create_class(lua_State* state, const std::string& class_name)
        {
            luaL_newmetatable(state, class_name.c_str());
            
            lua_pushvalue(state, -1);
            lua_setfield(state, -1, "__index");
            
            lua_setglobal(state, class_name.c_str());
            
            CLEAR_TOP(state);
        }
        
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, const math::vector3d& v3)
        {
            lua_getglobal(state, table.c_str());
            
            vector::push(state, v3.x, v3.y, v3.z);
            
            lua_setfield(state, -2, field.c_str());
            
            CLEAR_TOP(state);
        }
    }
}
