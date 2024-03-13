#define GLFW_INCLUDE_NONE
#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glad/glad.h>
namespace RR {
	/// <summary>
	/// Shader处理类
	/// </summary>
	class Shader {
	private:
		//名字
		std::string name;
		//shader的id
		GLuint ID;
		std::string vertexcode;
		std::string fragmentcode;
		std::string key;
	public:
		Shader(const char* vpath, const char* fpath);
		void use();
		void Setbool(const std::string& name, bool value)const;
		void SetInt(const std::string& name, int value)const;
		void SetFloat(const std::string& name, float value)const;
		void SetVec3(const std::string& name, const glm::vec3& value)const;
		void SetVec4(const std::string& name, const glm::vec4& value)const;
		void SetMat4(const std::string& name, const glm::mat4& value)const;
		GLuint Compile();
		std::string Key();
	};
}