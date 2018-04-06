#pragma once

namespace engine
{
    namespace loading_error
    {
        static const char* file_not_found_error = "file_not_found";
        static const char* unknown_error = "unknown";
    }
    
    class resource
    {
    public:
        virtual bool load(const unsigned char* data) = 0;
        virtual ~resource() {};
    };
    
    typedef std::function<void(const resource_ptr&)> resource_loader_callback;
    typedef std::function<void(const char*)> resource_error_callback;
    
    class resource_loader_task;
    
    class resource_loader_delegate
    {
    public:
        virtual void on_loading_done(resource_loader_task* task) = 0;
        virtual void on_loading_failed(resource_loader_task* task, const char* error) = 0;
    };
    
    class resource_loader_task
    {
    public:
        virtual ~resource_loader_task() {};
        virtual void load_resource() = 0;
        
        friend class resources_manager;
    protected:
        void on_loading_done();
        void on_loading_failed(const char* error);
    protected:
        std::string m_path;
        
        resource_ptr m_resource;
        resource_loader_callback m_complete_callback;
        resource_error_callback m_error_callback;
        
        resource_loader_delegate* m_delegate = nullptr;
    };
    
    class file_loader_task : public resource_loader_task
    {
    public:
        void load_resource() override;
    };
}
