#include "resources_manager.h"
#include "utils/file_utils.h"
#include "texture2d.h"
#include "resource.h"

namespace engine
{
    template<class T>
    const resource_ptr& resources_manager::load_resource(const std::string& file_name) const
    {
        auto path = file_utils::get_path_to_resource(file_name);
        auto it = m_resources.find(path);
        
        if (it != m_resources.end())
            return it->second;
        
        unsigned char* buffer;
        
        if (file_utils::read_file(path, &buffer))
        {
            auto resource = std::make_shared<T>();
            auto resource_loaded = resource->load(buffer);

            delete buffer;
            
            if (resource_loaded)
            {
                m_resources[path] = resource;
                return m_resources[path];
            }
        }
        
        static resource_ptr empty;
        
        return empty;
    }
}
