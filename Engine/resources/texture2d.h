#pragma once

#include "resource.h"

namespace engine
{
    class texture2d : public resource
	{
    public:
        virtual ~texture2d();
        
        bool load(const unsigned char* data) override;
        void draw();
        
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }
    private:
		int m_width = 0;
		int m_height = 0;
        int m_texture_id = -1;
	};
}
