#ifndef CAMERA_CONTROLS_H
#define CAMERA_CONTROLS_H

#include <core.h>
#include "Core/Camera.h"
#include "Core/Input.h"
#include "Events/Event.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

class CameraControls
{

public:
    glm::vec2 m_uvPos;
    float m_radius;
    GLFWwindow *m_window;

    bool activated = false;

public:
    CameraControls();
    CameraControls(GLFWwindow *window, Ref<Camera> &camera);

    void init(GLFWwindow *window, Ref<Camera> &camera);
    void setCamera(Ref<Camera> &camera) { m_camera = camera; }
    glm::vec3 fromPolar(glm::vec2 uv_pos);
    void update(float detla_time);

    void setEventCallback(std::function<void(Event &)> callback) { m_callback = callback; }
    bool onMouseScrollEvent(Event &e);
    bool onEvent(Event &e);

private:
    Ref<Camera> m_camera;

    glm::vec2 m_cursorDelta;

    glm::vec2 m_cursorOldPos;

    std::function<void(Event &)> m_callback;
};

#endif /* CAMERA_CONTROLS_H */