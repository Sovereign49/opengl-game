#pragma once

#include "Test.h"
#include "Shader/Shader.h"
#include "VertexArray/VertexArray.h"
#include "IndexBuffer/IndexBuffer.h"
#include "Texture/Texture.h"
#include "Camera/Camera.h"
#include "Renderer/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace test {

class Test2Quads : public Test
{
public:
    Test2Quads();
    ~Test2Quads();

    virtual void OnUpdate(float deltaTime, GLFWwindow *window);
    virtual void OnRender() override;
private:
    Shader shader = Shader("shaders/Quad.shader");
    VertexArray va = VertexArray();
    IndexBuffer ib;
    Texture texture = Texture("res/textures/grass.png");
    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 800.0f, 0.0f, -1.0f, 1.0f);
    Camera camera;
    glm::mat4 model = glm::mat4(1.0f);
    Renderer renderer;
    int width = 800;
    int height = 800;
};

}
