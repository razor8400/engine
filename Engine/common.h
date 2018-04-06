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

namespace engine
{
	class scene;
	typedef std::shared_ptr<scene> scene_ptr;

	class game_object;
	typedef std::shared_ptr<game_object> game_object_ptr;
    
    class resource;
    typedef std::shared_ptr<resource> resource_ptr;
    
    class texture2d;
    typedef std::shared_ptr<texture2d> texture2d_ptr;

	class renderer;

	enum projection_mode
	{
		ortographic, perspective
	};
    
    static const std::string empty_string;
    
    static void log(const char* msg)
    {
        
    }
}

