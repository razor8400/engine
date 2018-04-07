#include "my_app_delegate.h"

using namespace engine;

void my_app_delegate::application_launched(engine::application* application)
{
	engine::director& director = engine::director::instance();
	
	application->set_win_size(1024, 768);
	application->set_display_name("Test Application");

	director.set_frame_rate(60);

	director.set_projection_mode(engine::perspective);
	director.set_field_of_view(45);
	
	director.set_near_plane(0.1f);
	director.set_far_plane(100.0f);
	director.set_camera_position(math::vector3d(0, 0, -1));

	auto scene = game_object::create<engine::scene>();
    auto sprite = sprite::create("hui.png");
    sprite->set_scale(math::vector3d(0.5f, 0.5f, 0.5f));
    
    scene->add_child(sprite);
    
	director.start();
    director.run_scene(scene);
    
    application->run();
}
