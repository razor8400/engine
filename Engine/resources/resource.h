#pragma once

#include "common.h"

namespace engine
{
    class resource
    {
    public:
        virtual bool load(const unsigned char* data) = 0;
        virtual ~resource() {};
    };
}
