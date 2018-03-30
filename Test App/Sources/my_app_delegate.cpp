#include "my_app_delegate.h"

#include "math/vector3d.h"

using namespace engine;

void my_app_delegate::application_launched(engine::application* application)
{
	engine::director& director = engine::director::instance();
	
	application->set_win_size(1024, 768);
	application->set_display_name("Test Application");

	director.set_frame_rate(60);
    
    auto scene = std::make_shared<engine::scene>();
    
	director.start();
    director.run_scene(scene);
    
	application->run();
}
