#pragma once
#include "Macros/Macros.h"
#include "Renderer/Renderer.h"

#include <vector>
#include <string>
#include <functional>
#include <GLFW/glfw3.h>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texture;
};

namespace test {

class Test
{
public:
    Test() {}
    virtual ~Test() {}

    virtual void OnUpdate(float deltaTime, GLFWwindow *window) {}
    virtual void OnRender(Renderer renderer) {}
    virtual void OnImGuiRender() {}
};

class TestMenu : public Test
{
public:
    TestMenu(Test*& currentTestPointer);

    void OnImGuiRender() override;
    template <typename T>
    void RegisterTest(const std::string& name)
    {
        std::cout << "Registering test: " << name << std::endl;
        RegisterTest(name, identity<T>());
    }
private:
    Test*& m_CurrentTest;
    std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;

    template <typename T>
    void RegisterTest(const std::string& name, identity<T>)
    {
        m_Tests.push_back(std::make_pair(name, []() {
            return new T();
        }));
    }
};

}
