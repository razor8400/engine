#pragma once
#include "resources_manager.h"
#include "utils/file_utils.h"

namespace engine
{
    template<class T>
    void resources_manager::load_resource_from_file(const std::string& file_name, const resource_loader_callback& complete_callback, const resource_error_callback& error_callback)
    {
        auto path = file_utils::get_path_to_resource(file_name);
        auto it = m_resources.find(path);
        
        if (it != m_resources.end() && complete_callback)
        {
            complete_callback(it->second);
        }
        else
        {
            auto task = new file_loader_task();
            
            task->m_path = path;
            task->m_resource = std::make_shared<T>();
            task->m_complete_callback = complete_callback;
            task->m_error_callback = error_callback;
            task->m_delegate = this;
            
            m_loading_queue.push(task);
        }
    }
}
