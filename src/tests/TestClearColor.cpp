#include "TestClearColor.h"
#include "Macros/Macros.h"
#include "imgui/imgui.h"

namespace test {

TestClearColor::TestClearColor()
    : m_ClearColor {0.2f, 0.3f, 0.8f, 1.0f}
{

}

void TestClearColor::OnRender(Renderer renderer)
{
    GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
    renderer.Clear();
}

void TestClearColor::OnImGuiRender()
{
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::ColorEdit3("clear color", m_ClearColor); // Edit 3 floats representing a color
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}

}
