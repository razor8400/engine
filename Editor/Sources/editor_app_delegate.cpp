#include "engine.h"
#include "editor_app_delegate.h"

void editor_app_delegate::application_launched(engine::application* application)
{
	application->set_win_size(1024, 768);
	application->set_display_name("Editor");
 
    if (application->create_context_window())
    {
        engine::director& director = engine::director::instance();
        
        auto scene = engine::game_object::create<engine::scene>();
        
        director.set_projection_mode(engine::ortographic);
		director.set_near_plane(-1000.0f);
        director.set_far_plane(1000.0f);
        
        director.start();
        director.run_scene(scene);
        
        application->run();
    }
}

void editor_app_delegate::application_terminated(engine::application* application)
{
    application->shutdown();
}

void editor_app_delegate::application_enter_background(engine::application* application)
{
    
}

void editor_app_delegate::application_enter_foreground(engine::application* application)
{
    
}

