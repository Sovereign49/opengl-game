#pragma once

#include "VertexArray/VertexArray.h"
#include "Test.h"
#include "Shader/Shader.h"
#include "IndexBuffer/IndexBuffer.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

class Test2Quads : public Test
{
public:
    Test2Quads();
    ~Test2Quads();

    virtual void OnUpdate(float deltaTime, GLFWwindow *window) override;
    void OnRender(Renderer renderer) override;
private:
    Shader shader = Shader("shaders/Quad.shader");
    VertexArray va = VertexArray();
    IndexBuffer ib;
    Texture texture = Texture("res/textures/grass.png");
    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);
    Camera camera;
    glm::mat4 model = glm::scale(glm::mat4(1.0f),glm::vec3(100.0f));
    int width = 800;
    int height = 800;
};

}
