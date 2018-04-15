#include "common.h"
#include "scripting.h"

#include "core/game_object.h"
#include "core/scene.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        static T* get(lua_State* L, int n)
        {
            return *(T**)(luaL_checkudata(L, n, T::type_name()));
        }
        
        template<class T>
        static int create_ref(lua_State* L)
        {
            T** obj = (T**)lua_newuserdata(L, sizeof(T*));
            
            *obj = ref::create<T>();
            (*obj)->retain();
            
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
        void register_object(lua_State* state, const luaL_Reg* methods)
        {
            auto type_name = T::type_name();
            
            luaL_newmetatable(state, type_name);
            luaL_setfuncs(state, methods, NULL);
            
            lua_pushvalue(state, -1);
            lua_setfield(state, -1, "__index");
            
            lua_setglobal(state, type_name);
        }
        
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
        
        lua_State* create_state()
        {
            auto state = luaL_newstate();
            luaL_openlibs(state);
            
            return state;
        }
        
        void register_objects(lua_State* state)
        {
            register_object<engine::game_object>(state, scripting::game_object::functions);
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
        }
        
        void create_class(lua_State* state, const std::string& class_name)
        {
            luaL_newmetatable(state, class_name.c_str());
            lua_setglobal(state, class_name.c_str());
        }
    }
}
