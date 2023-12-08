#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    std::string ParseShader(const std::string& filepath);

    GLuint CompileShader(GLuint type, const std::string& source);

public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const std::string vertexPath, const std::string fragmentPath);
    // use/activate the shader
    void use();
    // delete the shader
    void del();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};
