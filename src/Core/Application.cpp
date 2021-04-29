#include "Application.h"

Application *Application::s_instance = nullptr;
Application *Application::getInstance()
{

    if (s_instance == nullptr)
    {

        s_instance = new Application();
    }

    return s_instance;
}

Application::Application()
{

    // ResourceLibrary::getInstance().addItem(MakeRef<TextureItem>());

    m_window = std::make_unique<Window>();
    m_window->setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));
    m_window->m_ui.m_controls.setEventCallback(BIND_EVENT_FUNCTION(Application::onEvent));
}

void Application::run()
{
    while (!m_window->shouldClose())
    {
        // std::cout << "Running ... \n";

        m_timer.update();

        m_window->refresh(m_timer);
    }

    // m_window->m_ui.close();

    glfwTerminate();
}

void Application::onEvent(Event &e)
{

    // m_window->m_ui.onEvent(e);
    // m_window->m_controls.onEvent(e);
    m_window->onEvent(e);
    m_window->m_ui.m_controls.onEvent(e);

    // printf("[Application Event] %s\n", e.GetName());
}
