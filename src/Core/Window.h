#ifndef WINDOW_H
#define WINDOW_H

#include <pch.h>
#include <core.h>
#include "Core/Camera.h"
#include "Core/CameraControls.h"
#include "Core/Timer.h"

#include "UI/UI.h"

#include "Events/Event.h"
#include "Render/OpenGLFrameBuffer.h"

#include "Core/DemTile.h"

class Window
{

public:
    UI m_ui;

public:
    Window();

    void refresh(Timer &timer);
    bool shouldClose();

    bool onEvent(Event &e);
    void setEventCallback(std::function<void(Event &)> callback) { m_data.EventCallback = callback; }

    bool onKeyPressEvent(Event &e);
    bool onDropEvent(Event &e);
    bool onMouseScrollEvent(Event &e);

    GLFWwindow *getNativeWindow() const { return m_window; }

private:
    GLFWwindow *m_window;

    std::function<void(Event &)> m_callback;
    // Ref<OpenGLFrameBuffer> m_frameBuffer;

    struct WindowData
    {

        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        std::vector<std::string> DropPaths;
        std::function<void(Event &)> EventCallback;
    };

    WindowData m_data;

    // friend class UI;
};

#endif /* WINDOW_H */