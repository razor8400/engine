#include "my_app_delegate.h"

#include "math/vector3d.h"

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
	auto obj = game_object::create<engine::game_object>();
	auto obj2 = game_object::create<engine::game_object>();

	obj->set_size(math::vector3d(1.1f, 1.1f, 0));
	obj->set_position(math::vector3d(0, 0, 1));	

	obj2->set_position(math::vector3d(1.0f, 1.0f, 1.0f));
	obj2->set_anchor(math::vector3d(1, 1, 0));
	obj2->set_rotation(math::vector3d(0, 0, -45));
	obj2->set_size(math::vector3d(0.5f, 0.5f, 0));
	
	obj->add_child(obj2);
	scene->add_child(obj);
    
	director.start();
    director.run_scene(scene);
    
	application->run();
}
