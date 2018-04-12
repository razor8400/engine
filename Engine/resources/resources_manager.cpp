#include "common.h"

#include "resources_manager.h"
#include "utils/file_utils.h"

namespace engine
{
    const int resources_manager::default_loading_tasks = 10;
    
    resources_manager& resources_manager::instance()
    {
        static resources_manager manager;
        
        return manager;
    }
    
    resources_manager::resources_manager()
    {
        
    }
    
    void resources_manager::update()
    {
        for (int i = 0; i < m_max_loading_tasks; ++i)
        {
            if (m_loading_queue.empty())
                break;
            
            auto front = m_loading_queue.front();
            front->load_resource();
            m_loading_queue.pop();
        }
    }
    
    void resources_manager::load_texture(const std::string& file_name, const resource_loader_callback& complete_callback, const resource_error_callback& error_callback)
    {
        auto path = file_utils::get_path_to_resource(file_name);
        
        if (!find_resource(path, complete_callback))
        {
            auto task = new texture_loader_task();
            
            task->m_complete_callback = complete_callback;
            task->m_error_callback = error_callback;
            task->m_delegate = this;
            task->m_path = path;
            
            m_loading_queue.push(task);
        }
    }
    
    bool resources_manager::find_resource(const std::string& path, const resource_loader_callback& complete_callback) const
    {
        auto it = m_resources.find(path);
        
        if (it != m_resources.end() && complete_callback)
        {
            complete_callback(it->second);
            return true;
        }
        
        return false;
    }
    
    void resources_manager::clear_cache()
    {
        m_resources.clear();
    }
    
    void resources_manager::on_loading_done(resource_loader_task* task, const resource_ptr& resource)
    {
        m_resources[task->m_path] = resource;
        
        if (task->m_complete_callback)
            task->m_complete_callback(resource);
        
        delete task;
    }
    
    void resources_manager::on_loading_failed(resource_loader_task* task, const char* error)
    {
        if (task->m_error_callback)
            task->m_error_callback(error);
        
        delete task;
    }
}
