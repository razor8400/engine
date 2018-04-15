#pragma once

#include "resource.h"

namespace engine
{
    class script : public resource
    {
    public:
        static std::shared_ptr<script> load_from_file(const std::string& file_name);
        
        script(const std::string& name);
        ~script();
        
        bool load(const unsigned char* data, size_t size) override;
        void run(game_object* obj);
        void call_function(const std::string& function);
    private:
        std::string m_name;
    };
}
