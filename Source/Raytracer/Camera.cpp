#include "Camera.h"
#include "mathutils.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio):
m_eye(eye),
	m_fov(fov),
	m_aspectRatio(aspectRatio)
{
	LookAt(eye, target, up);
}


void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)

	m_forward = target - eye;
	// normalize forward vector
	m_forward = glm::normalize(m_forward);
		// use cross product to create vectors
		// right = up x forward 
		m_right = glm::cross(up, m_forward);
		// up = forward x right
		m_up = glm::cross(m_forward, m_right);

		CalculateViewPlane();
}

ray_t Camera::GetRay(const glm::vec2& point) const
{
	ray_t ray;
	// the ray origin is the camera eye
	ray.origin = m_eye;
		// calculate direction from point
		 //<lower left + (horizontal * point x) + (vertical * point.y) - eye>
		ray.direction =  m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye;

		return ray;
}

void Camera::CalculateViewPlane()
{
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = halfHeight * 2.0f;
	float width = height* m_aspectRatio;

	// calculate horizontal vector (right vector * width)
	m_horizontal = m_right * width;
		// calculate vertical vector (up vector * height)
		m_vertical = m_up *height;
		// calculate lower left location (origin)
		m_lowerLeft = m_eye - (m_horizontal/2.0f) - (m_vertical/2.0f) - m_forward;
}
