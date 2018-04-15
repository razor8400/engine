#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include <functional>
#include <queue>

#include "gl/libgl.h"
#include "math/libmath.h"

#include "utils/vector.h"
#include "config.h"

namespace engine
{
    class ref;
    class renderer;
    
	class scene;
	class game_object;
    class component;

    class resource;
    class texture2d;
    class script;
    
    typedef std::shared_ptr<resource> resource_ptr;
    typedef std::shared_ptr<texture2d> texture2d_ptr;
    typedef std::shared_ptr<script> script_ptr;

	enum projection_mode
	{
		ortographic, perspective
	};
    
    static const std::string empty_string;
    
    static void log(const char* msg, ...)
    {
        static const int MAX = 1000;
        static char buffer[MAX];
        
        va_list args;
        
        va_start(args, msg);
        vsnprintf(buffer, MAX, msg, args);
        va_end(args);
        
        printf("[engine]%s\n", buffer);
    }
    
#define OBJECT_TYPE(TYPENAME)\
public:\
    static const char* type_name() { return #TYPENAME; }
}

