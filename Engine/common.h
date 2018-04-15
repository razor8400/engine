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

#include "utils/safe_vector.h"
#include "config.h"

#include "scripting/scripting.h"

namespace engine
{
    class renderer;
    
	class scene;
	typedef std::shared_ptr<scene> scene_ptr;

	class game_object;
	typedef std::shared_ptr<game_object> game_object_ptr;
    
    class resource;
    typedef std::shared_ptr<resource> resource_ptr;
    
    class texture2d;
    typedef std::shared_ptr<texture2d> texture2d_ptr;
    
    class action;
    typedef std::shared_ptr<action> action_ptr;

    class script;
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

