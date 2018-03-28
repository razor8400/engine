#pragma once

#include "common.h"
#include "game_object.h"

namespace engine
{
    class layer : public game_object
    {
    public:
        virtual bool init() override;
    };
}
