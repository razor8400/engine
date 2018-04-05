#pragma once

namespace engine
{
    class application;
    
    class app_delegate
    {
    public:
        virtual void application_launched(application* application) = 0;
    };
}


