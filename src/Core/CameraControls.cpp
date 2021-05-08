#include "CameraControls.h"

CameraControls::CameraControls()
    : m_window(nullptr),
      m_camera(nullptr),
      m_uvPos(glm::vec2(PI / 2.0f, PI * 0.22f)),
      m_radius(1.2f),
      m_cursorDelta(glm::vec2(0.f)),
      m_cursorOldPos(glm::vec2(0.f))
{
}

CameraControls::CameraControls(GLFWwindow *window, Ref<Camera> &camera)
    : m_window(window),
      m_camera(camera),
      m_uvPos(glm::vec2(PI / 2.0f, PI / 2.6f)),
      m_radius(1.2f),
      m_cursorDelta(glm::vec2(0.f)),
      m_cursorOldPos(glm::vec2(0.f))
{
}

void CameraControls::init(GLFWwindow *window, Ref<Camera> &camera)
{
    m_window = window;
    m_camera = camera;
}

void CameraControls::update(float delta_time)
{
    if (activated)
    {

        // if (Input::isKeyPressed(m_window, GLFW_KEY_LEFT_ALT) && Input::isMouseButtonClicked(m_window, 0))
        if (Input::isMouseButtonClicked(m_window, 0))
        {

            m_cursorDelta = Input::getMousePos(m_window) - m_cursorOldPos;
            m_uvPos += glm::vec2(m_cursorDelta.x * delta_time, m_cursorDelta.y * -delta_time);

            float radians_limit = PI * 0.05;
            // printf("uv pos Y : %.3f\n", m_uvPos.y);
            if (m_uvPos.y > PI - radians_limit)
                m_uvPos.y = PI - radians_limit;
            else if (m_uvPos.y < radians_limit)
                m_uvPos.y = radians_limit;
        }

        m_cursorOldPos = Input::getMousePos(m_window);
    }
    m_camera->position = fromPolar(m_uvPos);
}

glm::vec3 CameraControls::fromPolar(glm::vec2 uv_pos)
{
    glm::vec3 result;

    result.x = m_radius * sin(uv_pos.y) * cos(uv_pos.x);
    result.y = m_radius * cos(uv_pos.y);
    result.z = m_radius * sin(uv_pos.y) * sin(uv_pos.x);

    return result;
}

bool CameraControls::onEvent(Event &e)
{
    Dispatcher dispatcher(e);
    dispatcher.dispatch<MouseScrollEvent>(BIND_EVENT_FUNCTION(CameraControls::onMouseScrollEvent));

    return false;
}

bool CameraControls::onMouseScrollEvent(Event &e)
{
    if (activated)
    {
        MouseScrollEvent &event = static_cast<MouseScrollEvent &>(e);
        // std::cout << event.m_yoffset << "\n";

        m_radius *= event.m_yoffset > 0.f ? 0.9f : 1.1f;
        return true;
    }

    return false;
}