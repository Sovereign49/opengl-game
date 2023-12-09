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

int main()
{

    glfwInit();

    // Set the gl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window object
    int windowWidth = 800;
    int windowHeight = 800;
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "OpenGl-Tut", NULL, NULL);
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
    GLCall(glViewport(0, 0, windowWidth, windowHeight));

    GLfloat vertices[] = {
        -0.5f,  -0.5f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 1.0f, 0.0f, // bottom right
        0.5f, 0.5f, 1.0f, 1.0f,   // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f  // top left
    };

    GLuint indices[] {
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray *va = new VertexArray();

    VertexBuffer *vb = new VertexBuffer(vertices, 4*4*sizeof(GLfloat));
    IndexBuffer *ib = new IndexBuffer(indices, 6);

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    va->AddBuffer(*vb, layout, *ib);

    Shader *shader = new Shader("shaders/Basic.shader");
    shader->Bind();

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
        texture->Bind(0);
        renderer.Draw(*va, *ib, *shader);

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
