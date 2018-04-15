#pragma once

#include "resource.h"
#include "scripting/scripting.h"

class lua_State;

namespace engine
{
    class script : public resource
    {
    public:
        static std::shared_ptr<script> load_from_file(const std::string& file_name);
        
        script(const std::string& name);
        ~script();
        
        void run();
        void stop();
        bool load(const unsigned char* data, size_t size) override;
        
        void call_function(const std::string& function);
        
        template<class T>
        void push_user_data(const std::string& field, T* data);
    private:
        std::string m_name;
        std::vector<char> m_buffer;
        
        lua_State* m_state = nullptr;
    };
    
    template<class T>
    void script::push_user_data(const std::string& field, T* data)
    {
        scripting::push_to_table(m_state, m_name, field, data);
    }
}
