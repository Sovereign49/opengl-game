#include "common.h"
#include "shader.h"
#include "common.cpp"

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
    glewInit();

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

    GLuint VBO, VAO, IBO;

    // Create Objects
    GLCall(glGenVertexArrays(1, &VAO));
    GLCall(glGenBuffers(1, &VBO));
    GLCall(glGenBuffers(1, &IBO));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    GLCall(glBindVertexArray(VAO));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCall(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // Position
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*2, (void*)0));
    GLCall(glEnableVertexAttribArray(0));

    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    GLCall(glBindVertexArray(0));

    Shader shader = Shader(vertsource, fragsource);

    // Window run loop
    while (!glfwWindowShouldClose(window)) {

        // Render Here
        // Set the bckground color
        GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        // Render Square
        shader.use();
        GLCall(glBindVertexArray(VAO));
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    GLCall(glDeleteVertexArrays(1, &VAO));
    GLCall(glDeleteBuffers(1, &VBO));
    GLCall(glDeleteBuffers(1, &IBO));
    shader.del();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
