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
#include "Camera/Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    float vertices[] = {
        // ---- Pos ---- // ---- Tex Coords ---- //
        000.0f, 100.0f,     0.0f, 0.0f, //bottom left
        100.0f, 100.0f,     1.0f, 0.0f,  //bottom right
        100.0f, 000.0f,     1.0f, 1.0f,  //top right
        000.0f, 000.0f,     0.0f, 1.0f  //top left
    };

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

    // Create Model View Projection Matrix
    // Projection Matrix makes the vertex space from
    // (0,0) in the top left to (windowWidth, windowHeight) in the bottom right
    glm::mat4 proj = glm::ortho(0.0f, windowWidth, windowHeight, 0.0f, -1.0f, 1.0f);
    // Create Camera and get its position;
    Camera camera;
    glm::mat4 view = camera.GetPosition();
    // place block in middle of the screen
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((windowWidth/2)-50, (windowHeight/2)-50, 0.0f));

    // MUST multiply in this order
    glm::mat4 mvp = proj * view * model;
    Shader *shader = new Shader("shaders/Basic.shader");
    shader->Bind();
    shader->SetUniformMat4f("u_MVP", mvp);

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
        shader->SetUniformMat4f("u_MVP", mvp);
        texture->Bind(0);
        renderer.Draw(*va, *ib, *shader);

        // matrix stuff
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        GLCall(glViewport(0, 0, width, height));
        proj = glm::ortho( 0.0f, (float)width, (float)height, 0.0f,  -1.0f, 1.0f);
        view = camera.GetPosition();
        model = glm::translate(glm::mat4(1.0f), glm::vec3((width/2)-50, (height/2)-50, 0.0f));
        mvp = proj * view * model;

        // glfw stuff
        glfwSwapBuffers(window);
        // keyboard input;
        int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
        if (state == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, 1);
        }
        state = glfwGetKey(window, GLFW_KEY_W);
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
