#include "TestCube.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace test {

TestCube::TestCube()
{
    struct Vertex vertices[] = {
        { {-0.5f, 0.5f, -10.0f}, {0.0f,0.0f} },
        { {0.5f, 0.5, -10.0f}, {1.0f,0.0f} },
        { {0.5f, -0.5, -10.0f}, {1.0f,1.0f} },
        { {-0.5f, -0.5, -10.0f}, {0.0f,1.0f} },
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    VertexBuffer vb = VertexBuffer(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    ib.Init(indices, 6);
    shader.Bind();
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    // Unbind everything
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
}

TestCube::~TestCube()
{

}

void TestCube::OnUpdate(float deltaTime, GLFWwindow *window)
{
    float projectionWidth = 1920.0f;
    glfwGetWindowSize(window, &width, &height);
    GLCall(glViewport(0, 0, width, height));
    float windowAspect = ((float)width/(float)height);
    float fov = 45.0f;
    float near = 0.01f;
    float far = 10000.0f;
    proj = glm::perspective(fov, windowAspect, near, far);
    model = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));

    // keyboard input;
    int spd = 2;
    int state = glfwGetKey(window, GLFW_KEY_W);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(0, -spd, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_S);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(0, spd, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_A);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(-spd, 0, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_D);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(spd, 0, 0);
    }
}

void TestCube::OnRender(Renderer renderer)
{
    {
        glm::mat4 view = camera.GetViewMatrix();
        model = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));
        glm::mat4 mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);
    }
    {
        glm::mat4 view = camera.GetViewMatrix();
        model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(100.0f));
        glm::mat4 mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);
    }

}

}
