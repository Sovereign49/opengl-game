#pragma once
#include "glm/glm.hpp"

class Camera
{
private:
    glm::mat4 m_Position;
public:
    Camera() : m_Position(glm::mat4(1.0f)) {}

    void moveCamera(float x, float y, float z);

    inline glm::mat4 GetPosition() const
    {
        return m_Position;
    }
};
