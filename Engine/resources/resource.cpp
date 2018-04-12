#include "common.h"
#include "resource.h"

#include "utils/image_utils.h"
#include "utils/file_utils.h"

#include "texture2d.h"

namespace engine
{
    void resource_loader_task::on_loading_done(const resource_ptr& resource)
    {
        if (m_delegate)
            m_delegate->on_loading_done(this, resource);
    }
    
    void resource_loader_task::on_loading_failed(const char* error)
    {
        if (m_delegate)
            m_delegate->on_loading_failed(this, error);
    }
    
    void texture_loader_task::load_resource()
    {
        auto data = image_utils::image_data();
        
        if (image_utils::load_image_from_file(m_path, &data))
        {
            auto texture = std::make_shared<texture2d>(data.width, data.height, data.format);
            texture->load(data.buffer);
            
            on_loading_done(texture);
        }
        
        on_loading_failed(data.error.c_str());
    }
}
