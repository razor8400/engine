#pragma once

#include "resource.h"

namespace engine
{    
    typedef std::shared_ptr<resource_loader_task> resource_loader_task_ptr;
    
    class resources_manager : public resource_loader_delegate
    {
    public:
        static resources_manager& instance();

        template<class T>
        void load_resource_from_file(const std::string& file_name, const resource_loader_callback& complete_callback, const resource_error_callback& error_callback);
        
        void update();
        void clear_cache();
        void set_max_loading_tasks(int max_loading_tasks) { m_max_loading_tasks = max_loading_tasks; }
    private:
        void on_loading_done(resource_loader_task* task) override;
        void on_loading_failed(resource_loader_task* task, const char* error) override;
    private:
        static const int default_loading_tasks;
        resources_manager();
        
        std::map<std::string, resource_ptr> m_resources;
        std::queue<resource_loader_task*> m_loading_queue;
        
        int m_max_loading_tasks = default_loading_tasks;
    };
}

#include "resources_manager.inl"
