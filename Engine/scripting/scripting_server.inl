#include "scripting_server.h"
#include "core/game_object.h"
#include "scripting.h"

namespace engine
{
    template<class T>
    void scripting_server::register_object(const luaL_Reg* methods)
    {
        auto type_name = T::type_name();
        
        luaL_newmetatable(m_state, type_name);
        luaL_setfuncs(m_state, methods, NULL);
        
        lua_pushvalue(m_state, -1);
        lua_setfield(m_state, -1, "__index");
        
        lua_setglobal(m_state, type_name);
    }
    
    template<class T>
    void scripting_server::push_to_table(const std::string& table, const std::string& field, T* data)
    {
        lua_getglobal(m_state, table.c_str());
        
        T** obj = (T**)lua_newuserdata(m_state, sizeof(T*));
        
        *obj = data;
        
        luaL_getmetatable(m_state, T::type_name());
        lua_setmetatable(m_state, -2);
        
        lua_setfield(m_state, -2, field.c_str());
    }
}
