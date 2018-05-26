#include "engine.h"

#include "editor_app_delegate.h"
#include "editor_scene.h"
#include "editor_window.h"
#include "editor.h"

#include <QApplication>

static const int width = 1024;
static const int height = 768;

bool editor_app_delegate::application_launched(engine::application* application)
{
	application->set_win_size(width, height);
	application->set_display_name("Editor");
    
    if (application->create_context_window())
    {
        engine::director& director = engine::director::instance();
        engine::resources_manager::instance().add_resources_folder(editor::assets.toStdString());

        auto& editor = editor::instance();
        
        editor.load_elements();
        editor.new_scene();
        
        director.set_projection_mode(engine::ortographic);
		director.set_near_plane(-1000.0f);
        director.set_far_plane(1000.0f);
        
        director.start();
        
        auto window = new editor_window;
        
        window->resize(width / 2, height / 2);
        window->setWindowTitle("Tools");
        window->show();
        
        editor.m_main_window = window;
        
        application->run();
        
        return true;
    }
    
    return false;
}

void editor_app_delegate::application_terminated(engine::application* application)
{
    application->shutdown();
    QApplication::instance()->exit();
}

void editor_app_delegate::application_enter_background(engine::application* application)
{
    
}

void editor_app_delegate::application_enter_foreground(engine::application* application)
{
    
}

