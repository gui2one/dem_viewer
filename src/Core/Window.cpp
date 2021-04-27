#include "Window.h"

#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

Window::Window()
{
    int width = 1280;
    int height = 720;

    if (!glfwInit())
    {
        // ORBITONS_ASSERT(false, "GLFW Error \n");
        glfwTerminate();
    }

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    m_window = glfwCreateWindow(width, height, "DEM Viewer", NULL, NULL);
    if (!m_window)
    {
        // ORBITONS_ASSERT(false, "GLFW Window Error\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // return -1;
    }

    m_ui.ImGuiInit(m_window);
    m_data.Title = "Hello";

    // set GLFW window icon
    GLFWimage icons[1];
    icons[0].pixels = stbi_load("resources/icon.png", &icons[0].width, &icons[0].height, 0, 4); //rgba channels
    glfwSetWindowIcon(m_window, 1, icons);
    stbi_image_free(icons[0].pixels);
    /////////////////////

    glfwSetWindowUserPointer(m_window, &m_data);
    glfwSwapInterval(1);

    /* set callbacks */
    glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
        std::cout << "Key callback\n";
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        switch (action)
        {
        case GLFW_PRESS:
        {
            KeyPressEvent event(key, scancode, 0);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            KeyReleaseEvent event(key, scancode);
            data.EventCallback(event);
            break;
        }
        case GLFW_REPEAT:
        {
            KeyPressEvent event(key, scancode, 1);
            data.EventCallback(event);
            break;
        }
        };
    });

    glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double x_pos, double y_pos) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        MouseMoveEvent event(x_pos, y_pos);
        data.EventCallback(event);
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xoffset, double yoffset) {
        ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        MouseScrollEvent event(xoffset, yoffset);
        data.EventCallback(event);
    });
}

void Window::refresh(Timer &timer)
{

    glClearColor(.1f, .1f, .1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_ui.ImGuiBeginFrame();

    m_ui.drawMainMenu();

    m_ui.drawTileList();

    m_ui.displayDemTile();

    m_ui.ImGuiEndFrame();
    glfwPollEvents();

    glfwSwapBuffers(m_window);
}

bool Window::onKeyPressEvent(Event &e)
{

    KeyPressEvent &event = static_cast<KeyPressEvent &>(e);
    if (event.m_Keycode == 57) /*space bar*/
    {
        printf("space bar pressed\n");
        return true;
    }
    return true;
}

bool Window::onEvent(Event &e)
{

    // m_controls.onEvent(e);

    Dispatcher dispatcher(e);
    dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(Window::onKeyPressEvent));

    return true;
}

bool Window::shouldClose()
{

    return glfwWindowShouldClose(m_window);
}
