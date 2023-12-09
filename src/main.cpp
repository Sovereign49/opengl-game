#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "shader.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

void window_size_callback(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

int main() {
    const string vertsource = "shaders/triangle.vert";
    const string fragsource = "shaders/triangle.frag";

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
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context and initialize glew
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize glew" << endl;
    }

    // Create a viewport
    GLCall(glViewport(0, 0, windowWidth, windowHeight));

    GLfloat vertices[] = {
        0.5f,  0.5f,  // top right
        0.5f, -0.5f,  // bottom right
        -0.5f, -0.5f,  // bottom left
        -0.5f,  0.5f,   // top left
    };

    GLuint indices[] {
        0,1,3,
        1,2,3
    };

    VertexBuffer *vb = new VertexBuffer(vertices, 4*2*sizeof(GLfloat));
    IndexBuffer *ib = new IndexBuffer(indices, 6);
    VertexArray *va = new VertexArray();
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout, *ib);

    Shader *shader = new Shader(vertsource, fragsource);
    GLCall(glUseProgram(0));
    GLCall(glBindVertexArray(0));

    // Window run loop
    while (!glfwWindowShouldClose(window)) {

        // Render Here
        // Set the bckground color
        GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Render Square
        shader->use();
        GLCall(GLuint location = glGetUniformLocation(shader->ID, "u_Color"));
        ASSERT(location != -1);
        GLCall(glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f));
        va->Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
        glfwSetWindowSizeCallback(window, window_size_callback);
        glfwPollEvents();
    }

    // Cleanup
    delete shader;
    delete vb;
    delete ib;
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
