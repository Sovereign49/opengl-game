#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <csignal>
#include <assert.h>

using namespace std;

/*
static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line << endl;
        return false;
    }
    return true;
}
*/

// If fails with a core dump try gdb
#define ASSERT(x) assert((x));

#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))
