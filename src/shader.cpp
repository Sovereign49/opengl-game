#include "shader.h"
#include "renderer.h"

// constructor reads and builds the shader
Shader::Shader(const string vertexPath, const string fragmentPath) {
    string vertSrc = ParseShader(vertexPath);
    string fragSrc = ParseShader(fragmentPath);
    GLCall(GLuint program = glCreateProgram());
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    ID = program;

}
// use/activate the shader
void Shader::use() {
    GLCall(glUseProgram(ID));
}
// delete the shader
void Shader::del() {
    GLCall(glDeleteProgram(ID));
}
// utility uniform functions
void Shader::setBool(const string &name, bool value, int num) const {
    GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value));
}
void Shader::setInt(const string &name, int value, int num) const {
    GLCall(glUniform1i(glGetUniformLocation(ID, name.c_str()), value));
}
void Shader::setFloat(const string &name, float value, int num) const {
    GLCall(glUniform1f(glGetUniformLocation(ID, name.c_str()), value));
}

string Shader::ParseShader(const string& filepath) {
    ifstream file(filepath);

    stringstream shader;
    shader << file.rdbuf();
    return shader.str();
}

GLuint Shader::CompileShader(GLuint type, const string& source) {
    GLCall(GLuint id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
