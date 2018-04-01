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
	director.set_field_of_view(45.0f);
	
	director.set_near_plane(0.1f);
	director.set_far_plane(100.0f);
	director.set_camera_position(math::vector3d(4, 3, 3));

    auto scene = std::make_shared<engine::scene>();
	auto obj = std::make_shared<engine::game_object>();

	obj->set_size(math::vector3d(0.5f, 0.5f, 0));
	obj->set_position(math::vector3d(200, 200, 1));
	obj->set_tag(1);

	auto m1 = math::mat4::translate(10, 10, 1.0f);
	auto m2 = math::mat4::translate(20, 30, 1.0f);

	auto m3 = m1 * m2;

	scene->add_child(obj.get());
    
	director.start();
    director.run_scene(scene);
    
	application->run();
}
