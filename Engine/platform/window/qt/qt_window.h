#pragma once

#include <QtGui/QWindow>
#include "platform/window/window.h"

class QOpenGLContext;
class QOpenGLPaintDevice;

namespace engine
{
    class qt_window : public window, public QWindow
    {
    public:
        qt_window();
        ~qt_window();
        
        bool create(const char* display_name, int width, int height) override;
        void process() override;
        void terminate() override;
        const math::vector2d& get_win_size() const override { return m_size; }
        math::vector2d get_mouse_location() const override;
    private:
        void render();
        bool create_context();
        
        bool event(QEvent* event) override;
        void exposeEvent(QExposeEvent* event) override;
    private:
        QOpenGLContext* m_context = nullptr;
        QOpenGLPaintDevice* m_device = nullptr;
        math::vector2d m_size;
    };
}


