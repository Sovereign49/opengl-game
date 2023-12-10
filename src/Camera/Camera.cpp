#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

void Camera::moveCamera(float x, float y, float z)
{
    m_Position = glm::translate(m_Position,glm::vec3(-x, -y, -z));
}
