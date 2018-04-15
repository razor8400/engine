#include "common.h"
#include "scripting.h"
#include "scripting_server.h"

namespace engine
{
    scripting_server& scripting_server::instance()
    {
        static scripting_server server;
        return server;
    }
    
    void scripting_server::create_state()
    {
        m_state = luaL_newstate();
        luaL_openlibs(m_state);
    }
    
    scripting_server::scripting_server()
    {
        
    }
    
    scripting_server::~scripting_server()
    {
        if (m_state)
            lua_close(m_state);
    }
    
    bool scripting_server::load_script(const char* buffer, size_t size, const std::string& name) const
    {        
        if (luaL_loadbuffer(m_state, buffer, size, name.c_str()) || lua_pcall(m_state, 0, 0, 0))
        {
            log("[scripting_server] load error: %s", lua_tostring(m_state, -1));
            return false;
        }
        
        return true;
    }
    
    void scripting_server::call_method(const std::string& table, const std::string& method)
    {
        lua_getglobal(m_state, table.c_str());
        lua_getfield(m_state, -1, method.c_str());
        lua_pushvalue(m_state, -2);
        
        if (lua_pcall(m_state, 1, 0, 0))
            log("[scripting_server] call_method error: %s(%s)", lua_tostring(m_state, -1), method.c_str());
    }
    
    void scripting_server::create_table(const std::string& table)
    {
        luaL_newmetatable(m_state, table.c_str());
        lua_setglobal(m_state, table.c_str());
    }
}
