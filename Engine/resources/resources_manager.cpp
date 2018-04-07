#include "common.h"

#include "resources_manager.h"

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
    
    void resources_manager::clear_cache()
    {
        m_resources.clear();
    }
    
    void resources_manager::on_loading_done(resource_loader_task* task)
    {
        auto& resource = task->m_resource;
        
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
