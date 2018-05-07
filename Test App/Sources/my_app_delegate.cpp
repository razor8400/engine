#include "engine.h"
#include "my_app_delegate.h"

void my_app_delegate::application_launched(engine::application* application)
{
	application->set_win_size(1024, 768);
	application->set_display_name("Test Application");
 
    if (application->create_context_window())
    {
        engine::director& director = engine::director::instance();
        
        director.set_projection_mode(engine::ortographic);
		director.set_near_plane(-1000.0f);
        director.set_far_plane(1000.0f);
        
        director.start();
        
        run_match3_scene();
        
        application->run();
    }
}

void my_app_delegate::application_terminated(engine::application* application)
{
    application->shutdown();
}

void my_app_delegate::application_enter_background(engine::application* application)
{
    engine::resources_manager::instance().clear_cache();
}

void my_app_delegate::application_enter_foreground(engine::application* application)
{
    engine::logger() << "[my_app_delegate] restart current scene";
    run_match3_scene();
}

void my_app_delegate::run_match3_scene()
{
    engine::director& director = engine::director::instance();
    
    auto script = engine::scriptable_component::create("scripts/match3scene.lua");
    auto scene = engine::game_object::create<engine::scene>();
    
    auto label = engine::game_object::create<engine::label>("fonts/arial.ttf", 48);
    label->set_caption("hui2d");
    
    auto label2 = engine::game_object::create<engine::label>("fonts/arial.ttf", 48);
    label2->set_caption("zalupka");
        
    scene->add_child(label);
   // scene->add_child(label2);
    //scene->add_component(script);
    
    director.run_scene(scene);
}

