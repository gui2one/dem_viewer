#ifndef INPUT_H
#define INPUT_H

#include <pch.h>
class Input
{

public:
    static int scrollOffset;

public:
    static bool isKeyPressed(GLFWwindow *window, const int keycode);
    static bool isMouseButtonClicked(GLFWwindow *window, int button);
    static glm::vec2 getMousePos(GLFWwindow *window);
    static glm::vec2 getMouseScroll(GLFWwindow *window);

    static void setScrollOffset(int amount) { scrollOffset = amount; }

private:
};

#endif /* INPUT_H */