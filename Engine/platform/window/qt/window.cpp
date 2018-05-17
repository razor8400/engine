#include "common.h"

#include "core/director.h"
#include "core/application.h"
#include "core/input/touch_dispatcher.h"

#include "platform/window/window.h"
#include "qt_gl_window.h"

namespace engine
{
    qt_gl_window* main_window = nullptr;
    
    window::window()
    {
        
    }
    
    bool window::create(const char* display_name, int width, int height)
    {
        QSurfaceFormat format;
        
        format.setMinorVersion(3);
        format.setMajorVersion(3);
        format.setOption(QSurfaceFormat::DeprecatedFunctions);
        format.setProfile(QSurfaceFormat::CoreProfile);

        main_window = new qt_gl_window();
        main_window->setFormat(format);
        main_window->resize(width, height);
        main_window->setTitle(display_name);
        
        if (!main_window->create_context())
            return false;
        
        main_window->show();
        
        return true;
    }
    
    void window::process()
    {

    }
    
    void window::terminate()
    {
        main_window->close();
        delete main_window;
    }
    
    math::vector2d window::get_mouse_location() const
    {
        return math::vector2d::zero;
    }
}
