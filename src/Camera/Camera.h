#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
    glm::vec3 m_Eye;
    glm::vec3 m_Center = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 m_Up = glm::vec3(0.0f,1.0f,0.0f);
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 20.0f)) : m_Eye(pos) {}

    void moveCamera(float x, float y, float z);

    inline glm::mat4 GetViewMatrix(bool isOrtho = false) const
    {
        if (isOrtho)
            return glm::translate(glm::mat4(1.0f), m_Eye);
        else
            return glm::lookAt(m_Eye, m_Center, m_Up);
    }
};
