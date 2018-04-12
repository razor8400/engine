#pragma once

namespace engine
{
    class resource
    {
    public:
        virtual void load(const unsigned char* data) = 0;
        virtual ~resource() {};
    };
    
    typedef std::function<void(const resource_ptr&)> resource_loader_callback;
    typedef std::function<void(const char*)> resource_error_callback;
    
    class resource_loader_task;
    
    class resource_loader_delegate
    {
    public:
        virtual void on_loading_done(resource_loader_task* task, const resource_ptr& resource) = 0;
        virtual void on_loading_failed(resource_loader_task* task, const char* error) = 0;
    };
    
    class resource_loader_task
    {
    public:
        virtual ~resource_loader_task() {};
        virtual void load_resource() = 0;
        
        friend class resources_manager;
    protected:
        void on_loading_done(const resource_ptr& resource);
        void on_loading_failed(const char* error);
    protected:
        std::string m_path;
        
        resource_loader_callback m_complete_callback;
        resource_error_callback m_error_callback;
        
        resource_loader_delegate* m_delegate = nullptr;
    };
    
    class texture_loader_task : public resource_loader_task
    {
    public:
        void load_resource() override;
    };
}
