#pragma once
#include <fstream>
#include <sstream>

#include "common.h"

using namespace std;

class Shader
{
private:
    string ParseShader(const string& filepath);

    GLuint CompileShader(GLuint type, const string& source);

public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const string vertexPath, const string fragmentPath);
    // use/activate the shader
    void use();
    // delete the shader
    void del();
    // utility uniform functions
    void setBool(const string &name, bool value, int num) const;
    void setInt(const string &name, int value, int num) const;
    void setFloat(const string &name, float value, int num) const;
};
