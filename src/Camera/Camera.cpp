#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

void Camera::moveCamera(float x, float y, float z)
{
    m_Eye.x -= x;
    m_Eye.y -= y;
    m_Eye.z -= z;
}
