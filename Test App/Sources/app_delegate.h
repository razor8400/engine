#pragma once

#include "core/application.h"

class my_app_delegate : public engine::app_delegate
{
public:
	void application_launched(engine::application* application);
};