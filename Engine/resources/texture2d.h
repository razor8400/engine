#pragma once

#include "resource.h"

namespace engine
{
    class texture2d : public resource
	{
    public:
        virtual ~texture2d();
        
        struct data
        {
            int width;
            int height;
            int format;
        };
        
        bool load(const unsigned char* data) override;
    private:
        data m_data;
        int m_texture_id = -1;
	};
}
