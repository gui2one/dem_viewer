#ifndef APPLICATION_H
#define APPLICATION_H

#include <core.h>
#include <pch.h>

#include "Window.h"

#include "Core/Camera.h"
#include "Core/Timer.h"

#include "Events/Event.h"
#include "Events/KeyboardEvent.h"

class Application
{

public:
    Timer m_timer;
    static Application *s_instance;

protected:
    Application();

public:
    Application(const Application &other) = delete;
    Application(Application &other) = delete;
    void operator=(const Application &other) = delete;

    void run();
    void onEvent(Event &e);
    Window &getWindow() { return *m_window; }
    GLFWwindow *getGLFWWindow() { return m_window->getNativeWindow(); }

    static Application *getInstance();

private:
    std::unique_ptr<Window> m_window;
};

#endif /* APPLICATION_H */