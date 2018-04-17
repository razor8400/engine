#include "common.h"

#include "utils/file_utils.h"
#include "script.h"

namespace engine
{
    std::shared_ptr<script> script::load_from_file(const std::string& file_name)
    {
        unsigned char* buffer;
        size_t size;
        
        if (file_utils::read_file(file_name, &buffer, &size))
        {
            auto name = file_utils::get_file_name(file_name);
            auto lua = std::make_shared<script>(name);
            if (lua->load(buffer, size))
                return lua;
        }
        
        log("[script] can't load script file:%s", file_name.c_str());
        
        return std::shared_ptr<script>();
    }
    
    script::script(const std::string& name) : m_name(name)
    {

    }
    
    script::~script()
    {
        stop();
    }
    
    void script::run()
    {
        m_state = scripting::create_state();
        
        if (m_state)
        {
            scripting::create_class(m_state, m_name.c_str());
            scripting::register_objects(m_state);
            
            scripting::load_script(m_state, m_buffer.data(), m_buffer.size(), m_name);
        }
    }
    
    void script::stop()
    {
        if (m_state)
        {
            scripting::close_state(m_state);
            m_state = nullptr;
        }
    }
    
    bool script::load(const unsigned char* data, size_t size)
    {
        if (m_state)
            return false;
        
        m_buffer.clear();
        m_buffer.reserve(size);
        m_buffer.insert(m_buffer.end(), data, data + size);
        
        return m_buffer.size() > 0;
    }
    
    void script::call_function(const std::string& function)
    {
        scripting::call_method(m_state, m_name, function);
    }
}
