#include "common.h"
#include "qt_window.h"

#include "core/director.h"
#include "core/application.h"
#include "core/input/touch_dispatcher.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>

namespace engine
{
    std::unique_ptr<window> window::create()
    {
        return std::make_unique<qt_window>();
    }
    
    qt_window::qt_window() : QWindow(), m_device(new QOpenGLPaintDevice)
    {
        setSurfaceType(QSurface::OpenGLSurface);
    }
    
    qt_window::~qt_window()
    {
        delete m_device;
        
        if (m_context)
            delete m_context;
    }
    
    bool qt_window::create(const char* display_name, int width, int height)
    {
        QSurfaceFormat format;
        
        format.setMinorVersion(OPEN_GL_MINOR_VERSION);
        format.setMajorVersion(OPEN_GL_MAJOR_VERSION);
        format.setProfile(QSurfaceFormat::CoreProfile);
        
        m_context = new QOpenGLContext(this);
        m_context->setFormat(format);
        
        if (!m_context->create())
            return false;
        
        logger() << "[qt_window] initialized Qt OpenGL context " << format.majorVersion() << "."
                                                                    << format.minorVersion() << " successfully.";
        
        m_size.x = (float)width;
        m_size.y = (float)height;
        
        resize(width, height);
        
        show();
        
        return true;
    }
    
    void qt_window::process()
    {
        
    }
    
    void qt_window::terminate()
    {
        close();
    }
    
    math::vector2d qt_window::get_mouse_location() const
    {
        return math::vector2d::zero;
    }
    
    void qt_window::render()
    {
        m_context->makeCurrent(this);
        m_device->setSize(size());
        
        engine::director::instance().main_loop();
        
        m_context->swapBuffers(this);
        
        requestUpdate();
    }
    
    bool qt_window::event(QEvent *event)
    {
        switch (event->type())
        {
            case QEvent::UpdateRequest: render(); return true;
            default:
                return QWindow::event(event);
        }
    }
    
    void qt_window::exposeEvent(QExposeEvent *event)
    {
        Q_UNUSED(event);
        
        if (isExposed())
            render();
    }
}
