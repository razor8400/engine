#pragma once

namespace engine
{
    class resource
    {
    public:
        virtual void load(const unsigned char* data) = 0;
        virtual ~resource() {};
    };
}
