#include "Input.h"

#include <GLFW/glfw3.h>

bool Input::isKeyPressed(GLFWwindow *window, const int keycode)
{

    auto *win = static_cast<GLFWwindow *>(window);
    auto state = glfwGetKey(win, static_cast<int32_t>(keycode));

    if (state == GLFW_PRESS)
    {
        // printf("keycode %d PRESSED %d -- %d !!\n", keycode , state, GLFW_PRESS);
        return true;
    }
    return false;
}

bool Input::isMouseButtonClicked(GLFWwindow *window, int button)
{

    auto state = glfwGetMouseButton(window, button);
    switch (state)
    {
    case GLFW_PRESS:
        return true;
        break;

    default:
        break;
    }

    return false;
}

glm::vec2 Input::getMousePos(GLFWwindow *window)
{

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    return glm::vec2((float)x, (float)y);
}
