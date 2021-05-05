#include "Camera.h"

Camera::Camera()
{
	m_name = "User Camera";
}

Camera::Camera(float fov_angle, float ratio)
{
	m_name = "User Camera";
	m_fov_angle = fov_angle;
	m_screen_ratio = ratio;
	m_near = 0.01f;
	m_far = 100.0f;
	position = glm::vec3(1.0f, 1.0f, -1.0f);
	target_position = glm::vec3(0.0f, 0.0f, 0.0f);
	up_vector = glm::vec3(0.0f, 0.0f, 1.0f);
	setProjection(m_fov_angle, m_screen_ratio, m_near, m_far);
}

void Camera::setProjection(float angle, float screen_ratio, float near = 0.01f, float far = 100.0f)
{
	projection = glm::mat4(1.0f) * glm::perspective(angle, screen_ratio, near, far);
}

void Camera::setFovAngle(float angle)
{
	projection = glm::mat4(1.0f) * glm::perspective(angle, m_screen_ratio, m_near, m_far);
}

void Camera::setScreenRatio(float ratio)
{
	projection = glm::mat4(1.0f) * glm::perspective(m_fov_angle, ratio, m_near, m_far);
}
