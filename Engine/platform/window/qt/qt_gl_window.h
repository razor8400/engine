#pragma once

#include <QtGui/QWindow>

class QOpenGLContext;
class QOpenGLPaintDevice;

class qt_gl_window : public QWindow
{
public:
    explicit qt_gl_window(QWindow* parent = nullptr);
    ~qt_gl_window();
    
    void render();
    bool create_context();
protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
private:
    QOpenGLContext* m_context = nullptr;
    QOpenGLPaintDevice* m_device = nullptr;
};
