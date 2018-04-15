#pragma once

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

namespace engine
{
    namespace scripting
    {
        static const char* start = "start";
        static const char* update = "update";
        static const char* stop = "stop";
        
        void create_state();
    }
}

