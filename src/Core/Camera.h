#ifndef CAMERA_H
#define CAMERA_H
#include <core.h>
#include <pch.h>
#include "Core/Entity3d.h"

class Camera : public Entity3d
{
public:
	float m_fov_angle = 45.0f;
	float m_screen_ratio = 1.0f;
	float m_near = 0.01f;
	float m_far = 100.0f;

public:
	Camera();
	Camera(float _fov_angle, float ratio);
	void setProjection(float angle, float screen_ratio, float near, float far);
	void setFovAngle(float angle);
	void setScreenRatio(float ratio);

	glm::vec3 target_position;
	glm::vec3 up_vector;

	glm::mat4 projection;

private:
};

#endif /* CAMERA_H */