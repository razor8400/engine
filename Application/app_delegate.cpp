#include "app_delegate.h"
#include "core/scene.h"
#include "core/director.h"

void my_app_delegate::application_launched(engine::application* application)
{
	engine::director& director = engine::director::instance();
	
	application->set_win_size(1024, 768);
	application->set_display_name("Test Application");

	director.set_frame_rate(60);
	director.start(new engine::scene());

	application->run();
}
