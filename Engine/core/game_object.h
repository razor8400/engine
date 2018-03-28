#pragma once

#include "common.h"

namespace engine
{
	class game_object
	{
	public:
		virtual void update(float dt);
		virtual void draw();
	private:
		std::vector<game_object*> m_children;
	};
}