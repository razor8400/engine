#pragma once

#include "game_object.h"

namespace engine
{
	class scene : public game_object
	{
	public:
		virtual void on_mouse_down(const vector2d& location) {};
		virtual void on_mouse_move(const vector2d& location) {};
		virtual void on_mouse_up(const vector2d& location) {};
	};
}