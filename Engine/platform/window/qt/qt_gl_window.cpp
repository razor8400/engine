#include "common.h"
#include "qt_gl_window.h"

#include "core/director.h"
#include "core/application.h"
#include "core/input/touch_dispatcher.h"

#include "platform/window/window.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>

qt_gl_window::qt_gl_window(QWindow* parent) : QWindow(parent), m_device(new QOpenGLPaintDevice)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

qt_gl_window::~qt_gl_window()
{
    delete m_device;
    delete m_context;
}

bool qt_gl_window::create_context()
{
    m_context = new QOpenGLContext(this);
    m_context->setFormat(format());
    
    if (!m_context->create())
        return false;
    
    auto format(m_context->format());
    
    engine::logger() << "Initialized Qt OpenGL context " << format.majorVersion() << "."
                        << format.minorVersion() << " successfully.";
    
    return true;
}

void qt_gl_window::render()
{
    m_context->makeCurrent(this);
    m_device->setSize(size());

    engine::director::instance().main_loop();
    
    m_context->swapBuffers(this);
    
    requestUpdate();
}

bool qt_gl_window::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::UpdateRequest: render(); return true;
        default:
            return QWindow::event(event);
    }
}

void qt_gl_window::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);
    
    if (isExposed())
        render();
}
