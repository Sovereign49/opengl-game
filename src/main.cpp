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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"
#include "tests/Test2Quads.h"

int main()
{

    glfwInit();
    // Set the gl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window object
    float windowWidth = 800;
    float windowHeight = 800;
    GLFWwindow *window = glfwCreateWindow(800, 800, "OpenGl-Tut", NULL, NULL);
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
    GLCall(glViewport(0, 0, 800, 800));

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    test::TestClearColor testClearColor;
    test::Test2Quads test2Quads;

    enum TestChoice {
        clearColor, twoQuads
    };
    TestChoice currentTest = clearColor;
    std::string currentTestName = "Clear Color";
    // Window run loop
    while (!glfwWindowShouldClose(window)) {

        //GLCall(glClearColor(1.0f,1.0f,1.0f,1.0f));
        //GLCall(glClear(GL_COLOR_BUFFER_BIT));
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        switch (currentTest) {
        case clearColor:
            testClearColor.OnUpdate(0.0f);
            testClearColor.OnRender();
            testClearColor.OnImGuiRender();
            break;
        case twoQuads:
            test2Quads.OnUpdate(0.0f, window);
            test2Quads.OnRender();
            test2Quads.OnImGuiRender();

            break;

        }

        // Test Selector
        ImGui::Begin("Test Selector");
        ImGui::Text("Current Test: %s", currentTestName.c_str());
        if (ImGui::Button("Clear Color"))
        {
            currentTestName = "Clear Color";
            currentTest = clearColor;
        }
        if (ImGui::Button("2 Quads"))
        {
            currentTestName = "2 Quads";
            currentTest = twoQuads;
        }
        ImGui::End();

        // Render imgui stuff
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
