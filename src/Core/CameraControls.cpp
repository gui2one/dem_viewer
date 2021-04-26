#include "CameraControls.h"

CameraControls::CameraControls()
    : m_window(nullptr),
      m_camera(nullptr),
      m_uvPos(glm::vec2(PI * 0.9f, PI / 2.2f)),
      m_radius(5.0f),
      m_cursorDelta(glm::vec2(0.f)),
      m_cursorOldPos(glm::vec2(0.f))
{
}

CameraControls::CameraControls(GLFWwindow *window, Ref<Camera> camera)
    : m_window(window),
      m_camera(camera),
      m_uvPos(glm::vec2(PI * 0.9f, PI / 2.2f)),
      m_radius(5.0f),
      m_cursorDelta(glm::vec2(0.f)),
      m_cursorOldPos(glm::vec2(0.f))
{
}

void CameraControls::init(GLFWwindow *window, Ref<Camera> camera)
{
    m_window = window;
    m_camera = camera;
}

void CameraControls::update(float delta_time)
{
    if (activated)
    {

        if (Input::isKeyPressed(m_window, GLFW_KEY_LEFT_ALT) && Input::isMouseButtonClicked(m_window, 0))
        {

            m_cursorDelta = Input::getMousePos(m_window) - m_cursorOldPos;
            std::cout << m_cursorDelta.x << "\n";

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
// bool CameraControls::onKeyPressEvent(KeyPressEvent &e)
// {

//     if (activated)
//     {

//         switch (e.m_Keycode)
//         {
//         case GLFW_KEY_W:
//             m_camera->position.x -= 0.1f;
//             break;
//         case GLFW_KEY_A:
//             m_camera->position.z += 0.1f;
//             break;
//         case GLFW_KEY_S:
//             m_camera->position.x += 0.1f;
//             break;
//         case GLFW_KEY_D:
//             m_camera->position.z -= 0.1f;
//             break;

//         default:
//             break;
//         }
//     }

//     return false;
// }

// bool CameraControls::onMouseScrollEvent(MouseScrollEvent &e)
// {
//     if (activated)
//     {

//         m_radius *= 1.0f + (float)e.m_yoffset * -0.2f;
//         return true;
//     }
//     return true;
// }
// bool CameraControls::onEvent(Event &e)
// {
//     if (activated)
//     {
//         // printf("CameraControls onEvent ...\n");
//         Dispatcher dispatcher(e);
//         dispatcher.dispatch<KeyPressEvent>(BIND_EVENT_FUNCTION(CameraControls::onKeyPressEvent));
//         dispatcher.dispatch<MouseScrollEvent>(BIND_EVENT_FUNCTION(CameraControls::onMouseScrollEvent));
//     }
//     return false;
// }
