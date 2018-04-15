#pragma once

class lua_State;

namespace engine
{
    class scripting_server
    {
    public:
        static scripting_server& instance();
        
        void create_state();
        
        bool load_script(const char* buffer, size_t, const std::string& name) const;
        void call_method(const std::string& table, const std::string& method);
        void create_table(const std::string& table);
        
        template<class T>
        void push_to_table(const std::string& table, const std::string& field, T* data);
        
        template<class T>
        void register_object(const luaL_Reg* methods);
    private:
        scripting_server();
        ~scripting_server();
    private:
        lua_State* m_state = nullptr;
    };
}

#include "scripting_server.inl"
