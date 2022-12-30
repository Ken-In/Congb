#include "cbpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Congb {
	
	
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
		: m_ProjectMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectMatrix * m_ViewMatrix;
		m_Up = { 0, 1, 0 };
		m_LookAt = { 0, 0, 1 };
		m_Right = glm::cross(m_Up, m_LookAt);
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectMatrix * m_ViewMatrix;
	}

}