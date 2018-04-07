#include "common.h"
#include "resource.h"
#include "utils/file_utils.h"

namespace engine
{
    void resource_loader_task::on_loading_done()
    {
        if (m_delegate)
            m_delegate->on_loading_done(this);
    }
    
    void resource_loader_task::on_loading_failed(const char* error)
    {
        if (m_delegate)
            m_delegate->on_loading_failed(this, error);
    }
    
    void file_loader_task::load_resource()
    {
        bool resource_loaded = m_resource != nullptr;
        
        if (m_resource)
        {
            unsigned char* buffer;
            
            if (file_utils::read_file(m_path, &buffer))
            {
                resource_loaded = m_resource->load(buffer);
                
                delete[] buffer;
            }
        }
        
        if (resource_loaded)
        {
            on_loading_done();
        }
        else
        {
            on_loading_failed(loading_error::file_not_found_error);
        }
    }
}
