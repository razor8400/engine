#pragma once

#include "resource.h"

namespace engine
{
	class font : public resource
	{
	public:
		static std::shared_ptr<font> load_from_file(const std::string& file_name);
	private:
	};
}