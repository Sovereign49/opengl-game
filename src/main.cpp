#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "Macros/Macros.h"
#include "Renderer/Renderer.h"
#include "Shader/Shader.h"

#include "Texture/Texture.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "VertexArray/VertexArray.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void window_size_callback(GLFWwindow* window, int windowWidth, int windowHeight)
{
}

int main()
{

    glfwInit();

    // Set the gl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window object
    float windowWidth = 960;
    float windowHeight = 540;
    GLFWwindow *window = glfwCreateWindow(960, 540, "OpenGl-Tut", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context and initialize glew
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize glew" << std::endl;
    }

    // Create a viewport
    GLCall(glViewport(0, 0, 960, 540));

    /*
    float vertices[] = {
        // ---- Pos ---- // ---- Tex Coords ---- //
        -0.5f, -0.5f,      0.0f, 0.0f, //bottom left
        0.5f, -0.5f,      1.0f, 0.0f,  //bottom right
        0.5f,  0.5f,      1.0f, 1.0f,  //top right
        -0.5f,  0.5f,      0.0f, 1.0f  //top left
    };

    */
    ///*
    float vertices[] = {
        // ---- Pos ---- // ---- Tex Coords ---- //
        100.0f, 200.0f,     0.0f, 0.0f, //bottom left
        200.0f, 200.0f,     1.0f, 0.0f,  //bottom right
        200.0f, 100.0f,     1.0f, 1.0f,  //top right
        100.0f, 100.0f,     0.0f, 1.0f  //top left
    };
    //*/
    unsigned int indices[] {
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray *va = new VertexArray();

    VertexBuffer *vb = new VertexBuffer(vertices, 4*4*sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout);

    IndexBuffer *ib = new IndexBuffer(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
    //glm::mat4 proj = glm::ortho( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    Shader *shader = new Shader("shaders/Basic.shader");
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", proj);

    Texture *texture = new Texture("res/textures/grass.png");
    texture->Bind(0);
    shader->SetUniform1i("u_Texture", 0);

    // Unbind everything
    va->Unbind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();
    texture->Unbind();

    Renderer renderer;

    // Window run loop
    while (!glfwWindowShouldClose(window)) {

        // Render Here
        renderer.Clear();

        // Render Square
        // Bind shader to use uniform
        shader->Bind();
        shader->SetUniform1i("u_Texture", 0);
        shader->SetUniformMat4f("u_MVP", proj);
        texture->Bind(0);
        renderer.Draw(*va, *ib, *shader);

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        GLCall(glViewport(0, 0, width, height));
        proj = glm::ortho( 0.0f, (float)width, (float)height, 0.0f,  -1.0f, 1.0f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    delete va;
    delete shader;
    delete vb;
    delete ib;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
