#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

#include <core.h>
#include "Core/Camera.h"
#include "Core/Input.h"
// #include "Events/KeyboardEvent.h"
// #include "Events/MouseEvent.h"

class CameraControls
{

public:
    glm::vec2 m_uvPos;
    float m_radius;
    GLFWwindow *m_window;

    bool activated = true;

public:
    CameraControls();
    CameraControls(GLFWwindow *window, Ref<Camera> camera);

    void init(GLFWwindow *window, Ref<Camera> camera);
    void setCamera(Ref<Camera> &camera) { m_camera = camera; }
    glm::vec3 fromPolar(glm::vec2 uv_pos);
    void update(float detla_time);

    // void setEventCallback(std::function<void(Event &)> fn) { m_EventCallback = fn; }
    // bool onKeyPressEvent(KeyPressEvent &e);
    // bool onMouseScrollEvent(MouseScrollEvent &e);
    // bool onEvent(Event &e);

private:
    Ref<Camera> m_camera;

    // std::function<void(Event &)> m_EventCallback;

    glm::vec2 m_cursorDelta;
    glm::vec2 m_cursorOldPos;
};

#endif /* CAMERA_CONTROLS_H */