#include "Test2Quads.h"

namespace test {

float vertices[] = {
    // ---- Pos ---- // ---- Tex Coords ---- //
    000.0f, 100.0f,     0.0f, 0.0f, //bottom left
    100.0f, 100.0f,     1.0f, 0.0f,  //bottom right
    100.0f, 000.0f,     1.0f, 1.0f,  //top right
    000.0f, 000.0f,     0.0f, 1.0f  //top left
};

unsigned int indices[] = {
    0,1,2,
    2,3,0
};

Test2Quads::Test2Quads() : ib(indices, 6)
{
    VertexBuffer vb = VertexBuffer(vertices, 4*4*sizeof(GLfloat));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    shader.Bind();
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    // Unbind everything
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
}

Test2Quads::~Test2Quads()
{

}

void Test2Quads::OnUpdate(float deltaTime, GLFWwindow *window)
{

    glfwGetWindowSize(window, &width, &height);
    GLCall(glViewport(0, 0, width, height));
    proj = glm::ortho( 0.0f, (float)width, (float)height, 0.0f,  -1.0f, 1.0f);

    // keyboard input;
    int state = glfwGetKey(window, GLFW_KEY_W);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(0, -10, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_S);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(0, 10, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_A);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(-10, 0, 0);
    }
    state = glfwGetKey(window, GLFW_KEY_D);
    if (state == GLFW_PRESS)
    {
        camera.moveCamera(10, 0, 0);
    }
}

void Test2Quads::OnRender()
{
    GLCall(glClearColor(0.45f, 0.55f, 0.60f, 1.00f));
    renderer.Clear();
    {
        glm::mat4 view = camera.GetPosition();
        model = glm::translate(glm::mat4(1.0f), glm::vec3((width/2)-100, (height/2)-50, 0.0f));
        glm::mat4 mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);
    }
    {
        glm::mat4 view = camera.GetPosition();
        model = glm::translate(glm::mat4(1.0f), glm::vec3((width/2), (height/2)-50, 0.0f));
        glm::mat4 mvp = proj * view * model;

        shader.Bind();
        shader.SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(va, ib, shader);
    }

}

}
