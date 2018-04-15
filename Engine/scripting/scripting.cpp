#include "common.h"
#include "scripting.h"
#include "scripting_server.h"

#include "core/game_object.h"
#include "core/scene.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        static int create(lua_State* L)
        {
            T** obj = (T**)lua_newuserdata(L, sizeof(T*));
            
            *obj = new T();
            
            luaL_getmetatable(L, T::type_name());
            lua_setmetatable(L, -2);
            
            return 1;
        }
        
        template<class T>
        static T* get(lua_State* L, int n)
        {
            return *(T**)luaL_checkudata(L, n, T::type_name());
        }
        
        template<class T>
        static int destroy(lua_State* L)
        {
            auto obj = get<T>(L, 1);
            delete obj;
            
            return 0;
        }
        
        namespace game_object
        {
            static int create(lua_State* L)
            {
                return scripting::create<engine::game_object>(L);
            }
            
            static int destroy(lua_State* L)
            {
                return scripting::destroy<engine::game_object>(L);
            }
            
            static const luaL_Reg functions[] =
            {
                { "create", create },
                { "__gc", destroy },
                { NULL, NULL }
            };
        }
        
        void create_state()
        {
            auto& server = scripting_server::instance();
            
            server.create_state();
            server.register_object<engine::game_object>(scripting::game_object::functions);
        }
    }
}
