#pragma once

#include "resource.h"

namespace engine
{
    class texture2d : public resource
	{
    public:
        virtual ~texture2d();
        
        bool load(const unsigned char* data) override;
    private:
		int m_width = 0;
		int m_height = 0;
        int m_texture_id = -1;
	};
}
