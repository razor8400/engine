#include "common.h"
#include "utils/file_utils.h"
#include "scripting/scripting_server.h"
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

    }
    
    bool script::load(const unsigned char* data, size_t size)
    {
        std::string buffer = std::string(data, data + size);
        auto& server = scripting_server::instance();
        
        server.create_table(m_name.c_str());
        
        return server.load_script(buffer.c_str(), buffer.length(), m_name.c_str());
    }
    
    void script::run(game_object* obj)
    {
        scripting_server::instance().push_to_table<game_object>(m_name, "obj", obj);
        call_function(scripting::start);
    }
    
    void script::call_function(const std::string& function)
    {
        scripting_server::instance().call_method(m_name, function);
    }
}
