#include"ComputeShader.h"
namespace RR {
	ComputeShader::ComputeShader(const char* path) {
		std::ifstream cfile;
		cfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            cfile.open(path);
            std::stringstream cstream;
            cstream << cfile.rdbuf();
            cfile.close();
            computecode = cstream.str();
        }
        catch (std::fstream::failure& e)
        {
            std::cout << "error::Cannot read the shader files " << e.what() << std::endl;
        }
        key = computecode;
	}
    GLuint ComputeShader::Compile() {
        const char* ccode = this->computecode.c_str();
        GLuint compute;
        GLint success;
        GLchar infoLog[1024];
        compute = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &ccode, nullptr);
        glCompileShader(compute);
        glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(compute, 1024, NULL, infoLog);
            std::cout << "COMPUTE SHADER COMPILE ERROR " << infoLog << std::endl;
        }

        // shader Program
        this->computeid = glCreateProgram();
        glAttachShader(this->computeid, compute);
        glLinkProgram(this->computeid);
        glGetProgramiv(this->computeid, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->computeid, 1024, NULL, infoLog);
            std::cout << this->name << " SHADER COMPILE ERROR " << infoLog << std::endl;
        }
        else {
            std::cout << this->name << "COMPUTE SHADER COMPILE COMPLETE" << std::endl;
        }
        glDeleteShader(compute);
        return this->computeid;
    }
    void ComputeShader::use(const GLuint& width, const GLuint& height) {
        glUseProgram(this->computeid);
        this->setFloat("time", glfwGetTime());
        this->setVec2("wind", glm::vec2(1, 3));
        this->setFloat("A", 1);
        glDispatchCompute(width, height, 1);
        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    }
    void ComputeShader::setFloat(const std::string& name, const float& value) const {
        glUniform1f(glGetUniformLocation(this->computeid, name.c_str()), value);
    }
    void ComputeShader::setVec2(const std::string& name, const glm::vec2& value) const {
        glUniform2f(glGetUniformLocation(this->computeid, name.c_str()), value.x, value.y);
    }
}