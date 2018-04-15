#pragma once

#include "engine.h"

class my_app_delegate : public engine::app_delegate
{
public:
	void application_launched(engine::application* application);
    void application_terminated(engine::application* application);
};
