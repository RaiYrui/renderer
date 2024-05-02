#pragma once
#define GLFW_INCLUDE_NONE
#include<iostream>
#include<fstream>
#include<sstream>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glad/glad.h>
namespace RR {
	class ComputeShader {
	private:
		std::string name;
		GLuint computeid;
		std::string computecode;
		std::string key;
	public:
		ComputeShader(const char* path);
		GLuint Compile();
		void dispatch(const GLuint& width,const GLuint& height);
		void use();
		void setFloat(const std::string& name, const float& value) const;
		void setBool(const std::string& name, const bool& value) const;
		void setInt(const std::string& name, const int& value) const;
		void setVec2(const std::string& name, const glm::vec2& value) const;
	};
}