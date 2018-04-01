#pragma once

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <map>

#include "math/vector2d.h"
#include "math/vector3d.h"
#include "math/mat4.h"

namespace engine
{
	class scene;
	typedef std::shared_ptr<scene> scene_ptr;

	class game_object;
	typedef std::shared_ptr<game_object> game_object_ptr;

	class renderer;

	enum projection_mode
	{
		ortographic, perspective
	};
}

