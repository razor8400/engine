#pragma once

#include "common.h"

namespace engine
{
    class resources_manager
    {
    public:
        static resources_manager& instance();
        
        template<class T>
        const resource_ptr& load_resource(const std::string& path) const;
        
        void clear_cache();
    private:
        resources_manager();
        
        mutable std::map<std::string, resource_ptr> m_resources;
    };
}
