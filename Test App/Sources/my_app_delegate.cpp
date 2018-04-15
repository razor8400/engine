#include "my_app_delegate.h"

void my_app_delegate::application_launched(engine::application* application)
{
	application->set_win_size(1024, 768);
	application->set_display_name("Test Application");
 
    if (application->create_context_window())
    {
        engine::director& director = engine::director::instance();
        
        director.set_frame_rate(60);
        director.set_projection_mode(engine::ortographic);
        
        director.set_near_plane(0.1f);
        director.set_far_plane(100.0f);
        
        auto script = engine::scriptable_component::create("scripts/scene.lua");
        auto scene = engine::game_object::create<engine::scene>();
        
        scene->add_component(script);
        
        director.start();
        director.run_scene(scene);
        
        application->run();
    }
}

void my_app_delegate::application_terminated(engine::application* application)
{
    application->shutdown();
}
