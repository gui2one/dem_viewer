#ifndef WINDOW_H
#define WINDOW_H

#include <pch.h>
#include <core.h>
#include "Core/Camera.h"
#include "Core/CameraControls.h"
#include "Core/Timer.h"

#include "UI/UI.h"

#include "Events/Event.h"
#include "Core/OpenGLFrameBuffer.h"

#include "Core/DemTile.h"

class Window
{

public:
    CameraControls m_controls;

    UI m_ui;

public:
    Window();

    void refresh(Timer &timer);
    bool shouldClose();

    bool onKeyPressEvent(Event &e);
    bool onEvent(Event &e);
    void setEventCallback(std::function<void(Event &)> callback) { m_data.EventCallback = callback; }

    GLFWwindow *getNativeWindow() const { return m_window; }

private:
    GLFWwindow *m_window;

    std::function<void(Event &)> m_callback;
    Ref<OpenGLFrameBuffer> m_frameBuffer;

    struct WindowData
    {

        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        std::function<void(Event &)> EventCallback;
    };

    WindowData m_data;

    // friend class UI;
};

#endif /* WINDOW_H */