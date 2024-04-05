#include "Shader.h"
namespace RR {
    Shader::Shader(const char* vpath, const char* fpath) {
        std::ifstream vfile;
        std::ifstream ffile;
        vfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        ffile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vfile.open(vpath);
            ffile.open(fpath);
            std::stringstream vstream, fstream;
            vstream << vfile.rdbuf();
            fstream << ffile.rdbuf();
            vfile.close();
            ffile.close();
            vertexcode = vstream.str();
            fragmentcode = fstream.str();
        }
        catch (std::fstream::failure& e)
        {
            std::cout << "error::Cannot read the shader files " << e.what() << std::endl;
        }
        key = vertexcode + fragmentcode;
    }
    void Shader::use() {
        glUseProgram(ID);
    }
    void  Shader::Setbool(const std::string& name, bool value)const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void Shader::SetFloat(const std::string& name, float value)const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::SetInt(const std::string& name, int value)const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value)const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value)const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
    }
    void Shader::SetMat4(const std::string& name, const glm::mat4& value)const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }
    GLuint Shader::Compile() {
        const char* vcode = vertexcode.c_str();
        const char* fcode = fragmentcode.c_str();
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[1024];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vcode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
            std::cout << "VERTEX SHADER COMPILE ERROR " << infoLog << std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fcode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
            std::cout << "FRAGMENT SHADER COMPILE ERROR " << infoLog << std::endl;
        }
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 1024, NULL, infoLog);
            std::cout << " SHADER COMPILE ERROR " << infoLog << std::endl;
        }
        else {
            std::cout << "SHADER COMPILE COMPLETE" << std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return ID;
    }
    std::string Shader::Key() {
        return this->key;
    }
    Shader::~Shader() {

    }
}